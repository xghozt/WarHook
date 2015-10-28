#include "d3drender.h"

using namespace WarHook;

struct D3DVertex {
	float x, y, z, rhw;
	DWORD color;
};

ID3DXLine* Render::pLine = 0;
ID3DXFont* Render::pMainFont = 0;
ID3DXFont* Render::pMenuFont = 0;
ID3DXFont* Render::pCurrentFont = 0;

IDirect3DTexture9* Render::texGreen;
IDirect3DTexture9* Render::texBlue;

//Credits; tim0n
long GenerateTexture(IDirect3DDevice9 *pDevice, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if (pDevice->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL < 0))
		return E_FAIL;

	uint16_t colour16 = 
		  (uint16_t)(((colour32 >> 28) & 0xF) << 12)
		| (uint16_t)(((colour32 >> 20) & 0xF) << 8)
		| (uint16_t)(((colour32 >> 12) & 0xF) << 4)
		| (uint16_t)(((colour32 >> 4)  & 0xF) << 0);

	D3DLOCKED_RECT d3dlr;

	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);

	WORD *pDst16 = (WORD*)d3dlr.pBits;

	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;

	(*ppD3Dtex)->UnlockRect(0);

	return S_OK;
}

void Render::InitTextures(IDirect3DDevice9 *pDevice)
{
	GenerateTexture(pDevice, &texGreen, D3DCOLOR_ARGB(255, 0, 200, 0));
	GenerateTexture(pDevice, &texBlue, D3DCOLOR_ARGB(255, 0, 0, 200));
}

void Render::SetupFonts(IDirect3DDevice9* pDevice)
{
	if (!pMainFont)
		D3DXCreateFontA(pDevice, 12, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pMainFont);

	if (!pMenuFont)
		D3DXCreateFontA(pDevice, 16, 0, FW_NORMAL, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Tahoma", &pMenuFont);

	pCurrentFont = pMainFont;

	if (!pLine)
		D3DXCreateLine(pDevice, &pLine);
}

void Render::OnLostDevice()
{
	if (pMainFont)
		pMainFont->OnLostDevice();

	if (pMenuFont)
		pMenuFont->OnLostDevice();

	if (pLine)
		pLine->OnLostDevice();
}

void Render::OnResetDevice()
{
	if (pMainFont)
		pMainFont->OnResetDevice();

	if (pMenuFont)
		pMenuFont->OnResetDevice();

	if (pLine)
		pLine->OnResetDevice();
}

void Render::SetFont(ID3DXFont* Font)
{
	pCurrentFont = Font;
}

void Render::ResetFont()
{
	pCurrentFont = pMainFont;
}

void Render::DrawString(int x, int y, std::string text, Color color, uint32_t flags)
{
	RECT rect;
	SetRect(&rect, x, y, x, y);

	pCurrentFont->DrawTextA(0, text.c_str(), text.length(), &rect, DT_NOCLIP | flags, color.c);
}

void Render::DrawTextOutlined(int x, int y, std::string text, Color color, uint32_t flags)
{
	Color black = Color(0, 0, 0, 255);

	DrawString(x + 1, y, text, black, flags);
	DrawString(x - 1, y, text, black, flags);
	DrawString(x, y + 1, text, black, flags);
	DrawString(x, y - 1, text, black, flags);

	DrawString(x - 1, y - 1, text, black, flags);
	DrawString(x + 1, y - 1, text, black, flags);
	DrawString(x - 1, y + 1, text, black, flags);
	DrawString(x + 1, y + 1, text, black, flags);

	DrawString(x, y, text, color, flags);
}

void Render::DrawText(int x, int y, Color color, uint32_t flags, char* String, ...)
{
	char Buffer[1024];

	va_list va;

	va_start(va, String);
		vsprintf_s(Buffer, String, va);
	va_end(va);

	DrawTextOutlined(x, y, Buffer, color, flags);
}

void Render::FillRGB(int x, int y, int w, int h, Color color)
{
	D3DRECT rec = { x, y, x + w, y + h };
	D3DHook::Render->m_pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color.c, 0, 0);
}

void Render::DrawLine(int x1, int y1, int x2, int y2, Color color)
{
	D3DXVECTOR2 dLine[2];

	dLine[0].x = x1;
	dLine[0].y = y1;

	dLine[1].x = x2;
	dLine[1].y = y2;

	pLine->SetWidth(1);
	pLine->Draw(dLine, 2, color.c);
}

void Render::DrawOutlinedRect(int x, int y, int width, int height, Color color)
{
	DrawLine(x, y, x+width, y, color.c);
	DrawLine(x, y, x, y+height, color.c);

	DrawLine(x, y+height, x+width, y+height, color.c);
	DrawLine(x+width, y, x+width, y+height, color.c);
}

//Todo: Write my own WorldToScreen function
bool Render::WorldToScreen(Vec3 &vecOut, Vec3 vecIn)
{
	int retv = 0;

	uintptr_t adr = ImageBase + 0x181960;

	__asm {
		mov edi, vecOut
		lea esi, vecIn
		call[adr]
		mov[retv], eax
	}

	return retv;
}