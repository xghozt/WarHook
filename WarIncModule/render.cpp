#include "render.h"
#include "stdafx.h"
#include "esp.h"
#include "structures.h"
#include "menu.h"
#include "cvars.h"

using namespace WarHook;

void DebugLayout();

void Main::Render()
{
	Render::DrawTextA(D3DHook::Render->m_width - 5, 5, Color(0, 255, 195), DT_RIGHT, "Warhook by Firehawk");

	if (cVars::esp)
		Esp::Render();
	
	//Debug
	if (cVars::showdebug)
		DebugLayout();

	if (gMenu.bVisible)
		gMenu.Draw();

	if (GetAsyncKeyState(VK_HOME) & 1)
		gMenu.bVisible = !gMenu.bVisible;

	if (gMenu.bVisible)
	{
		if (GetAsyncKeyState(VK_UP) & 1) gMenu.NavigateUp();
		if (GetAsyncKeyState(VK_DOWN) & 1) gMenu.NavigateDown();
		if (GetAsyncKeyState(VK_LEFT) & 1) gMenu.Decrease();
		if (GetAsyncKeyState(VK_RIGHT) & 1) gMenu.Increase();
	}
}

void DebugLayout()
{
	float y_offset = 100;

	CPlayer* LocalPlayer;

	if (NetworkManager)
	{
		LocalPlayer = NetworkManager->GetLocalPlayer();

		Render::DrawText(20, y_offset, color_white, DT_LEFT, "R3DNetwork: %x", NetworkManager);
		y_offset += 15;
	}

	CObjectManager* ObjectManager = CObjectManager::Get();

	if (ObjectManager)
	{
		Render::DrawText(20, y_offset, color_white, DT_LEFT, "ObjectManager: %x", ObjectManager);
		y_offset += 15;

		//Finds LocalPlayer in the main menu (For the shooting range)
		if (!LocalPlayer)
		{
			CGameObject* Object = ObjectManager->GetFirst();

			for (CGameObject* Object = ObjectManager->GetFirst(); Object && Object->GetNext(); Object = Object->GetNext())
			{
				if (Object->GetObjectInfo()->m_id == OBJECT_AI_PLAYER)
				{
					LocalPlayer = (CPlayer*)Object;
					break;
				}
			} 
		}
	}

	if (LocalPlayer)
	{
		Render::DrawText(20, y_offset, color_white, DT_LEFT, "LocalPlayer: %x [0x%x]", LocalPlayer, LocalPlayer->GetObjectInfo());
		y_offset += 15;

		for (int slot = 0; slot < SLOT_MAX; slot++)
		{
			Weapon* pWeapon = LocalPlayer->m_weaponSlots[slot];

			if (!pWeapon)
				continue;

			Render::DrawText(40, y_offset, color_white, DT_LEFT, "Slot Weapon %i: %x (CWeaponConfig: %x)", slot, pWeapon, pWeapon->GetWeaponConfig());
			y_offset += 15;
		}

		Render::DrawTextA(20, y_offset, color_white, DT_LEFT, "Health: %f", LocalPlayer->GetHealth());
	}
}