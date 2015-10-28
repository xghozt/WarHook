#include "menu.h"
#include "stdafx.h"
#include "cvars.h"

using namespace WarHook;

void CMenu::AddItem(std::string name, std::string description, float* variable, float min, float max)
{
	MenuItem Item = MenuItem(name, description, variable, min, max);

	this->m_items.push_back(Item);
}

void CMenu::Increase()
{
	MenuItem Item = m_items[m_selecteditem];

	if (Item.Get() < Item.m_max)
		*Item.m_value += 1;
}

void CMenu::Decrease()
{
	MenuItem Item = m_items[m_selecteditem];

	if (Item.Get() > Item.m_min)
		*Item.m_value -= 1;
}

void CMenu::NavigateUp()
{
	if (this->m_selecteditem > 0)
		this->m_selecteditem--;
	else
		this->m_selecteditem = m_items.size() - 1;
}

void CMenu::NavigateDown()
{
	if (this->m_selecteditem < m_items.size() - 1)
		this->m_selecteditem++;
	else
		this->m_selecteditem = 0;
}

void CMenu::Initialize()
{
	m_x = 10;
	m_y = 300;
	m_w = 210;
	m_bgcolor = 30;
	m_spacing = 21;
	m_padding = 5;

	m_title = "WarHook";

	AddItem("Aimbot",			"You aim, you shoot, you kill.",											&cVars::aimbot);
	AddItem("ESP",				"Shows players through the wall with additional information.",				&cVars::esp);
	AddItem("ESP Skeleton",		"Shows a wireframe skeletal structure of players through the wall.",		&cVars::esp_skeleton);
	AddItem("ESP Health",		"Diplays a health bar below the bounding box drawn for players.",			&cVars::esp_health);
	AddItem("ESP Team",			"Determines whether or not your team members should show on the esp.",		&cVars::esp_team);
	AddItem("ESP Weapon",		"Display the currently equipped weapon of players on the esp.",				&cVars::esp_weapon);

	AddItem("No Recoil",		"Removes the recoil that firing your weapons applies.",						&cVars::norecoil);
	AddItem("No Spread",		"Removes the spread that firing your weapons applies.",						&cVars::nospread);
	AddItem("Instant Reload",	"Removes the delay imposed by reloading your weapon.",						&cVars::noreload);

	AddItem("Speed Multiplier",	"This value is the amount that your movement speed will be multiplied by.", &cVars::speed_mult, 1, 10);
	AddItem("Jump Height",		"When you jump, this is the magnitude applied..",							&cVars::jumpheight, 17, 100);
	AddItem("Debug",			"Let's get to work, betty!",												&cVars::showdebug);

	m_h = m_items.size() * m_spacing;
}

uint32_t colSelected = D3DCOLOR_ARGB(255, 0, 195, 255);
uint32_t colMain = D3DCOLOR_ARGB(255, 255, 255, 255);

void CMenu::Draw()
{
	Render::SetFont(Render::pMenuFont);

	Render::FillRGB(m_x, m_y - 22, m_w, 18, Color(0, 0, 0, 150));
	Render::FillRGB(m_x, m_y, m_w, m_h, Color(0, 0, 0, 150));

	Render::DrawTextOutlined(m_x + m_padding, m_y - 22, m_title, color_white, DT_LEFT);

	for (int i = 0; i < m_items.size(); i++)
	{
		MenuItem Item = m_items[i];

		int y_offset = i * m_spacing;

		uint32_t color = i == m_selecteditem ? colSelected : colMain;

		Render::DrawTextA(m_x + m_padding, m_y + y_offset, color, DT_LEFT, "%s", Item.Name());
		Render::DrawTextA(m_x + m_w - m_padding, m_y + y_offset, color, DT_RIGHT, "%.1f", Item.Get());
	}

	MenuItem CurrentItem = m_items[m_selecteditem];

	Render::DrawTextOutlined(m_x, m_y + m_h + m_spacing, CurrentItem.Description(), color_white, DT_LEFT);
	Render::DrawTextA(m_x, m_y + m_h + m_spacing * 2, color_white, DT_LEFT, "Min: %.1f; Max: %.1f", CurrentItem.m_min, CurrentItem.m_max);

	Render::ResetFont();
}

CMenu gMenu;