#pragma once
#include "stdafx.h"

namespace WarHook
{
	namespace Render
	{
		extern void SetupFonts(IDirect3DDevice9* pDevice);

		extern void DrawString(int x, int y, std::string text, Color color, uint32_t flags = 0);
		extern void DrawTextOutlined(int x, int y, std::string text, Color color, uint32_t flags = 0);
		extern void DrawText(int x, int y, Color color, uint32_t flags, char* String, ...);
		
		extern void FillRGB(int x, int y, int w, int h, Color color);
		extern void DrawOutlinedRect(int x, int y, int width, int height, Color color);
		extern void DrawLine(int x1, int y1, int x2, int y2, Color color);

		extern bool WorldToScreen(Vec3 &Out, Vec3 In);

		extern void SetFont(ID3DXFont* Font);
		extern void ResetFont();

		extern void OnLostDevice();
		extern void OnResetDevice();

		void InitTextures(IDirect3DDevice9 *pDevice);

		extern ID3DXFont* pMainFont;
		extern ID3DXFont* pMenuFont;
		extern ID3DXFont* pCurrentFont;
		extern ID3DXLine* pLine;

		extern IDirect3DTexture9* texGreen;
		extern IDirect3DTexture9* texBlue;
	}
}