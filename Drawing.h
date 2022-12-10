#ifndef __DRAWING_H__
#define __DRAWING_H__

class Drawing
{
public:
	void FontInit( );
	void DrawPolygon( int, Valve::vgui::Vertex_t*, Color );
	void DrawRectRainbow( int, int, int, int, float, float& );
	void DrawCircle( int, int, int, Color );
	void MenuStringNormal( bool, bool, int, int, Color, const char*, ... );
	void MenuStringBold( bool, bool, int, int, Color, const char*, ... );
	void MenuString2( bool, bool, int, int, Color, const char*, ... );
	void String( bool, int, int, Color, const char*, ... );
	void StringNormal( bool, int, int, Color, const char*, ... );
	void BigString( bool, int, int, Color, const char*, ... );
	int Pulse( int, int, float );
	void Line( int, int, int, int, Color );
	void FilledRect( int, int, int, int, Color );
	void ColoredFilledRect( int, int, int, int, Color );
	void OutlinedRect( int, int, int, int, Color );
	void Circle( int, int, int, int, Color );
	void OutlinedBox( int, int, int, int, Color, Color );
	void GradientHorizontal( int, int, int, int, Color, Color, int );
	void GradientVertical( int, int, int, int, Color, Color, int );
	void Box3D( Vector*, Color );
	void DrawBones( BasePlayer*, Color );
	void DrawHitbox( BasePlayer*, int, Color );
	void DrawAimSpot( BasePlayer*, int, Color );
};
extern Drawing g_Drawing;

#endif //__DRAWING_H__
