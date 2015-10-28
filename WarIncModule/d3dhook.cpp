#include "d3dhook.h"
#include "d3drender.h"
#include "render.h"

namespace WarHook
{
	namespace D3DHook
	{
		uintptr_t* dxDeviceVMT;
		R3DRenderer* Render;

		tReset pReset = 0;
		tBeginScene pBeginScene = 0;
		tEndScene pEndScene = 0;
		tDrawIndexedPrimitive pDrawIndexedPrimitive = 0;
	}
}

bool bInit = false;

using namespace WarHook;

void D3DHook::Apply()
{
	pReset = SwapVMTIndex<tReset>(dxDeviceVMT, 16, (uintptr_t)hkReset);
	pEndScene =	SwapVMTIndex<tEndScene>(dxDeviceVMT, 42, (uintptr_t)hkEndScene);
	pBeginScene = SwapVMTIndex<tBeginScene>(dxDeviceVMT, 41, (uintptr_t)hkBeginScene);
	pDrawIndexedPrimitive = SwapVMTIndex<tDrawIndexedPrimitive>(dxDeviceVMT, 82, (uintptr_t)hkDrawIndexedPrimitive);

	FlushInstructionCache(GetCurrentProcess(), 0, 0);
}

void D3DHook::Restore()
{
	SwapVMTIndex<tReset>(dxDeviceVMT, 16, (uintptr_t)pReset);
	SwapVMTIndex<tEndScene>(dxDeviceVMT, 42, (uintptr_t)pEndScene);
	SwapVMTIndex<tBeginScene>(dxDeviceVMT, 41, (uintptr_t)pBeginScene);
	SwapVMTIndex<tDrawIndexedPrimitive>(dxDeviceVMT, 82, (uintptr_t)pDrawIndexedPrimitive);

	FlushInstructionCache(GetCurrentProcess(), 0, 0);
}

void D3DHook::Rehook()
{
	SwapVMTIndex<tReset>(dxDeviceVMT, 16, (uintptr_t)hkReset);
	SwapVMTIndex<tEndScene>(dxDeviceVMT, 42, (uintptr_t)hkEndScene);
	SwapVMTIndex<tBeginScene>(dxDeviceVMT, 41, (uintptr_t)hkBeginScene);
	SwapVMTIndex<tDrawIndexedPrimitive>(dxDeviceVMT, 82, (uintptr_t)hkDrawIndexedPrimitive);
}

long __stdcall D3DHook::hkBeginScene(IDirect3DDevice9* pDevice)
{
	if (!bInit)
	{
		Render::InitTextures(pDevice);
		bInit = true;
	}

	return pBeginScene(pDevice);
}

long __stdcall D3DHook::hkEndScene(IDirect3DDevice9* pDevice)
{
	Render::SetupFonts(pDevice);

	WarHook::Main::Render();

	return pEndScene(pDevice);
}

long __stdcall D3DHook::hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams)
{
	Render::OnLostDevice();

	long ret = pReset(pDevice, pParams);

	if (ret == D3D_OK)
		Render::OnResetDevice();

	return ret;
}

uint32_t Stride;

long __stdcall D3DHook::hkDrawIndexedPrimitive(IDirect3DDevice9* pDevice, D3DPRIMITIVETYPE PrimitiveType, int BaseVertexIndex, uint32_t MinVertexIndex, uint32_t NumVertices, uint32_t startIndex, uint32_t primCount)
{
	IDirect3DVertexBuffer9* StreamData;
	uint32_t OffsetInBytes;

	if (pDevice->GetStreamSource(0, &StreamData, &OffsetInBytes, &Stride) == D3D_OK)
		if (StreamData)
			StreamData->Release();
	
	if (Stride == 32)
	{
		DWORD dwOldZEnable = D3DZB_TRUE;
		pDevice->GetRenderState(D3DRS_ZENABLE, &dwOldZEnable);

		pDevice->SetTexture(0, Render::texGreen);
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

		pDrawIndexedPrimitive(pDevice, PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
		
		pDevice->SetTexture(0, Render::texBlue);
		pDevice->SetRenderState(D3DRS_ZENABLE, dwOldZEnable);
	}

	return pDrawIndexedPrimitive(pDevice, PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}