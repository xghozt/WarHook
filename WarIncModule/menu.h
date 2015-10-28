#pragma once

#include <vector>
#include <string.h>

class MenuItem
{
public:
	float *m_value, m_min, m_max;

	std::string m_name;
	std::string m_description;

	MenuItem(std::string name, std::string description, float* variable, float min, float max)
	{
		m_name = name;
		m_description = description;
		m_value = variable;
		m_min = min;
		m_max = max;
	}

	bool Bool()
	{
		return *m_value != 0;
	}

	float Get()
	{
		return *m_value;
	}

	const char* Description()
	{
		return m_description.c_str();
	}

	const char* Name()
	{
		return m_name.c_str();
	}
};

class CMenu
{
public:
	CMenu()
	{
		m_x = 10;
		m_y = 10;
		m_w = 100;
		bVisible = false;
	}

	void AddItem(std::string name, std::string description, float* variable, float min = 0, float max = 1);

	std::vector<MenuItem> m_items;

	std::string m_title;

	int m_x, m_y, m_w, m_h, m_bgcolor, m_spacing, m_padding, m_selecteditem;

	bool bVisible;

	void Initialize();

	void Increase();
	void Decrease();

	void NavigateUp();
	void NavigateDown();

	void Draw();
};

extern CMenu gMenu;