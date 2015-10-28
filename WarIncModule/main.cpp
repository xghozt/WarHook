#include "stdafx.h"
#include "structures.h"
#include "patches.h"
#include "memory.h"
#include "menu.h"
#include "cvars.h"

namespace WarHook {
	uint32_t ImageBase;
	R3DNetwork* NetworkManager;
	CPatchManager* PatchManager;
}

HANDLE hRepatch;
DWORD dwOld;

void RepatchThread()
{
	while (true)
	{
		WarHook::D3DHook::Rehook();
		Sleep(5);
	}
}

void Cleanup(HMODULE hModule)
{
	delete WarHook::PatchManager;

	TerminateThread(hRepatch, 0);
	WarHook::D3DHook::Restore();

	std::cout << "[WarHook] Unhooking and gtfo-ing!\n" << std::endl;

	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
}

void MainThread(HMODULE hModule)
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	freopen("CON", "w", stdout);

	gMenu.Initialize();

	WarHook::ImageBase = (uint32_t)GetModuleHandle("WarInc.exe");
	
	WarHook::NetworkManager = R3DNetwork::Get();
	WarHook::D3DHook::Render = R3DRenderer::Get();

	/*======================================================================*/
	/*DirectX Hooking														*/
	/*======================================================================*/
	while (true)
	{
		if (!WarHook::D3DHook::Render)
		{
			Sleep(250);
			continue;
		}

		IDirect3DDevice9* pDevice = WarHook::D3DHook::Render->m_pDevice;

		if (pDevice == nullptr) 
		{
			Sleep(250);
			return;
		}

		WarHook::D3DHook::dxDeviceVMT = *(uintptr_t**)pDevice;
		WarHook::D3DHook::Apply();

		hRepatch = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RepatchThread, 0, 0, 0);
		break;
	}
	
	WarHook::PatchManager = new CPatchManager();
	WarHook::Patches::Apply(WarHook::PatchManager);

	float* flJumpHeight = (float*)(WarHook::ImageBase + 0x6EDA98);
	VirtualProtect((void*)flJumpHeight, sizeof(float), PAGE_EXECUTE_READWRITE, &dwOld);

	while (true)
	{
		if (GetAsyncKeyState(VK_INSERT) & 1)
		{	
			Cleanup(hModule);
			break;
		}

		CPlayer* LocalPlayer = WarHook::NetworkManager->GetLocalPlayer();

		if (LocalPlayer)
		{
			Weapon* pSelectedWeapon = LocalPlayer->m_weaponSlots[LocalPlayer->m_selectedWeapon];

			if (pSelectedWeapon)	
				pSelectedWeapon->m_firemode = 4;
		}

		*flJumpHeight = WarHook::cVars::jumpheight;

		Sleep(5);
	}
}

bool __stdcall DllMain( HMODULE hModule, DWORD  dwReason, LPVOID lpReserved )
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0);
			break;
		case DLL_PROCESS_DETACH:
			break;
	}

	return true;
}