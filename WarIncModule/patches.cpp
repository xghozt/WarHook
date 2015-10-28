#include "stdafx.h"
#include "patches.h"
#include "memory.h"
#include "cvars.h"
#include "aimbot.h"

using namespace WarHook;

const float Zero = 0.0f;

void __declspec(naked) GenericZeroFloat()
{	
	__asm
	{
		movss xmm0, [Zero]
		movss xmm1, [Zero]
		ret
	}
}

void __declspec(naked) SpeedHook()
{
	__asm
	{
		movss xmm1, [cVars::speed_mult]
		movss xmm0, [edi + 0x870]
		ret
	}
}

void __declspec(naked) ObjectManagerFrameAdvance()
{
	__asm
	{
		mov eax, [ebx+0x0C]
		mov ecx, [eax+0x24]
		pushad
	}

	Aimbot::Think();

	__asm
	{
		popad
		ret
	}
}

void Patches::Apply(CPatchManager* Manager)
{
	Manager->Patch<CPatch>(ImageBase+0x3D225, (uintptr_t)GenericZeroFloat, CODE_CALL, 5);			//Spread
	Manager->Patch<CPatch>(ImageBase+0x398AA, (uintptr_t)GenericZeroFloat, CODE_CALL, 5);			//Recoil

	Manager->Patch<CPatch>(ImageBase+0x3C7B4, (uintptr_t)SpeedHook, CODE_CALL, 12);					//Speedhack
	Manager->Patch<CPatch>(ImageBase+0x1D508, (uintptr_t)GenericZeroFloat, CODE_CALL, 6);			//Reload Speed

	Manager->Patch<CPatch>(ImageBase+0xFD8D0, (uintptr_t)ObjectManagerFrameAdvance, CODE_CALL, 6);	//Frame Advance
}