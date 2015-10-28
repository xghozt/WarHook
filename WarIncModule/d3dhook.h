#pragma once
#include "stdafx.h"
#include "structures.h"

typedef HRESULT(WINAPI* tReset)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
typedef HRESULT(WINAPI* tBeginScene)(IDirect3DDevice9*);
typedef HRESULT(WINAPI* tEndScene)(IDirect3DDevice9*);
typedef HRESULT(WINAPI* tDrawIndexedPrimitive)(IDirect3DDevice9*, D3DPRIMITIVETYPE, int, uint32_t, uint32_t, uint32_t, uint32_t);

namespace WarHook
{
	namespace D3DHook
	{
		extern uintptr_t* dxDeviceVMT;
		extern R3DRenderer* Render;

		extern tReset pReset;
		extern tEndScene pEndScene;
		extern tBeginScene pBeginScene;
		extern tDrawIndexedPrimitive pDrawIndexedPrimitive;

		extern void Apply();
		extern void Restore();
		extern void Rehook();

		extern long __stdcall hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams);
		extern long __stdcall hkBeginScene(IDirect3DDevice9* pDevice);
		extern long __stdcall hkEndScene(IDirect3DDevice9* pDevice);
		extern long __stdcall hkDrawIndexedPrimitive(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, int BaseVertexIndex, uint32_t MinVertexIndex, uint32_t NumVertices, uint32_t startIndex, uint32_t primCount);
	}
}