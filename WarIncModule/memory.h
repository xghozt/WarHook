#pragma once

#include <vector>
#include <iostream>
#include <Windows.h>
#include <stdint.h>

#define CODE_JMP	0xE9
#define CODE_CALL	0xE8

class CPatchManager;

class IPatch
{
public:
	virtual void Apply() = 0;
	virtual void Remove() = 0;

	void Toggle();

	CPatchManager* m_manager;
	bool m_applied;

protected:
	uintptr_t m_target; //Location of the patch.
};

enum class PatchType { Trampoline, Mempatch };

//Detour/MemPatch Class
class CPatch : public IPatch
{
public:
	CPatch::CPatch(uintptr_t address, uintptr_t function, uint8_t instruction, uint32_t len);
	CPatch::CPatch(uintptr_t address, uint8_t* data, uint32_t len);
	~CPatch();

	PatchType m_type;				//The type of patch being applied.

	void Apply();
	void Remove();

	bool Write(void* data);
	void StoreOriginal();

private:
	bool Generate();
	void InitPatchBuffer();

	uint32_t m_length;

	uint8_t m_bInstruction;

	uint8_t* m_bOriginalCode;
	uint8_t* m_bPatchBuffer;

	uintptr_t m_source;				//Function to use for the patch.
};

//VMT/VFT Hooking.
class CVMTHook : public IPatch
{
public:
	CVMTHook::CVMTHook(uintptr_t** vtable);
	~CVMTHook();

	uint32_t GetVMTSize();

	void Apply();
	void Remove();

	uintptr_t Hook(uintptr_t newfunc, uint32_t index);

	template <class Type> inline Type GetOriginal(uint32_t index)
	{
		return (Type)m_pOriginalVMT[index];
	}

protected:
	uintptr_t* m_pProxyVMT;			//Pointer to our fake VMT.
	uintptr_t* m_pOriginalVMT;		//Pointer to the original VMT.
	uintptr_t** m_pBaseVMT;			//Far pointer to the VMT of the provided object.

	uint32_t m_size;
};

//Factory/Manager for the patches.
class CPatchManager
{
public:
	CPatchManager::CPatchManager() : m_bEnabled(true) {};
	~CPatchManager();

	bool m_bEnabled;

	void Enable();
	void Disable();
	void Toggle();

	void AddPatch(IPatch* Patch);

	template <typename T, typename...Args> inline T* Patch(Args...args)
	{
		auto Patch = new T(args...);

		if (Patch) {
			AddPatch(Patch);
			Patch->Apply();
		}

		return Patch;
	}

private:
	std::vector<IPatch*> m_patches;
};

namespace Memory
{
	template <typename T, typename...Args>
	T CallVFunc(uintptr_t** thisptr, uint32_t i, Args...args)
	{
		return ((T(__thiscall*)(void*, Args...))(*(*thisptr + i*4)))(thisptr, args...);
	}
}