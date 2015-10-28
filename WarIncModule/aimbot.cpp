#include "aimbot.h"
#include "stdafx.h"
#include "structures.h"
#include "cvars.h"

#define M_PI (float)3.141593
#define RAD (180.0f / M_PI)

using namespace WarHook;

namespace WarHook
{
	namespace Aimbot
	{
		CPlayer* pAimTarget;
		CPlayer* LocalPlayer;

		float fDistance;
		bool bShooting = false;
		bool bAiming = false;

		float flAimFOV = 360;
	}
}

bool Aimbot::IsValid(CPlayer* Target)
{
	if (!Target)
		return false;

	if (Target->m_bIsDead)
		return false;

	if (Target->GetTeam() == LocalPlayer->GetTeam())
		return false;

	return true;
}

void Aimbot::Scan()
{
	CPlayer* Target = nullptr;
	fDistance = 0;

	for (int i = 0; i < NetworkManager->m_player_count; i++)
	{
		CPlayer* Player = NetworkManager->GetPlayer(i);

		if (!IsValid(Player))
			continue;

		float Distance = Player->m_position.Distance(LocalPlayer->m_position);

		if (fDistance == 0 || Distance < fDistance)
		{
			fDistance = Distance;
			Target = Player;
		}
	}

	if (Target)
		pAimTarget = Target;
	else
		pAimTarget = nullptr;
}

void Aimbot::Aim()
{
	if (!pAimTarget || !LocalPlayer)
		return;

	Vec3 vHeadPos; 
	Vec3 vHeadPosLocal = *(Vec3*)(ImageBase + 0x74BF48); //Magic numbers galore~
	
	if (!pAimTarget->GetBoneOrigin(pAimTarget->m_head_id, vHeadPos))
		return;
	
	Vec3 vAimDirection = vHeadPos - vHeadPosLocal;

	vAimDirection.normalize();	

	float pitch = (atan2(vAimDirection.y, vAimDirection.magnitude2d_2()) * RAD);
	float yaw = (atan2(vAimDirection.x, vAimDirection.z) * RAD);
	
	LocalPlayer->m_pitch = pitch;
	LocalPlayer->m_yaw = -yaw;
}

void Aimbot::Think()
{
	if (!cVars::aimbot)
		return;

	LocalPlayer = NetworkManager->GetLocalPlayer();

	if (!LocalPlayer)
		return;

	Scan();

	if (GetAsyncKeyState(VK_RBUTTON))
		bAiming = true;
	else
		bAiming = false;

	if (bAiming)
		Aimbot::Aim();
}