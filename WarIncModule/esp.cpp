#include "esp.h"
#include "stdafx.h"
#include "structures.h"
#include "cvars.h"

using namespace WarHook;

template<typename T, int size> int ArraySize(T(&)[size]) { return size; }

static const int Skeleton[5][7] =
{
	{ 06, 05, 04, 03, 02, 01, 00 },
	{ 05, 07,  8, 26, 27, 10, 00 },
	{ 05, 28, 29, 48, 49, 31, 00 },
	{ 01, 53, 54, 55, 56, 00, 00 },
	{ 01, 58, 59, 60, 61, 00, 00 }
};

void DrawSkeleton(CPlayer* Player)
{
	for (int a = 0; a < ArraySize(Skeleton); a++)
	{
		int SkipIndex = -1;
		Vec3 NextBone, CurrentBone;

		for (int b = 0; b < ArraySize(Skeleton[a]); b++)
		{
			if (b + 1 > ArraySize(Skeleton[a]) || Skeleton[a][b + 1] == 0)
				continue;

			if (b + 1 != SkipIndex)
			{
				if (!Player->GetBoneOrigin(Skeleton[a][b], CurrentBone))
					continue;

				if (!Render::WorldToScreen(CurrentBone, CurrentBone))
					continue;
			}
			else
				CurrentBone = NextBone;

			if (!Player->GetBoneOrigin(Skeleton[a][b + 1], NextBone))
				continue;

			if (Render::WorldToScreen(NextBone, NextBone))
				Render::DrawLine(CurrentBone.x, CurrentBone.y, NextBone.x, NextBone.y, color_teal);

			SkipIndex = b + 1;
		}
	}
}

bool RenderBoundingBox(CPlayer* Player, Color color, D3DRECT* rect, float& width)
{
	Vec3 vecFootPos, vecHeadPos;

	if (!Player->GetBoneOrigin(Player->m_head_id, vecHeadPos))
		return false;

	//Todo: Find the head height in memory.
	vecHeadPos.y += 0.25;

	if (!Render::WorldToScreen(vecFootPos, Player->m_position) || !Render::WorldToScreen(vecHeadPos, vecHeadPos))
		return false;

	int body_length = vecFootPos.y - vecHeadPos.y;
	int body_width = body_length / 2;

	int x1 = vecFootPos.x - (body_width / 2);
	int y1 = vecFootPos.y - body_length;

	int x2 = vecFootPos.x + (body_width / 2);
	int y2 = vecFootPos.y;

	if (rect) {
		rect->x1 = x1;
		rect->y1 = y1;
		rect->x2 = x2;
		rect->y2 = y2;

		width = body_width;
	}

	Render::DrawOutlinedRect(x1 + 1, y1 + 1, body_width - 2, body_length - 2, color_black);
	Render::DrawOutlinedRect(x1, y1, body_width, body_length, color);
	Render::DrawOutlinedRect(x1 - 1, y1 - 1, body_width + 2, body_length + 2, color_black);

	return true;
}

void DrawPlayer(CPlayer* Player)
{
	CPlayer* LocalPlayer = NetworkManager->GetLocalPlayer();

	if (!LocalPlayer)
		return;

	Vec3 Out = Vec3(0, 0, 0);

	bool teamPlayer = LocalPlayer->GetTeam() == Player->GetTeam();

	if (!Player || Player->m_bIsDead || (!cVars::esp_team && teamPlayer))
		return;

	if (!Player->GetBoneOrigin(Player->m_head_id, Out))
		return;

	Color boxColor = teamPlayer ? color_green : color_red;

	D3DRECT bbox = { 0, 0, 0, 0 };
	float bbox_width = 0;

	if (RenderBoundingBox(Player, boxColor, &bbox, bbox_width))
	{
		if (cVars::esp_skeleton)
			DrawSkeleton(Player);

		float center_x = bbox.x1 + bbox_width / 2;

		//Name Plate
		Render::DrawTextOutlined(center_x, bbox.y1 - 15, Player->GetName(), boxColor, DT_CENTER);

		CWeaponConfig* pWeaponConfig = Player->m_weaponSlots[Player->m_selectedWeapon]->GetWeaponConfig();

		float y_offset = 0;

		if (cVars::esp_health)
		{
			//Health Bar
			Render::FillRGB(center_x - 20, bbox.y2 + y_offset + 5, 40, 6, color_black);
			Render::FillRGB(center_x - 19, bbox.y2 + y_offset + 6, 38 * (Player->GetHealth() / 100.0f), 4, color_green);

			y_offset += 10;
		}

		if (cVars::esp_weapon)
		{
			//Weapon Name
			Render::DrawTextOutlined(center_x, bbox.y2 + y_offset, pWeaponConfig->m_name, color_white, DT_CENTER);

			y_offset += 10;
		}

		//Player Distance
		Render::DrawTextA(center_x, bbox.y2 + y_offset, color_white, DT_CENTER, "Distance: %.2f", Player->m_position.Distance(LocalPlayer->m_position));
	}
}

void Esp::Render()
{
	CObjectManager* ObjectManager = CObjectManager::Get();

	if (!ObjectManager)
		return;

	Vec3 Out = Vec3(0, 0, 0);

	for (CGameObject* Object = ObjectManager->GetFirst(); Object && Object->GetNext(); Object = Object->GetNext())
	{
		ObjectInfo_t* Info = Object->GetObjectInfo();

		if (!Info)
			continue;

		Color red_flash = color_red.Lerp(color_lightred, sinf(ObjectManager->m_frame));

		//Todo: Do anything less shitty than this.

		if (Info->m_id == OBJECT_AI_PLAYER)
		{
			DrawPlayer((CPlayer*)Object);
		}
		else if (Info->m_id == OBJECT_AUTOTURRET)
		{
			if (Render::WorldToScreen(Out, Object->m_position))
				Render::DrawTextA(Out.x, Out.y, red_flash, DT_CENTER, "**Turret**");
		}
		else if (Info->m_id == OBJECT_MINE)
		{
			if (Render::WorldToScreen(Out, Object->m_position))
				Render::DrawTextA(Out.x, Out.y, red_flash, DT_CENTER, "**Mine**");
		}
		else if (Info->m_id == OBJECT_GRENADE)
		{
			if (Render::WorldToScreen(Out, Object->m_position))
				Render::DrawTextA(Out.x, Out.y, red_flash, DT_CENTER, "**Grenade**");
		}
		else if (Info->m_id == OBJECT_SUPPLYCRATE)
		{
			if (Render::WorldToScreen(Out, Object->m_position))
				Render::DrawTextOutlined(Out.x, Out.y, "**Supply Crate**", color_green, DT_CENTER);
		}
		else if (Info->m_id == OBJECT_DROPPEDWEAPON)
		{   
			if (Render::WorldToScreen(Out, Object->m_position))
				Render::DrawTextOutlined(Out.x, Out.y, ((CDroppedWeapon*)Object)->GetName(), Color(195, 80, 255), DT_CENTER);
		}
	}
}
