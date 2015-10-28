#include "memory.h"

void IPatch::Toggle() {
	if (m_applied)
		Remove();
	else
		Apply();
}

CPatch::CPatch(uintptr_t address, uintptr_t function, uint8_t instruction, uint32_t len) {
	m_target = address;
	m_length = len;
	m_source = function;
	m_bInstruction = instruction;
	m_type = PatchType::Trampoline;
	m_applied = false;

	StoreOriginal();
	Generate();
}

CPatch::CPatch(uintptr_t address, uint8_t* pData, uint32_t len) {
	m_target = address;
	m_length = len;
	m_type = PatchType::Mempatch;
	m_applied = false;

	StoreOriginal();

	m_bPatchBuffer = pData;
}

CPatch::~CPatch() {
	Write(m_bOriginalCode);

	delete m_bOriginalCode;
	delete m_bPatchBuffer;
}

void CPatch::StoreOriginal() {
	if (!m_target || m_bOriginalCode)
		return;

	uint8_t* bOriginal = new uint8_t[m_length];
	memcpy(bOriginal, (void*)m_target, m_length);

	m_bOriginalCode = bOriginal;
}

bool CPatch::Write(void* data) {
	DWORD dwOldProt;
	void* destination = (void*)m_target;

	if (!VirtualProtect(destination, m_length, PAGE_READWRITE, &dwOldProt))
		return false;

	memcpy(destination, data, m_length);

		

	return VirtualProtect(destination, m_length, dwOldProt, &dwOldProt);
}

void CPatch::Apply() {
	if (m_applied || (m_manager && !m_manager->m_bEnabled))
		return;

	Write(m_bPatchBuffer);
	m_applied = true;
}

void CPatch::Remove() {
	if (!m_applied || (m_manager && !m_manager->m_bEnabled))
		return;

	Write(m_bOriginalCode);
	m_applied = false;
}

void CPatch::InitPatchBuffer() {
	if (m_bPatchBuffer)
		delete m_bPatchBuffer;

	m_bPatchBuffer = new uint8_t[m_length];
	memset(m_bPatchBuffer, 0x90, m_length);
}

bool CPatch::Generate() {
	if (m_type == PatchType::Mempatch)
		return false;

	InitPatchBuffer();

	m_bPatchBuffer[0] = m_bInstruction;

	/*
	To jump from one position to the next, get the offset between the
	patch location and the patch destination +5 bytes for the length of the instruction.
	*/
	uintptr_t dwFunc = m_source - (m_target + 5);

	//Write the information directly to the address of the first offset (4 bytes).
	*(uintptr_t*)&m_bPatchBuffer[1] = dwFunc;

	return true;
}

CVMTHook::CVMTHook(uintptr_t** vtable)
{
	m_pBaseVMT = vtable;
	m_pOriginalVMT = *vtable;

	m_size = GetVMTSize();

	m_pProxyVMT = new uintptr_t[m_size];

	memcpy(m_pProxyVMT, m_pOriginalVMT, sizeof(uintptr_t)*m_size);
}

CVMTHook::~CVMTHook()
{
	if (m_pBaseVMT)
		*m_pBaseVMT = m_pOriginalVMT;

	delete m_pProxyVMT;
}

void CVMTHook::Apply()
{
	if (m_applied || (m_manager && !m_manager->m_bEnabled))
		return;

	if (m_pBaseVMT)
		*m_pBaseVMT = m_pProxyVMT;

	m_applied = true;
}

void CVMTHook::Remove()
{
	if (!m_applied || (m_manager && !m_manager->m_bEnabled))
		return;

	if (m_pBaseVMT)
		*m_pBaseVMT = m_pOriginalVMT;

	m_applied = false;
}

uintptr_t CVMTHook::Hook(uintptr_t newfunc, uint32_t index)
{
	if (m_pOriginalVMT && m_pProxyVMT && index >= 0 && index < m_size) {
		m_pProxyVMT[index] = newfunc;
		return m_pOriginalVMT[index];
	}

	return 0;
}

//This isn't guaranteed to give the actual VMT size.
uint32_t CVMTHook::GetVMTSize()
{
	uint32_t index = 0;

	while (!IsBadCodePtr((FARPROC)m_pOriginalVMT[index]))
		index++;

	return index;
}

CPatchManager::~CPatchManager() {
	for (auto it = m_patches.begin(); it != m_patches.end(); it++)
		delete (*it);
}

void CPatchManager::AddPatch(IPatch* Patch) {
	m_patches.push_back(Patch);
	Patch->m_manager = this;
}

void CPatchManager::Enable() {
	if (m_bEnabled)
		return;

	for (auto it = m_patches.begin(); it != m_patches.end(); it++) {
		auto* Patch = *it;
		Patch->Apply();
	}

	m_bEnabled = true;
}

void CPatchManager::Disable() {
	if (!m_bEnabled)
		return;

	for (auto it = m_patches.begin(); it != m_patches.end(); it++) {
		auto* Patch = *it;
		Patch->Remove();
	}

	m_bEnabled = false;
}

void CPatchManager::Toggle() {
	if (m_bEnabled)
		Enable();
	else
		Disable();
}
