/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __COLOR_H__
#define __COLOR_H__

#include "Vector.h"
#define MENU_ALPHA 255
namespace Valve
{
	typedef struct
	{
		byte r, g, b, a;
	} color32;

	class Color
	{
	public:
		// constructors
		Color()
		{
			*((int *)this) = 0;
		}
		Color(int _r, int _g, int _b)
		{
			SetColor(_r, _g, _b, 255);
		}
		Color(int _r, int _g, int _b, int _a)
		{
			SetColor(_r, _g, _b, _a);
		}
	
		void SetColor(int _r, int _g, int _b, int _a = 0)
		{
			_color[0] = (unsigned char)_r;
			_color[1] = (unsigned char)_g;
			_color[2] = (unsigned char)_b;
			_color[3] = (unsigned char)_a;
		}

		void GetColor(int &_r, int &_g, int &_b, int &_a) const
		{
			_r = _color[0];
			_g = _color[1];
			_b = _color[2];
			_a = _color[3];
		}

		void SetRawColor( int color32 )
		{
			*((int *)this) = color32;
		}

		int GetRawColor() const
		{
			return *((int *)this);
		}
		inline Vector ToVector()
		{
			return Vector(((float)_color[0])/255.f, ((float)_color[1])/255.f, ((float)_color[2])/255.f);
		}
		inline int r()	{ return _color[0]; }
		inline int g()	{ return _color[1]; }
		inline int b()	{ return _color[2]; }
		inline int a()	{ return _color[3]; }
	
		unsigned char &operator[](int index)
		{
			return _color[index];
		}

		const unsigned char &operator[](int index) const
		{
			return _color[index];
		}

		bool operator == (const Color &rhs) const
		{
			return ( *((int *)this) == *((int *)&rhs) );
		}

		bool operator != (const Color &rhs) const
		{
			return !(operator==(rhs));
		}

		Color &operator=( const Color &rhs )
		{
			SetRawColor( rhs.GetRawColor() );
			return *this;
		}
		static Color Green()
		{
			return Color(0, 255, 0);
		}
		static Color Red()
		{
			return Color(255, 60, 60);
		}
		static Color Blue()
		{
			return Color(35, 35, 255);
		}
		static Color Black()
		{
			return Color(0, 0, 0);
		}
		static Color White()
		{
			return Color(255, 255, 255);
		}
		static Color Orange()
		{
			return Color(255, 128, 0);
		}
		static Color LightBlue()
		{
			return Color(160, 200, 255);
		}
		static Color LightPink()
		{
			return Color(255, 200, 200);
		}
		static Color Pink()
		{
			return Color(255, 0, 128);
		}
		static Color CyanBlue()
		{
			return Color(0, 255, 128);
		}
		static Color YellowGreen()
		{
			return Color(128, 255, 0);
		}
		static Color Purple()
		{
			return Color(128, 0, 255);
		}
		static Color DarkPurple()
		{
			return Color(40, 0, 145);
		}
		static Color LightPurple()
		{
			return Color(200, 160, 255);
		}
		static Color PurplePink()
		{
			return Color(255, 0, 255);
		}
		static Color Cyan()
		{
			return Color(0, 255, 255);
		}
		static Color Yellow()
		{
			return Color(255, 255, 70);
		}
		static Color MenuInner()
		{
			return Color(0, 0, 0, MENU_ALPHA);
		}
		static Color MenuOuter()
		{
			return Color(200, 160, 30, 255);
		}
		static Color HighlightedMenuInner()
		{
			return Color(145, 120, 20, MENU_ALPHA);
		}
		static Color HighlightedMenuOuter()
		{
			return Color(128, 64, 64);
		}
		static Color EspFriend()
		{
			return Color(75, 90, 40);
		}

		float Hue() const
	{
		if (_color[0] == _color[1] && _color[1] == _color[2])
		{
			return 0.0f;
		}

		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;

		if (r == max)
		{
			hue = (g - b) / delta;
		}
		else if (g == max)
		{
			hue = 2 + (b - r) / delta;
		}
		else if (b == max)
		{
			hue = 4 + (r - g) / delta;
		}
		hue *= 60;

		if (hue < 0.0f)
		{
			hue += 360.0f;
		}
		return hue;
	}

	float Saturation() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;

		if (max != min)
		{
			l = (max + min) / 2;
			if (l <= 0.5f)
				s = (max - min) / (max + min);
			else
				s = (max - min) / (2 - max - min);
		}
		return s;
	}

	float Brightness() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}

	Color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
				);
		}
		else if (h < 2)
		{
			return Color(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
				);
		}
		else if (h < 3)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
				);
		}
		else if (h < 4)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
				);
		}
		else if (h < 5)
		{
			return Color(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
				);
		}
		else
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
				);
		}
	}
	private:
		unsigned char _color[4];
	};
};

#endif // __COLOR_H__
