#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <windows.h>
#include <stdint.h>
#include <iostream>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#pragma warning(disable : 4244)
#pragma warning(disable : 4018)
#pragma warning(disable : 4800)
#pragma warning(disable : 4455)
#pragma warning(disable : 4305)
#pragma warning(disable : 4996)

class R3DNetwork;
class CPatchManager;

namespace WarHook 
{
	extern uint32_t ImageBase;
	extern R3DNetwork* NetworkManager;
	extern CPatchManager* PatchManager;
}

//Todo: Put this somewhere not retarded
template <typename T> T SwapVMTIndex(uintptr_t* VMT, uint32_t index, uintptr_t pPtr)
{
	T pOrig = reinterpret_cast<T>(VMT[index]);
	VMT[index] = pPtr;

	return pOrig;
}

#include "Vec3.h"
#include "Color.h"
#include "d3dhook.h"
#include "d3drender.h"