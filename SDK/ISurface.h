/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __ISURFACE_H__
#define __ISURFACE_H__

#include "VfuncTemplates.h"
#include "Color.h"

namespace Valve
{
	namespace vgui
	{
		typedef unsigned long HFont;
		struct Vertex_t
		{
			Vertex_t( ) {}
			Vertex_t( const Vector2D &pos, const Vector2D &coord = Vector2D( 0, 0 ) )
			{
				m_Position = pos;
				m_TexCoord = coord;
			}
			Vector2D	m_Position;
			Vector2D	m_TexCoord;
		};

		enum FontDrawType_t
		{
			FONT_DRAW_DEFAULT = 0,
			FONT_DRAW_NONADDITIVE,
			FONT_DRAW_ADDITIVE,
			FONT_DRAW_TYPE_COUNT = 2,
		};

		enum EFontFlags
		{
			FONTFLAG_NONE,
			FONTFLAG_ITALIC			= 0x001,
			FONTFLAG_UNDERLINE		= 0x002,
			FONTFLAG_STRIKEOUT		= 0x004,
			FONTFLAG_SYMBOL			= 0x008,
			FONTFLAG_ANTIALIAS		= 0x010,
			FONTFLAG_GAUSSIANBLUR	= 0x020,
			FONTFLAG_ROTARY			= 0x040,
			FONTFLAG_DROPSHADOW		= 0x080,
			FONTFLAG_ADDITIVE		= 0x100,
			FONTFLAG_OUTLINE		= 0x200,
			FONTFLAG_CUSTOM			= 0x400,
			FONTFLAG_BITMAP			= 0x800,
		};

#define CLASSNAME ISurface
		class ISurface
		{
		public:
			VFUNCN2(GetScreenSize, 0x94, int&, int&);

			VFUNCN1(DrawSetColor, 0x28, Color);
			VFUNCN4(DrawSetColorRGBA, 0x2C, int, int, int, int);
			VFUNCN4(DrawFilledRect, 0x30, int, int, int, int);
			VFUNCN4(DrawOutlinedRect, 0x38, int, int, int, int);
			VFUNCN4(DrawLine, 0x3C, int, int, int, int);

			VFUNCN1(DrawSetTextFont, 0x44, HFont);
			VFUNCN1(DrawSetTextColor, 0x48, Color);
			VFUNCN4(DrawSetTextColorRGBA, 0x4C, int, int, int, int);
			VFUNCN2(DrawSetTextPos, 0x50, int, int);
			VFUNCN2(DrawGetTextPos, 0x54, int&, int&);
			VFUNCN3(DrawPrintText, 0x58, const wchar_t *, int, FontDrawType_t);
			VFUNCN4(GetTextSize, 0x120, HFont, const wchar_t *, int&, int&);
			VFUNCR0(FontCreate, 0x100, HFont);
			VFUNCR7(SetFontGlyphSet, 0x104, bool, HFont, const char*, int, int, int, int, int);

			VFUNCN4(DrawSetTextureRGBA, Index2Offset( 27 ), int, const unsigned char*, int, int );
			VFUNCN1(DrawSetTexture, Index2Offset( 28 ), int );
			VFUNCN4(DrawTexturedRect, Index2Offset( 30 ), int, int, int, int );
			VFUNCR1(IsTextureIDValid, Index2Offset( 31 ), bool, int );
			VFUNCR1(CreateNewTextureID, Index2Offset( 32 ), int, bool );
			VFUNCN4(DrawOutlinedCircle, Index2Offset( 96 ), int, int, int, int);
			VFUNCN2(DrawTexturedPolygon, Index2Offset( 99 ), int, Vertex_t* );
		};
	};
};


#endif //__ISURFACE_H__