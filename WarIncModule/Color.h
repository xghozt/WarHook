#pragma once

#include <stdint.h>

//ARGB Color
class Color
{
public:
	union
	{
		struct
		{
			unsigned char b;
			unsigned char g;
			unsigned char r;
			unsigned char a;
		};
		uint32_t c;
	};

public:
	Color(const uint32_t inputColor)
	{
		c = inputColor;
	}

	Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha=255)
	{
		a = alpha;
		r = red;
		g = green;
		b = blue;
	}

	Color Lerp(Color approach, float perc)
	{
		perc = perc < 0 ? 0 : (perc > 1 ? 1 : perc);

		Color newColor = Color(0, 0, 0, 0);
		newColor.r = this->r*(1 - perc) + approach.r*perc;
		newColor.g = this->g*(1 - perc) + approach.g*perc;
		newColor.b = this->b*(1 - perc) + approach.b*perc;
		newColor.a = this->a*(1 - perc) + approach.a*perc;

		return newColor;
	}
};

#define color_white		Color(255, 255, 255)
#define color_teal		Color(0, 170, 255)
#define color_black		Color(0, 0, 0)
#define color_green		Color(0, 255, 0)
#define color_red		Color(255, 0, 0)
#define color_lightred	Color(255, 150, 150)