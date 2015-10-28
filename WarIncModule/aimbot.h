#pragma once

class CPlayer;
class Vec3;

namespace WarHook
{
	namespace Aimbot
	{
		extern CPlayer* pAimTarget;
		extern float fDistance;
		extern bool bShooting;

		void Scan();
		void Aim();
		void Think();

		//bool IsInFOV(Vec3 Position);
		bool IsValid(CPlayer* Target);
	}
}