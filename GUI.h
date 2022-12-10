#ifndef __GUI_H_
#define __GUI_H_

class GUI
{
public:
	struct tabs
	{
		int x, y, w, h, half, secondhalf;
	}tabs[ 5 ];

	struct menu
	{
		int x, y, w, h;
	}menu;

	int activetab;
	int columns[ 2 ];
	int itemheight[ 2 ];
	int itemscount;

	bool ShouldDisableInput( );
	void Slider( int, bool, int, int, int, int&, const char* );
	void Slider( int, bool, int, float, float, float&, const char* );
	void CheckBox( int, bool&, const char* );
	void PseudoCombo( int, int&, int, int, const char*, const char* );
	void ClickBox( int, bool&, const char* );
	void Section( bool, int, int, const char* );
	void Menu( int, int, int, int );
	void Radar( int, int, int, int );
	void ColorSchemes( );
	void Draw( );
};
extern GUI g_GUI;

#endif // __GUI_H_