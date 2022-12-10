#include "Main.h"

GUI g_GUI;

bool GUI::ShouldDisableInput( )
{
	if( bMouse )
	{
		if( GetAsyncKeyState( VK_LBUTTON ) ) return true;
		else if( GetAsyncKeyState( VK_RBUTTON ) ) return true;
		else return false;
	}
	else return false;
}

void GUI::Slider( int column, bool active, int width, int min, int max, int &value, const char* name )
{
	itemheight[ column ] += 16;

	if( column == 0 )
	{
		int x = columns[ column ] + 12;

		g_Drawing.MenuStringNormal( false, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) + tabs[ 2 ].w - 43, itemheight[ column ] + 7, Color( 255, 255, 255, 200 ), /*%s: %i*/XorStr<0x31,7,0x92B43402>("\x14\x41\x09\x14\x10\x5F"+0x92B43402).s, name, value );

		width += 10;

		int barheight = 15;

		if( value > max ) value = max;
		if( value < min ) value = min;
	
		if( active )
		{
			if( g_Stuff.Mouse.Hold( x - 3, itemheight[ column ], width + 6, 16 ) ) 
			{
				value = ( mouse_x - x ) * ( max - min ) / width;
				if( value > max ) value = max;
				if( value < min ) value = min;
			}
		}

		int valueX = x + ( ( value - min ) * width / ( max - min ) );
		int val = valueX - x;

		int col = 80;
		g_Drawing.FilledRect( x, itemheight[ column ], width, 1, Color( col, col, col, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 1, width, 1, Color( col - 2, col - 2, col - 2, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 2, width, 1, Color( col - 4, col - 4, col - 4, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 3, width, 1, Color( col - 8, col - 8, col - 8, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 4, width, 1, Color( col - 12, col - 12, col - 12, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 5, width, 1, Color( col - 14, col - 14, col - 14, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 6, width, 9, Color( col - 16, col - 16, col - 16, 255 ) );

		g_Drawing.GradientHorizontal( x, itemheight[ column ], val, barheight, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );

		g_Drawing.OutlinedRect( x, itemheight[ column ], width, barheight, Color( 51, 51, 51, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ], width - 1, 1, Color( 91, 91, 91, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ], 1, 14, Color( 91, 91, 91, 255 ) );
	}
	else if( column == 1 )
	{
		int x = columns[ column ] + 12;

		g_Drawing.MenuStringNormal( false, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) + tabs[ 2 ].w - 47, itemheight[ column ] + 7, Color( 255, 255, 255, 200 ), /*%s: %i*/XorStr<0x31,7,0x92B43402>("\x14\x41\x09\x14\x10\x5F"+0x92B43402).s, name, value );

		width += 10;

		int barheight = 15;

		if( value > max ) value = max;
		if( value < min ) value = min;
	
		if( active )
		{
			if( g_Stuff.Mouse.Hold( x - 3, itemheight[ column ], width + 6, 16 ) ) 
			{
				value = ( mouse_x - x ) * ( max - min ) / width;
				if( value > max ) value = max;
				if( value < min ) value = min;
			}
		}

		int valueX = x + ( ( value - min ) * width / ( max - min ) );
		int val = valueX - x;

		int col = 80;
		g_Drawing.FilledRect( x, itemheight[ column ], width, 1, Color( col, col, col, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 1, width, 1, Color( col - 2, col - 2, col - 2, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 2, width, 1, Color( col - 4, col - 4, col - 4, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 3, width, 1, Color( col - 8, col - 8, col - 8, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 4, width, 1, Color( col - 12, col - 12, col - 12, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 5, width, 1, Color( col - 14, col - 14, col - 14, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 6, width, 9, Color( col - 16, col - 16, col - 16, 255 ) );

		g_Drawing.GradientHorizontal( x, itemheight[ column ], val, barheight, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );

		g_Drawing.OutlinedRect( x, itemheight[ column ], width, barheight, Color( 51, 51, 51, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ], width - 1, 1, Color( 91, 91, 91, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ], 1, 14, Color( 91, 91, 91, 255 ) );
	}

	itemscount++;
}

void GUI::Slider( int column, bool active, int width, float min, float max, float &value, const char* name )
{
	itemheight[ column ] += 16;

	if( column == 0 )
	{
		int x = columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36;

		g_Drawing.MenuStringNormal( false, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) + tabs[ 2 ].w - 43, itemheight[ column ] + 7, Color( 255, 255, 255, 200 ), /*%s: %.1f*/XorStr<0x42,9,0x308A5774>("\x67\x30\x7E\x65\x63\x69\x79\x2F"+0x308A5774).s, name, value );

		width += 11;

		int barheight = 15;

		if( value > max ) value = max;
		if( value < min ) value = min;
	
		if( active )
		{
			if( g_Stuff.Mouse.Hold( x - 3, itemheight[ column ], width + 6, 16 ) ) 
			{
				value = ( mouse_x - x ) * ( max - min ) / width;
				if( value > max ) value = max;
				if( value < min ) value = min;
			}
		}

		int valueX = x + ( ( value - min ) * width / ( max - min ) );
		int val = valueX - x;

		int col = 80;
		g_Drawing.FilledRect( x, itemheight[ column ], width, 1, Color( col, col, col, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 1, width, 1, Color( col - 2, col - 2, col - 2, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 2, width, 1, Color( col - 4, col - 4, col - 4, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 3, width, 1, Color( col - 8, col - 8, col - 8, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 4, width, 1, Color( col - 12, col - 12, col - 12, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 5, width, 1, Color( col - 14, col - 14, col - 14, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 6, width, 9, Color( col - 16, col - 16, col - 16, 255 ) );

		g_Drawing.GradientHorizontal( x, itemheight[ column ], val, barheight, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );

		g_Drawing.OutlinedRect( x, itemheight[ column ], width, barheight, Color( 51, 51, 51, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ], width - 1, 1, Color( 91, 91, 91, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ], 1, 14, Color( 91, 91, 91, 255 ) );
	}
	else if( column == 1 )
	{
		int x = columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40;

		g_Drawing.MenuStringNormal( false, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) + tabs[ 2 ].w - 47, itemheight[ column ] + 7, Color( 255, 255, 255, 200 ), /*%s: %.1f*/XorStr<0x42,9,0x308A5774>("\x67\x30\x7E\x65\x63\x69\x79\x2F"+0x308A5774).s, name, value );

		width += 10;

		int barheight = 15;

		if( value > max ) value = max;
		if( value < min ) value = min;
	
		if( active )
		{
			if( g_Stuff.Mouse.Hold( x - 3, itemheight[ column ], width + 6, 16 ) ) 
			{
				value = ( mouse_x - x ) * ( max - min ) / width;
				if( value > max ) value = max;
				if( value < min ) value = min;
			}
		}

		int valueX = x + ( ( value - min ) * width / ( max - min ) );
		int val = valueX - x;

		int col = 80;
		g_Drawing.FilledRect( x, itemheight[ column ], width, 1, Color( col, col, col, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 1, width, 1, Color( col - 2, col - 2, col - 2, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 2, width, 1, Color( col - 4, col - 4, col - 4, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 3, width, 1, Color( col - 8, col - 8, col - 8, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 4, width, 1, Color( col - 12, col - 12, col - 12, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 5, width, 1, Color( col - 14, col - 14, col - 14, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ] + 6, width, 9, Color( col - 16, col - 16, col - 16, 255 ) );

		g_Drawing.GradientHorizontal( x, itemheight[ column ], val, barheight, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );

		g_Drawing.OutlinedRect( x, itemheight[ column ], width, barheight, Color( 51, 51, 51, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ], width - 1, 1, Color( 91, 91, 91, 255 ) );
		g_Drawing.FilledRect( x, itemheight[ column ], 1, 14, Color( 91, 91, 91, 255 ) );
	}

	itemscount++;
}

void GUI::CheckBox( int column, bool& var, const char* name )
{
	itemheight[ column ] += 16;

	if( column == 0 )
	{
		g_Drawing.FilledRect( columns[ column ] + 16, itemheight[ column ] + 3, 9, 9, g_CVars.Colors.tabs_fill );

		if( g_Stuff.Mouse.IsInBox( columns[ column ] + 13, itemheight[ column ], 15, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + 16, itemheight[ column ] + 3, 9, 9, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
		else g_Drawing.OutlinedRect( columns[ column ] + 16, itemheight[ column ] + 3, 9, 9, Color::Black( ) );

		if( g_Stuff.Mouse.Click( columns[ column ] + 13, itemheight[ column ], 15, 15 ) ) var = !var;
		if( var ) g_Drawing.GradientHorizontal( columns[ column ] + 17, itemheight[ column ] + 4, 7, 7, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );
		g_Drawing.MenuStringNormal( false, true, columns[ column ] + 33, itemheight[ column ] + 7, Color( 200, 200, 200 ), name );
	}
	else if( column == 1 )
	{
		g_Drawing.FilledRect( columns[ column ] + 12, itemheight[ column ] + 3, 9, 9, g_CVars.Colors.tabs_fill );

		if( g_Stuff.Mouse.IsInBox( columns[ column ] + 9, itemheight[ column ], 15, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + 12, itemheight[ column ] + 3, 9, 9, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
		else g_Drawing.OutlinedRect( columns[ column ] + 12, itemheight[ column ] + 3, 9, 9, Color::Black( ) );

		if( g_Stuff.Mouse.Click( columns[ column ] + 9, itemheight[ column ], 15, 15 ) ) var = !var;
		if( var ) g_Drawing.GradientHorizontal( columns[ column ] + 13, itemheight[ column ] + 4, 7, 7, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );
		g_Drawing.MenuStringNormal( false, true, columns[ column ] + 29, itemheight[ column ] + 7, Color( 200, 200, 200 ), name );
	}

	itemscount++;
}

void GUI::PseudoCombo( int column, int& var, int min, int max, const char* name, const char* value )
{
	if( column == 0 )
	{
		itemheight[ column ] += 16;
		g_Drawing.MenuStringNormal( false, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) + tabs[ 2 ].w - 43, itemheight[ 0 ] + 7, Color( 200, 200, 200 ), name );

		if( g_Stuff.Mouse.Click( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 15, 15 ) )
		{
			var++;
			if( var > max ) var = min;
		}

		if( g_Stuff.Mouse.RightClick( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 15, 15 ) )
		{
			var--;
			if( var < min ) var = max;
		}

		int col = 80;
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 15, 1, Color( col, col, col, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 1, tabs[ 2 ].w - 15, 1, Color( col - 2, col - 2, col - 2, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 2, tabs[ 2 ].w - 15, 1, Color( col - 4, col - 4, col - 4, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 3, tabs[ 2 ].w - 15, 1, Color( col - 8, col - 8, col - 8, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 4, tabs[ 2 ].w - 15, 1, Color( col - 12, col - 12, col - 12, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 5, tabs[ 2 ].w - 15, 1, Color( col - 14, col - 14, col - 14, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 6, tabs[ 2 ].w - 15, 9, Color( col - 16, col - 16, col - 16, 255 ) );

		if( g_Stuff.Mouse.IsInBox( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 15, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 15, 15, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
		if( g_Stuff.Mouse.Click( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 15, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 15, 15, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );

		g_Drawing.MenuStringNormal( true, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36 + ( ( tabs[ 2 ].w - 15 ) / 2 ), itemheight[ column ] + 7, Color( 200, 200, 200 ), value );
		g_Drawing.OutlinedRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 15, 15, Color( 51, 51, 51, 255 ) );

		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w - 16, 1, Color( 91, 91, 91, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], 1, 14, Color( 91, 91, 91, 255 ) );
	}
	else if( column == 1 )
	{
		itemheight[ column ] += 16;
		g_Drawing.MenuStringNormal( false, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) + tabs[ 2 ].w - 47, itemheight[ column ] + 7, Color( 200, 200, 200 ), name );

		if( g_Stuff.Mouse.Click( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 15, 15 ) )
		{
			var++;
			if( var > max ) var = min;
		}

		if( g_Stuff.Mouse.RightClick( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 15, 15 ) )
		{
			var--;
			if( var < min ) var = max;
		}

		int col = 80;
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 15, 1, Color( col, col, col, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 1, tabs[ 4 ].w - 15, 1, Color( col - 2, col - 2, col - 2, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 2, tabs[ 4 ].w - 15, 1, Color( col - 4, col - 4, col - 4, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 3, tabs[ 4 ].w - 15, 1, Color( col - 8, col - 8, col - 8, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 4, tabs[ 4 ].w - 15, 1, Color( col - 12, col - 12, col - 12, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 5, tabs[ 4 ].w - 15, 1, Color( col - 14, col - 14, col - 14, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 6, tabs[ 4 ].w - 15, 9, Color( col - 16, col - 16, col - 16, 255 ) );

		if( g_Stuff.Mouse.IsInBox( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 15, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 15, 15, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
		if( g_Stuff.Mouse.Click( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 15, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 15, 15, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );

		g_Drawing.MenuStringNormal( true, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40 + ( ( tabs[ 4 ].w - 15 ) / 2 ), itemheight[ column ] + 7, Color( 200, 200, 200 ), value );
		g_Drawing.OutlinedRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 15, 15, Color( 51, 51, 51, 255 ) );	

		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w - 16, 1, Color( 91, 91, 91, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], 1, 14, Color( 91, 91, 91, 255 ) );
	}

	itemscount++;
}

void GUI::ClickBox( int column, bool& var, const char* name )
{
	if( column == 0 )
	{
		itemheight[ column ] += 16;
		int halfwidth = ( tabs[ 2 ].w + 75 ) / 2;

		if( g_Stuff.Mouse.Click( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 75, 15 ) )
		{
			var = !var;
		}

		if( g_Stuff.Mouse.RightClick( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 75, 15 ) )
		{
			var = !var;
		}

		int col = 80;
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 75, 1, Color( col, col, col, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 1, tabs[ 2 ].w + 75, 1, Color( col - 2, col - 2, col - 2, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 2, tabs[ 2 ].w + 75, 1, Color( col - 4, col - 4, col - 4, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 3, tabs[ 2 ].w + 75, 1, Color( col - 8, col - 8, col - 8, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 4, tabs[ 2 ].w + 75, 1, Color( col - 12, col - 12, col - 12, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 5, tabs[ 2 ].w + 75, 1, Color( col - 14, col - 14, col - 14, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ] + 6, tabs[ 2 ].w + 75, 9, Color( col - 16, col - 16, col - 16, 255 ) );

		if( g_Stuff.Mouse.IsInBox( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 75, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 75, 15, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
		if( g_Stuff.Mouse.Click( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 75, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 75, 15, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );

		g_Drawing.OutlinedRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 75, 15, Color( 51, 51, 51, 255 ) );

		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], tabs[ 2 ].w + 74, 1, Color( 91, 91, 91, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 36, itemheight[ column ], 1, 14, Color( 91, 91, 91, 255 ) );

		g_Drawing.MenuStringNormal( true, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) + halfwidth - 36, itemheight[ 0 ] + 7, Color( 200, 200, 200 ), name );
	}
	else if( column == 1 )
	{
		itemheight[ column ] += 16;
		int halfwidth = ( tabs[ 2 ].w + 75 ) / 2;

		if( g_Stuff.Mouse.Click( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 75, 15 ) )
		{
			var = !var;
		}

		if( g_Stuff.Mouse.RightClick( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 75, 15 ) )
		{
			var = !var;
		}

		int col = 80;
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 75, 1, Color( col, col, col, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 1, tabs[ 4 ].w + 75, 1, Color( col - 2, col - 2, col - 2, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 2, tabs[ 4 ].w + 75, 1, Color( col - 4, col - 4, col - 4, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 3, tabs[ 4 ].w + 75, 1, Color( col - 8, col - 8, col - 8, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 4, tabs[ 4 ].w + 75, 1, Color( col - 12, col - 12, col - 12, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 5, tabs[ 4 ].w + 75, 1, Color( col - 14, col - 14, col - 14, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ] + 6, tabs[ 4 ].w + 75, 9, Color( col - 16, col - 16, col - 16, 255 ) );

		if( g_Stuff.Mouse.IsInBox( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 75, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 75, 15, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
		if( g_Stuff.Mouse.Click( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 75, 15 ) ) g_Drawing.GradientHorizontal( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 75, 15, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );

		g_Drawing.OutlinedRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 75, 15, Color( 51, 51, 51, 255 ) );	

		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], tabs[ 4 ].w + 74, 1, Color( 91, 91, 91, 255 ) );
		g_Drawing.FilledRect( columns[ column ] + ( tabs[ 3 ].w / 2 ) - 40, itemheight[ column ], 1, 14, Color( 91, 91, 91, 255 ) );

		g_Drawing.MenuStringNormal( true, true, columns[ column ] + ( tabs[ 3 ].w / 2 ) + halfwidth - 40, itemheight[ column ] + 7, Color( 200, 200, 200 ), name );
	}

	itemscount++;
}

void GUI::Section( bool first, int column, int items, const char* name )
{
	itemscount = 0;
	if( !first ) itemheight[ column ] += 32;

	int x, y, w, h;

	g_Drawing.MenuStringNormal( true, true, columns[ column ] + tabs[ 1 ].w, itemheight[ column ] + 7, Color( 230, 230, 230 ), name );
	Color clr_ = Color( g_CVars.Colors.gui_sections.r( ), g_CVars.Colors.gui_sections.g( ), g_CVars.Colors.gui_sections.b( ), 160 );

	if( column == 0 )
	{
		x = columns[ column ] + 8;
		y = itemheight[ column ] + 7;
		w = tabs[ 1 ].w + tabs[ 2 ].w - 12;
		h = 16 * ( items + 1 );

		int wfix1 = w * .5f;
		int wfix2 = w - wfix1;
		int size1 = g_flMenuFontNormalSize * .5f;
		int size2 = g_flMenuFontNormalSize - size1;
		wfix1 -= size1 + 7;
		wfix2 -= size2;

		int xfix = x + ( w * .5f ) + size2;

		// top
		g_Drawing.FilledRect( x, y, wfix1, 1, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( x + 2, y + 1, wfix1 - 2, 1, clr_ );

		g_Drawing.FilledRect( xfix, y, wfix2, 1, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( xfix, y + 1, wfix2 - 1, 1, clr_ );

		// left
		g_Drawing.FilledRect( x, y, 1, h, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( x + 1, y + 1, 1, h - 2, clr_ );

		// right
		g_Drawing.FilledRect( x + w, y, 1, h, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( x + w - 1, y + 1, 1, h - 2, clr_ );

		// down
		g_Drawing.FilledRect( x, y + h, w + 1, 1, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( x + 1, y + h - 1, w - 1, 1, clr_ );

		//g_Drawing.OutlinedRect( columns[ column ] + 8, itemheight[ column ] + 7, tabs[ 1 ].w + tabs[ 2 ].w - 12, 16 * ( items + 1 ), Color::Black( ) );
		//g_Drawing.OutlinedRect( columns[ column ] + 9, itemheight[ column ] + 8, tabs[ 1 ].w + tabs[ 2 ].w - 14, ( 16 * ( items + 1 ) ) - 2, g_CVars.Colors.gui_sections );
	}
	else if( column == 1 )
	{
		x = columns[ column ] + 4;
		y = itemheight[ column ] + 7;
		w = tabs[ 1 ].w + tabs[ 2 ].w - 12;
		h = 16 * ( items + 1 );

		int wfix1 = w * .5f;
		int wfix2 = w - wfix1;
		int size1 = g_flMenuFontNormalSize * .5f;
		int size2 = g_flMenuFontNormalSize - size1;
		wfix1 -= size1 + 3;
		wfix2 -= size2;

		int xfix = x + ( w * .5f ) + size2 + 3;

		// top
		g_Drawing.FilledRect( x, y, wfix1, 1, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( x + 2, y + 1, wfix1 - 2, 1, clr_ );

		g_Drawing.FilledRect( xfix, y, wfix2 - 2, 1, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( xfix, y + 1, wfix2 - 3, 1, clr_ );

		// left
		g_Drawing.FilledRect( x, y, 1, h, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( x + 1, y + 1, 1, h - 2, clr_ );

		// right
		g_Drawing.FilledRect( x + w, y, 1, h, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( x + w - 1, y + 1, 1, h - 2, clr_ );

		// down
		g_Drawing.FilledRect( x, y + h, w + 1, 1, Color( 0, 0, 0, 160 ) );
		g_Drawing.FilledRect( x + 1, y + h - 1, w - 1, 1, clr_ );

		//g_Drawing.OutlinedRect( columns[ column ] + 4, itemheight[ column ] + 7, tabs[ 1 ].w + tabs[ 2 ].w - 12, 16 * ( items + 1 ), Color::Black( ) );
		//g_Drawing.OutlinedRect( columns[ column ] + 5, itemheight[ column ] + 8, tabs[ 1 ].w + tabs[ 2 ].w - 14, ( 16 * ( items + 1 ) ) - 2, g_CVars.Colors.gui_sections );
	}
}

#define LEFT 0
#define RIGHT 1

struct list_s
{
	int index;
}list_s[ 64 ];

static bool update = true;

void LoadColors( )
{
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 0 ] = g_CVars.ColorSelector.ESP.CT.r( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 1 ] = g_CVars.ColorSelector.ESP.CT.g( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 2 ] = g_CVars.ColorSelector.ESP.CT.b( );

	g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 0 ] = g_CVars.ColorSelector.ESP.TT.r( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 1 ] = g_CVars.ColorSelector.ESP.TT.g( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 2 ] = g_CVars.ColorSelector.ESP.TT.b( );

	g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 0 ] = g_CVars.ColorSelector.ESP.Wpn.r( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 1 ] = g_CVars.ColorSelector.ESP.Wpn.g( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 2 ] = g_CVars.ColorSelector.ESP.Wpn.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 0 ] = g_CVars.ColorSelector.Chams.CTVis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 1 ] = g_CVars.ColorSelector.Chams.CTVis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 2 ] = g_CVars.ColorSelector.Chams.CTVis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 0 ] = g_CVars.ColorSelector.Chams.CTInvis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 1 ] = g_CVars.ColorSelector.Chams.CTInvis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 2 ] = g_CVars.ColorSelector.Chams.CTInvis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 0 ] = g_CVars.ColorSelector.Chams.CTOutline.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 1 ] = g_CVars.ColorSelector.Chams.CTOutline.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 2 ] = g_CVars.ColorSelector.Chams.CTOutline.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 0 ] = g_CVars.ColorSelector.Chams.TTVis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 1 ] = g_CVars.ColorSelector.Chams.TTVis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 2 ] = g_CVars.ColorSelector.Chams.TTVis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 0 ] = g_CVars.ColorSelector.Chams.TTInvis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 1 ] = g_CVars.ColorSelector.Chams.TTInvis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 2 ] = g_CVars.ColorSelector.Chams.TTInvis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 0 ] = g_CVars.ColorSelector.Chams.TTOutline.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 1 ] = g_CVars.ColorSelector.Chams.TTOutline.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 2 ] = g_CVars.ColorSelector.Chams.TTOutline.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 0 ] = g_CVars.ColorSelector.Chams.WpnVis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 1 ] = g_CVars.ColorSelector.Chams.WpnVis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 2 ] = g_CVars.ColorSelector.Chams.WpnVis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 0 ] = g_CVars.ColorSelector.Chams.WpnInvis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 1 ] = g_CVars.ColorSelector.Chams.WpnInvis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 2 ] = g_CVars.ColorSelector.Chams.WpnInvis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 0 ] = g_CVars.ColorSelector.Chams.WpnOutline.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 1 ] = g_CVars.ColorSelector.Chams.WpnOutline.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 2 ] = g_CVars.ColorSelector.Chams.WpnOutline.b( );
}

void SetColors( )
{
	g_CVars.ColorSelector.ESP.CT = Color( g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 2 ], 255 );
	g_CVars.ColorSelector.ESP.TT = Color( g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 2 ], 255 );
	g_CVars.ColorSelector.ESP.Wpn = Color( g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 2 ], 255 );

	g_CVars.ColorSelector.Chams.CTVis = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 2 ], 255 );
	g_CVars.ColorSelector.Chams.CTInvis = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 2 ], 255 );
	g_CVars.ColorSelector.Chams.CTOutline = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 2 ], 255 );

	g_CVars.ColorSelector.Chams.TTVis = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 2 ], 255 );
	g_CVars.ColorSelector.Chams.TTInvis = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 2 ], 255 );
	g_CVars.ColorSelector.Chams.TTOutline = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 2 ], 255 );

	g_CVars.ColorSelector.Chams.WpnVis = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 2 ], 255 );
	g_CVars.ColorSelector.Chams.WpnInvis = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 2 ], 255 );
	g_CVars.ColorSelector.Chams.WpnOutline = Color( g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 0 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 1 ], g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 2 ], 255 );
}

void GUI::Menu( int x, int y, int w, int h )
{
	static bool Init = false;
	if( Init == false )
	{
		Init = true;
		activetab = 1;
	}

	static int titlebar = 8;
	static int tabheight = 25;

	int dragfix_x = x - 10;
	int dragfix_y = y - 10;
	int dragfix_w = w + 20;
	int dragfix_h = titlebar + 10;

	g_Stuff.Mouse.DragMenu( dragfix_x, dragfix_y, dragfix_w, dragfix_h );
	g_Drawing.FilledRect( x, y, w, h, g_CVars.Colors.gui_fill );


	g_Drawing.OutlinedRect( x, y, w, h, g_CVars.Colors.gui_outline2 ); // gui outline
	g_Drawing.OutlinedRect( x + 1, y + 1, w - 2, h - 2, g_CVars.Colors.inside_outline ); // gui outline
	//g_Drawing.OutlinedRect( x + 1, y + 1, w - 2, 1, g_CVars.Colors.maincolor );
	//g_Drawing.OutlinedRect( x + 1, y + 2, w - 2, 1, g_CVars.Colors.maincolorfade );

	/*********************************************************************************************************/

	menu.x = x + 5;
	menu.y = y + titlebar + ( ( ( h - titlebar ) - ( h - titlebar ) ) );
	menu.w = w - 10;
	menu.h = h - titlebar - 5;

	/*********************************************************************************************************/

	g_Drawing.FilledRect( menu.x, menu.y, menu.w, menu.h, g_CVars.Colors.inside_fill ); // menu fill
	//g_Drawing.FilledRect( menu.x, menu.y, menu.w, tabheight, g_CVars.Colors.tabs_fill ); // tabs fill

	/*********************************************************************************************************/

	tabs[ 1 ].x = menu.x;
	tabs[ 1 ].y = menu.y;
	tabs[ 1 ].w = ( menu.w * .25f );
	tabs[ 1 ].h = tabheight;
	tabs[ 1 ].half = tabs[ 1 ].h / 2;
	tabs[ 1 ].secondhalf = tabs[ 1 ].h - tabs[ 1 ].half;

	tabs[ 2 ].x = menu.x + ( menu.w * .25f ) - 1;
	tabs[ 2 ].y = menu.y;
	tabs[ 2 ].w = ( menu.w * .25f ) + 2;
	tabs[ 2 ].h = tabheight;
	tabs[ 2 ].half = tabs[ 2 ].h / 2;
	tabs[ 2 ].secondhalf = tabs[ 2 ].h - tabs[ 2 ].half;

	tabs[ 3 ].x = menu.x + ( menu.w * .5f ) - 1;
	tabs[ 3 ].y = menu.y;
	tabs[ 3 ].w = ( menu.w * .25f ) + 2;
	tabs[ 3 ].h = tabheight;
	tabs[ 3 ].half = tabs[ 3 ].h / 2;
	tabs[ 3 ].secondhalf = tabs[ 3 ].h - tabs[ 3 ].half;

	tabs[ 4 ].x = menu.x + ( menu.w * .75f );
	tabs[ 4 ].y = menu.y;
	tabs[ 4 ].w = ( menu.w * .25f ) + 1;
	tabs[ 4 ].h = tabheight;
	tabs[ 4 ].half = tabs[ 4 ].h / 2;
	tabs[ 4 ].secondhalf = tabs[ 4 ].h - tabs[ 4 ].half;

	/*********************************************************************************************************/

	Color maincolor_ = Color( g_CVars.Colors.maincolor.r( ), g_CVars.Colors.maincolor.g( ), g_CVars.Colors.maincolor.b( ), 160 );
	Color maincolorfade_ = Color( g_CVars.Colors.maincolorfade.r( ), g_CVars.Colors.maincolorfade.g( ), g_CVars.Colors.maincolorfade.b( ), 160 );

	for( int i = 1; i <= 4; i++ )
	{
		if( i == activetab ) continue;

		if( g_Stuff.Mouse.IsInBox( tabs[ i ].x, tabs[ i ].y, tabs[ i ].w, tabs[ i ].h ) )
		{
			g_Drawing.FilledRect( tabs[ i ].x + 5, tabs[ i ].y + tabs[ i ].h - 1, tabs[ i ].w - 10, 1, maincolor_ );
			g_Drawing.FilledRect( tabs[ i ].x + 5, tabs[ i ].y + tabs[ i ].h, tabs[ i ].w - 10, 1, maincolorfade_ );
		}
		else
		{
			g_Drawing.FilledRect( tabs[ i ].x + 5, tabs[ i ].y + tabs[ i ].h - 1, tabs[ i ].w - 10, 1, Color( 60, 60, 60, 160 ) );
			g_Drawing.FilledRect( tabs[ i ].x + 5, tabs[ i ].y + tabs[ i ].h, tabs[ i ].w - 10, 1, Color( 60, 60, 60, 160 ) );
		}
	}

	g_Drawing.FilledRect( tabs[ activetab ].x + 5, tabs[ activetab ].y + tabs[ activetab ].h - 1, tabs[ activetab ].w - 10, 1, g_CVars.Colors.maincolor );
	g_Drawing.FilledRect( tabs[ activetab ].x + 5, tabs[ activetab ].y + tabs[ activetab ].h, tabs[ activetab ].w - 10, 1, g_CVars.Colors.maincolorfade );

	// menu outline
	g_Drawing.OutlinedRect( menu.x, menu.y - 3, menu.w, menu.h + 3, g_CVars.Colors.inside_outline );

	if( g_Stuff.Mouse.Click( tabs[ 1 ].x, tabs[ 1 ].y, tabs[ 1 ].w, tabs[ 1 ].h ) ) activetab = 1;
	else if( g_Stuff.Mouse.Click( tabs[ 2 ].x, tabs[ 2 ].y, tabs[ 2 ].w, tabs[ 2 ].h ) ) activetab = 2;
	else if( g_Stuff.Mouse.Click( tabs[ 3 ].x, tabs[ 3 ].y, tabs[ 3 ].w, tabs[ 3 ].h ) ) activetab = 3;
	else if( g_Stuff.Mouse.Click( tabs[ 4 ].x, tabs[ 4 ].y, tabs[ 4 ].w, tabs[ 4 ].h ) ) activetab = 4;

	g_Drawing.MenuStringBold( true, true, tabs[ 1 ].x + tabs[ 1 ].w * .5f, tabs[ 1 ].y + tabs[ 1 ].h * .5f, Color( 230, 230, 230 ), /*Aimbot*/XorStr<0xE7,7,0x70909851>("\xA6\x81\x84\x88\x84\x98"+0x70909851).s );
	g_Drawing.MenuStringBold( true, true, tabs[ 2 ].x + tabs[ 2 ].w * .5f, tabs[ 2 ].y + tabs[ 2 ].h * .5f, Color( 230, 230, 230 ), /*Visuals*/XorStr<0x7A,8,0x7250E5DB>("\x2C\x12\x0F\x08\x1F\x13\xF3"+0x7250E5DB).s );
	g_Drawing.MenuStringBold( true, true, tabs[ 3 ].x + tabs[ 3 ].w * .5f, tabs[ 3 ].y + tabs[ 3 ].h * .5f, Color( 230, 230, 230 ), /*Miscellaneous*/XorStr<0x33,14,0x7E882478>("\x7E\x5D\x46\x55\x52\x54\x55\x5B\x55\x59\x52\x4B\x4C"+0x7E882478).s );
	g_Drawing.MenuStringBold( true, true, tabs[ 4 ].x + tabs[ 4 ].w * .5f, tabs[ 4 ].y + tabs[ 4 ].h * .5f, Color( 230, 230, 230 ), /*Player List*/XorStr<0x7A,12,0x64B98E2F>("\x2A\x17\x1D\x04\x1B\x0D\xA0\xCD\xEB\xF0\xF0"+0x64B98E2F).s );

	/*********************************************************************************************************/

	columns[ 0 ] = tabs[ 1 ].x;
	columns[ 1 ] = tabs[ 3 ].x - 1;

	if( activetab == 1 )
	{
		itemheight[ 0 ] = menu.y + tabs[ 1 ].h + 5;
		itemheight[ 1 ] = menu.y + tabs[ 1 ].h + 5;

		Section( true, LEFT, 10, /*Aimbot*/XorStr<0xBD,7,0xA4394F62>("\xFC\xD7\xD2\xA2\xAE\xB6"+0xA4394F62).s );
		CheckBox( LEFT, g_CVars.Aimbot.Active, /*Active*/XorStr<0x4D,7,0x9B85A041>("\x0C\x2D\x3B\x39\x27\x37"+0x9B85A041).s );
		CheckBox( LEFT, g_CVars.Aimbot.AutoShoot, /*Auto Shoot*/XorStr<0xDF,11,0xEDF36918>("\x9E\x95\x95\x8D\xC3\xB7\x8D\x89\x88\x9C"+0xEDF36918).s );
		CheckBox( LEFT, g_CVars.Aimbot.Silent, /*Silent*/XorStr<0x34,7,0xEB0B393B>("\x67\x5C\x5A\x52\x56\x4D"+0xEB0B393B).s );
		CheckBox( LEFT, g_CVars.Aimbot.PerfectSilent, /*Perfect Silent*/XorStr<0x1C,15,0x9CB90BFF>("\x4C\x78\x6C\x79\x45\x42\x56\x03\x77\x4C\x4A\x42\x46\x5D"+0x9CB90BFF).s );
		CheckBox( LEFT, g_CVars.Aimbot.MultiSpot, /*Multi Spot*/XorStr<0x55,11,0x0A7EC520>("\x18\x23\x3B\x2C\x30\x7A\x08\x2C\x32\x2A"+0x0A7EC520).s );
		CheckBox( LEFT, g_CVars.Aimbot.BodyAWP, /*Body AWP*/XorStr<0xC5,9,0x76FC50E1>("\x87\xA9\xA3\xB1\xE9\x8B\x9C\x9C"+0x76FC50E1).s );
		CheckBox( LEFT, g_CVars.Aimbot.HitScan, /*Hit Scan*/XorStr<0x9F,9,0x2EF0EBFC>("\xD7\xC9\xD5\x82\xF0\xC7\xC4\xC8"+0x2EF0EBFC).s );
		CheckBox( LEFT, g_CVars.Aimbot.AutoWall, /*Perfect Auto Wall*/XorStr<0x15,18,0x00FF1925>("\x45\x73\x65\x7E\x7C\x79\x6F\x3C\x5C\x6B\x6B\x4F\x01\x75\x42\x48\x49"+0x00FF1925).s );
		CheckBox( LEFT, g_CVars.Aimbot.AntiSMAC, /*Anti SMAC*/XorStr<0x45,10,0x0CEAE4D1>("\x04\x28\x33\x21\x69\x19\x06\x0D\x0E"+0x0CEAE4D1).s ); 
		CheckBox( LEFT, g_CVars.Aimbot.FriendlyFire, /*Friendly Fire*/XorStr<0x8C,14,0x2C90A980>("\xCA\xFF\xE7\xEA\xFE\xF5\xFE\xEA\xB4\xD3\xFF\xE5\xFD"+0x2C90A980).s );

		// ========================================================================================================

		Section( false, LEFT, 7, /*Triggerbot*/XorStr<0xD6,11,0xEB95B0A2>("\x82\xA5\xB1\xBE\xBD\xBE\xAE\xBF\xB1\xAB"+0xEB95B0A2).s );
		CheckBox( LEFT, g_CVars.Triggerbot.Active, /*Active*/XorStr<0x25,7,0x171FD308>("\x64\x45\x53\x41\x5F\x4F"+0x171FD308).s );
		CheckBox( LEFT, g_CVars.Triggerbot.Seed, /*Seed*/XorStr<0xF8,5,0x9416AC0C>("\xAB\x9C\x9F\x9F"+0x9416AC0C).s );
		CheckBox( LEFT, g_CVars.Triggerbot.Spread, /*Spread*/XorStr<0xB8,7,0x7268DBAE>("\xEB\xC9\xC8\xDE\xDD\xD9"+0x7268DBAE).s );
		CheckBox( LEFT, g_CVars.Triggerbot.Recoil, /*Recoil*/XorStr<0xFD,7,0xD441EA56>("\xAF\x9B\x9C\x6F\x68\x6E"+0xD441EA56).s );

		std::array< std::string, 4 > triggerstrength =
		{
			/*Low*/XorStr<0x20,4,0x5770480C>("\x6C\x4E\x55"+0x5770480C).s,
			/*Medium*/XorStr<0x39,7,0x643C7CF8>("\x74\x5F\x5F\x55\x48\x53"+0x643C7CF8).s,
			/*High*/XorStr<0x3F,5,0x802E49A5>("\x77\x29\x26\x2A"+0x802E49A5).s,
			/*Extra*/XorStr<0x3A,6,0xCF93E7E3>("\x7F\x43\x48\x4F\x5F"+0xCF93E7E3).s
		};

		PseudoCombo( LEFT, g_CVars.Triggerbot.Strength, 0, 3, /*Strength*/XorStr<0xA4,9,0x19311483>("\xF7\xD1\xD4\xC2\xC6\xCE\xDE\xC3"+0x19311483).s, triggerstrength.at( g_CVars.Triggerbot.Strength ).c_str( ) );

		std::array< std::string, 4 > triggerhitbox = { /*Head*/XorStr<0x4C,5,0x5B3E67DD>("\x04\x28\x2F\x2B"+0x5B3E67DD).s, /*Upper Body*/XorStr<0x88,11,0x06670E5D>("\xDD\xF9\xFA\xEE\xFE\xAD\xCC\xE0\xF4\xE8"+0x06670E5D).s, /*Lower Body*/XorStr<0xD5,11,0x910F775D>("\x99\xB9\xA0\xBD\xAB\xFA\x99\xB3\xB9\xA7"+0x910F775D).s, /*Full Body*/XorStr<0x77,10,0xD5FA15D3>("\x31\x0D\x15\x16\x5B\x3E\x12\x1A\x06"+0xD5FA15D3).s };
		PseudoCombo( LEFT, g_CVars.Triggerbot.Hitbox, 0, 3, /*Hitbox*/XorStr<0x52,7,0x193033A8>("\x1A\x3A\x20\x37\x39\x2F"+0x193033A8).s, triggerhitbox.at( g_CVars.Triggerbot.Hitbox ).c_str( ) );

		std::array< std::string, 6 > triggerkey = { /*Auto*/XorStr<0x36,5,0x44E3AA75>("\x77\x42\x4C\x56"+0x44E3AA75).s, /*Mouse 1*/XorStr<0xBF,8,0xB316B6F5>("\xF2\xAF\xB4\xB1\xA6\xE4\xF4"+0xB316B6F5).s, /*Mouse 2*/XorStr<0x2A,8,0x361FE457>("\x67\x44\x59\x5E\x4B\x0F\x02"+0x361FE457).s, /*Mouse 3*/XorStr<0xD3,8,0x21FCF1F6>("\x9E\xBB\xA0\xA5\xB2\xF8\xEA"+0x21FCF1F6).s, /*Mouse 4*/XorStr<0xC2,8,0x607CCE25>("\x8F\xAC\xB1\xB6\xA3\xE7\xFC"+0x607CCE25).s, /*Mouse 5*/XorStr<0xAB,8,0x90CFF5BC>("\xE6\xC3\xD8\xDD\xCA\x90\x84"+0x90CFF5BC).s };
		PseudoCombo( LEFT, g_CVars.Triggerbot.Key, 0, 5, /*Key*/XorStr<0x4D,4,0xBB57E42F>("\x06\x2B\x36"+0xBB57E42F).s, triggerkey.at( g_CVars.Triggerbot.Key ).c_str( ) );

		// ========================================================================================================

		Section( true, RIGHT, 7, /*Adjustments*/XorStr<0xB7,12,0x16426759>("\xF6\xDC\xD3\xCF\xC8\xC8\xD0\xDB\xD1\xB4\xB2"+0x16426759).s );

		std::array< std::string, 6 > aimkey = { /*Auto*/XorStr<0x36,5,0x44E3AA75>("\x77\x42\x4C\x56"+0x44E3AA75).s, /*Mouse 1*/XorStr<0xBF,8,0xB316B6F5>("\xF2\xAF\xB4\xB1\xA6\xE4\xF4"+0xB316B6F5).s, /*Mouse 2*/XorStr<0x2A,8,0x361FE457>("\x67\x44\x59\x5E\x4B\x0F\x02"+0x361FE457).s, /*Mouse 3*/XorStr<0xD3,8,0x21FCF1F6>("\x9E\xBB\xA0\xA5\xB2\xF8\xEA"+0x21FCF1F6).s, /*Mouse 4*/XorStr<0xC2,8,0x607CCE25>("\x8F\xAC\xB1\xB6\xA3\xE7\xFC"+0x607CCE25).s, /*Mouse 5*/XorStr<0xAB,8,0x90CFF5BC>("\xE6\xC3\xD8\xDD\xCA\x90\x84"+0x90CFF5BC).s };
		PseudoCombo( RIGHT, g_CVars.Aimbot.Key, 0, 5, /*Key*/XorStr<0x4D,4,0xBB57E42F>("\x06\x2B\x36"+0xBB57E42F).s, aimkey.at( g_CVars.Aimbot.Key ).c_str( ) );

		std::array< std::string, 4 > aimbothitbox = { /*Head*/XorStr<0x4B,5,0x233FDD89>("\x03\x29\x2C\x2A"+0x233FDD89).s, /*Neck*/XorStr<0x44,5,0x136015B7>("\x0A\x20\x25\x2C"+0x136015B7).s, /*Chest*/XorStr<0xFB,6,0x6BD4CC8E>("\xB8\x94\x98\x8D\x8B"+0x6BD4CC8E).s, /*Stomach*/XorStr<0x2B,8,0x0EFFCC08>("\x78\x58\x42\x43\x4E\x53\x59"+0x0EFFCC08).s };
		static int hitboxselect = 0;
		PseudoCombo( RIGHT, hitboxselect, 0, 3, /*Hitbox*/XorStr<0x30,7,0x3155BDA3>("\x78\x58\x46\x51\x5B\x4D"+0x3155BDA3).s, aimbothitbox.at( hitboxselect ).c_str( ) );

		if( hitboxselect == 0 ) g_CVars.Aimbot.Hitbox = 12;
		else if( hitboxselect == 1 ) g_CVars.Aimbot.Hitbox = 11;
		else if( hitboxselect == 2 ) g_CVars.Aimbot.Hitbox = 10;
		else if( hitboxselect == 3 ) g_CVars.Aimbot.Hitbox = 9;

		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0.0, 1.0, g_CVars.Aimbot.PointScale, /*Point Scale*/XorStr<0xDC,12,0x4B36B2CC>("\x8C\xB2\xB7\xB1\x94\xC1\xB1\x80\x85\x89\x83"+0x4B36B2CC).s );

		std::array< std::string, 5 > heightmode = { "Auto", /*Origin*/XorStr<0x8A,7,0xFF65096E>("\xC5\xF9\xE5\xEA\xE7\xE1"+0xFF65096E).s, /*Center*/XorStr<0x3F,7,0xF981A5D0>("\x7C\x25\x2F\x36\x26\x36"+0xF981A5D0).s, /*Center Fixed*/XorStr<0xA3,13,0xC029B685>("\xE0\xC1\xCB\xD2\xC2\xDA\x89\xEC\xC2\xD4\xC8\xCA"+0xC029B685).s, /*Highest*/XorStr<0xC4,8,0x84A6977A>("\x8C\xAC\xA1\xAF\xAD\xBA\xBE"+0x84A6977A).s };
		PseudoCombo( RIGHT, g_CVars.Aimbot.HitboxMode, 0, 4, /*Height Mode*/XorStr<0xAB,12,0xC635B680>("\xE3\xC9\xC4\xC9\xC7\xC4\x91\xFF\xDC\xD0\xD0"+0xC635B680).s, heightmode.at( g_CVars.Aimbot.HitboxMode ).c_str( ) );

		std::array< std::string, 4 > targetselection = { /*Distance*/XorStr<0x8B,9,0xFB02BC35>("\xCF\xE5\xFE\xFA\xEE\xFE\xF2\xF7"+0xFB02BC35).s, /*Health*/XorStr<0xC7,7,0xDFA778A4>("\x8F\xAD\xA8\xA6\xBF\xA4"+0xDFA778A4).s, /*Next Shot*/XorStr<0x61,10,0x3DD0B4E9>("\x2F\x07\x1B\x10\x45\x35\x0F\x07\x1D"+0x3DD0B4E9).s, /*Random*/XorStr<0x82,7,0x6F47C06C>("\xD0\xE2\xEA\xE1\xE9\xEA"+0x6F47C06C).s };
		PseudoCombo( RIGHT, g_CVars.Aimbot.TargetSelection, 0, 3, /*Targeting*/XorStr<0x2E,10,0xA2146379>("\x7A\x4E\x42\x56\x57\x47\x5D\x5B\x51"+0xA2146379).s, targetselection.at( g_CVars.Aimbot.TargetSelection ).c_str( ) );

		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0, 100, g_CVars.Aimbot.MinDamage, "Min Damage" );

		//CheckBox( RIGHT, g_CVars.Aimbot.Interpolation.LagPrediction, /*Interpolation Fix*/XorStr<0x3B,18,0x359A6776>("\x72\x52\x49\x5B\x4D\x30\x2E\x2E\x22\x30\x2C\x29\x29\x68\x0F\x23\x33"+0x359A6776).s );

		std::array< std::string, 3 > positionadjustment = { "Off", "On", "On + History" };
		PseudoCombo( RIGHT, g_CVars.Aimbot.Interpolation.LagPrediction, 0, 2, "Pos Adjustment", positionadjustment.at( g_CVars.Aimbot.Interpolation.LagPrediction ).c_str( ) );

		// ========================================================================================================

		Section( false, RIGHT, 3, /*Accuracy*/XorStr<0xB8,9,0x2AEAB136>("\xF9\xDA\xD9\xCE\xCE\xDC\xDD\xC6"+0x2AEAB136).s );
		CheckBox( RIGHT, g_CVars.Accuracy.PerfectAccuracy, /*Remove Recoil/Spread*/XorStr<0x31,21,0x30357A82>("\x63\x57\x5E\x5B\x43\x53\x17\x6A\x5C\x59\x54\x55\x51\x11\x6C\x30\x33\x27\x22\x20"+0x30357A82).s );
		CheckBox( RIGHT, g_CVars.Accuracy.ForceSeed, /*Force Seed*/XorStr<0x42,11,0x2720C7CA>("\x04\x2C\x36\x26\x23\x67\x1B\x2C\x2F\x2F"+0x2720C7CA).s );

		std::array< std::string, 4 > spreadmode = { /*NULL*/XorStr<0x65,5,0xA4FCA922>("\x2B\x33\x2B\x24"+0xA4FCA922).s, /*Classic*/XorStr<0x69,8,0x1214F6FA>("\x2A\x06\x0A\x1F\x1E\x07\x0C"+0x1214F6FA).s, /*Iterative*/XorStr<0x47,10,0xAD9B0D80>("\x0E\x3C\x2C\x38\x2A\x38\x24\x38\x2A"+0xAD9B0D80).s, "Rotation" };
		PseudoCombo( RIGHT, g_CVars.Accuracy.NoSpreadMode, 1, 3, /*Spread Mode*/XorStr<0xAB,12,0x78CA5E5B>("\xF8\xDC\xDF\xCB\xCE\xD4\x91\xFF\xDC\xD0\xD0"+0x78CA5E5B).s, spreadmode.at( g_CVars.Accuracy.NoSpreadMode ).c_str( ) );

		// ========================================================================================================

		Section( false, RIGHT, 3, /*Snap Limiter*/XorStr<0xBF,13,0xB888C3CE>("\xEC\xAE\xA0\xB2\xE3\x88\xAC\xAB\xAE\xBC\xAC\xB8"+0xB888C3CE).s );
		CheckBox( RIGHT, g_CVars.Aimbot.SnapLimiter, /*Active*/XorStr<0xB3,7,0x0C913435>("\xF2\xD7\xC1\xDF\xC1\xDD"+0x0C913435).s );

		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0, 180, g_CVars.Aimbot.AngleLimit, /*Limit*/XorStr<0x40,6,0x93E506EA>("\x0C\x28\x2F\x2A\x30"+0x93E506EA).s );
		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0.0, 1.0, g_CVars.Aimbot.AngleLimitTens, /*Limit Tens*/XorStr<0x19,11,0x35A31129>("\x55\x73\x76\x75\x69\x3E\x4B\x45\x4F\x51"+0x35A31129).s );

		// ========================================================================================================

		Section( false, RIGHT, 4, /*Resolver*/XorStr<0xE5,9,0xFFF99FBB>("\xB7\x83\x94\x87\x85\x9C\x8E\x9E"+0xFFF99FBB).s );
		CheckBox( RIGHT, g_CVars.Aimbot.Resolver.Active, /*Active*/XorStr<0x64,7,0xA8A8E422>("\x25\x06\x12\x0E\x1E\x0C"+0xA8A8E422).s );

		std::array< std::string, 2 > resolvermode = { /*Everyone*/XorStr<0xA3,9,0xF4C70D49>("\xE6\xD2\xC0\xD4\xDE\xC7\xC7\xCF"+0xF4C70D49).s, /*Selected*/XorStr<0x59,9,0x53DE718B>("\x0A\x3F\x37\x39\x3E\x2A\x3A\x04"+0x53DE718B).s };
		PseudoCombo( RIGHT, g_CVars.Aimbot.Resolver.Mode, 0, 1, /*Target*/XorStr<0x5F,7,0x095BEB01>("\x0B\x01\x13\x05\x06\x10"+0x095BEB01).s, resolvermode.at( g_CVars.Aimbot.Resolver.Mode ).c_str( ) );

		std::array< std::string, 5 > resolvertype = { /*Spin*/XorStr<0x89,5,0x32275D09>("\xDA\xFA\xE2\xE2"+0x32275D09).s,
			/*Back Twitch*/XorStr<0x3D,12,0x0304ECA3>("\x7F\x5F\x5C\x2B\x61\x16\x34\x2D\x31\x25\x2F"+0x0304ECA3).s,
			/*Alternative*/XorStr<0xC4,12,0x1C1C37E0>("\x85\xA9\xB2\xA2\xBA\xA7\xAB\xBF\xA5\xBB\xAB"+0x1C1C37E0).s,
			"2 bullets",
			"" };
		PseudoCombo( RIGHT, g_CVars.Aimbot.Resolver.Type, 0, 3, /*Type*/XorStr<0x34,5,0x62256357>("\x60\x4C\x46\x52"+0x62256357).s, resolvertype.at( g_CVars.Aimbot.Resolver.Type ).c_str( ) );

		CheckBox( RIGHT, g_CVars.Aimbot.Resolver.Smart, /*Smart*/XorStr<0xA0,6,0x76FE69A0>("\xF3\xCC\xC3\xD1\xD0"+0x76FE69A0).s );

		// ========================================================================================================

		if( itemheight[ 0 ] > itemheight[ 1 ] ) g_CVars.Menu.h = itemheight[ 0 ] - menu.y + 44;
		else if( itemheight[ 1 ] > itemheight[ 0 ] ) g_CVars.Menu.h = itemheight[ 1 ] - menu.y + 44;
	}

	// ========================================================================================================

	if( activetab == 2 )
	{
		itemheight[ 0 ] = menu.y + tabs[ 1 ].h + 5;
		itemheight[ 1 ] = menu.y + tabs[ 1 ].h + 5;

		Section( true, LEFT, 9, /*ESP*/XorStr<0x4B,4,0xCC12A5D5>("\x0E\x1F\x1D"+0xCC12A5D5).s );
		CheckBox( LEFT, g_CVars.Visuals.ESP.Box, /*Box*/XorStr<0xD0,4,0x1EA294EE>("\x92\xBE\xAA"+0x1EA294EE).s );
		CheckBox( LEFT, g_CVars.Visuals.ESP.Name, /*Name*/XorStr<0x3A,5,0x9FB67974>("\x74\x5A\x51\x58"+0x9FB67974).s );
		CheckBox( LEFT, g_CVars.Visuals.ESP.Health, /*Health*/XorStr<0xA5,7,0xF15B6294>("\xED\xC3\xC6\xC4\xDD\xC2"+0xF15B6294).s );
		CheckBox( LEFT, g_CVars.Visuals.ESP.Weapon, /*Weapon*/XorStr<0x81,7,0xFEB7B46E>("\xD6\xE7\xE2\xF4\xEA\xE8"+0xFEB7B46E).s );
		CheckBox( LEFT, g_CVars.Visuals.ESP.Bone, /*Bone*/XorStr<0x12,5,0x430B3235>("\x50\x7C\x7A\x70"+0x430B3235).s );
		CheckBox( LEFT, g_CVars.Visuals.ESP.AimSpot, /*Aim Spot*/XorStr<0xD4,9,0xC1136F55>("\x95\xBC\xBB\xF7\x8B\xA9\xB5\xAF"+0xC1136F55).s );
		CheckBox( LEFT, g_CVars.Visuals.ESP.Hit, "Hitmarker" );
		CheckBox( LEFT, g_CVars.Visuals.ESP.Ground, /*Ground*/XorStr<0xD2,7,0xE06C9E7E>("\x95\xA1\xBB\xA0\xB8\xB3"+0xE06C9E7E).s );
		CheckBox( LEFT, g_CVars.Visuals.ESP.EnemyOnly, /*Enemy Only*/XorStr<0x5E,11,0xF3DB2F3B>("\x1B\x31\x05\x0C\x1B\x43\x2B\x0B\x0A\x1E"+0xF3DB2F3B).s );
		
		// ========================================================================================================

		Section( false, LEFT, 6, /*Chams*/XorStr<0x1E,6,0x213736E5>("\x5D\x77\x41\x4C\x51"+0x213736E5).s );
		CheckBox( LEFT, g_CVars.Visuals.Chams.Active, /*Players*/XorStr<0xB0,8,0x8917C060>("\xE0\xDD\xD3\xCA\xD1\xC7\xC5"+0x8917C060).s );
		CheckBox( LEFT, g_CVars.Visuals.Chams.Weapons, /*Weapons*/XorStr<0xF6,8,0x19E948CC>("\xA1\x92\x99\x89\x95\x95\x8F"+0x19E948CC).s );
		CheckBox( LEFT, g_CVars.Visuals.Chams.Shadows, /*Shadows*/XorStr<0x61,8,0x963B6FC3>("\x32\x0A\x02\x00\x0A\x11\x14"+0x963B6FC3).s );
		CheckBox( LEFT, g_CVars.Visuals.Chams.Outline, /*Outline*/XorStr<0x6D,8,0xC5CA4050>("\x22\x1B\x1B\x1C\x18\x1C\x16"+0xC5CA4050).s );
		CheckBox( LEFT, g_CVars.Visuals.Chams.HandsOutline, /*Hands Outline*/XorStr<0x38,14,0x20B64C60>("\x70\x58\x54\x5F\x4F\x1D\x71\x4A\x34\x2D\x2B\x2D\x21"+0x20B64C60).s );
		CheckBox( LEFT, g_CVars.Visuals.Chams.EnemyOnly, /*Enemy Only*/XorStr<0x5E,11,0xF3DB2F3B>("\x1B\x31\x05\x0C\x1B\x43\x2B\x0B\x0A\x1E"+0xF3DB2F3B).s );

		// ========================================================================================================

		Section( true, RIGHT, 7, /*Others*/XorStr<0xE7,7,0x5E1621D0>("\xA8\x9C\x81\x8F\x99\x9F"+0x5E1621D0).s );
		CheckBox( RIGHT, g_CVars.Visuals.Radar, /*Radar*/XorStr<0x6C,6,0x9B37F1DF>("\x3E\x0C\x0A\x0E\x02"+0x9B37F1DF).s );
		CheckBox( RIGHT, g_CVars.Visuals.NoSky, /*No Sky*/XorStr<0x01,7,0x436A056A>("\x4F\x6D\x23\x57\x6E\x7F"+0x436A056A).s );
		CheckBox( RIGHT, g_CVars.Visuals.NoSmoke, /*No Smoke*/XorStr<0x45,9,0x72CB6BDC>("\x0B\x29\x67\x1B\x24\x25\x20\x29"+0x72CB6BDC).s );
		CheckBox( RIGHT, g_CVars.Visuals.NoFlash, /*No Flash*/XorStr<0x92,9,0x4E6F6E86>("\xDC\xFC\xB4\xD3\xFA\xF6\xEB\xF1"+0x4E6F6E86).s );
		CheckBox( RIGHT, g_CVars.Visuals.NoHands, /*No Hands*/XorStr<0xD4,9,0xA574435B>("\x9A\xBA\xF6\x9F\xB9\xB7\xBE\xA8"+0xA574435B).s );
		CheckBox( RIGHT, g_CVars.Visuals.NoVisualRecoil, /*No Visual Recoil*/XorStr<0x3C,17,0xAF722FE3>("\x72\x52\x1E\x69\x29\x32\x37\x22\x28\x65\x14\x22\x2B\x26\x23\x27"+0xAF722FE3).s );

		//itemheight[ 1 ] += 16;
		//Slider( true, tabs[ 4 ].x - 3, menu.y + tabs[ 2 ].h + 117, tabs[ 4 ].w - 25, 0.0, 1.0, g_CVars.Visuals.ASUS );
		//g_Drawing.MenuStringNormal( true, true, columns[ 1 ] + ( tabs[ 3 ].w / 2 ) + 2, menu.y + tabs[ 1 ].h + 117 + 7, Color( 255, 255, 255, 200 ), "ASUS: %.001f", g_CVars.Visuals.ASUS );

		Slider( 1, true, tabs[ 4 ].w - 25, 0.0, 1.0, g_CVars.Visuals.ASUS, /*ASUS*/XorStr<0x2C,5,0x0AD49684>("\x6D\x7E\x7B\x7C"+0x0AD49684).s );

		// ========================================================================================================

		Section( false, RIGHT, 2, /*Crosshair*/XorStr<0x66,10,0x225F0216>("\x25\x15\x07\x1A\x19\x03\x0D\x04\x1C"+0x225F0216).s );

		std::array< std::string, 4 > crosshairtype = { /*Off*/XorStr<0x7D,4,0xC2F45876>("\x32\x18\x19"+0xC2F45876).s, /*Cross*/XorStr<0x46,6,0x14B47584>("\x05\x35\x27\x3A\x39"+0x14B47584).s, /*Dot*/XorStr<0x4B,4,0x8306D1AD>("\x0F\x23\x39"+0x8306D1AD).s, /*Round*/XorStr<0xAA,6,0x99A99C10>("\xF8\xC4\xD9\xC3\xCA"+0x99A99C10).s };
		PseudoCombo( RIGHT, g_CVars.Visuals.Crosshair.Type, 0, 3, /*Type*/XorStr<0x42,5,0x97F4E2D8>("\x16\x3A\x34\x20"+0x97F4E2D8).s, crosshairtype.at( g_CVars.Visuals.Crosshair.Type ).c_str( ) );
		CheckBox( RIGHT, g_CVars.Visuals.Crosshair.Dynamic, /*Dynamic*/XorStr<0x1D,8,0xD8B96F58>("\x59\x67\x71\x41\x4C\x4B\x40"+0xD8B96F58).s );

		// ========================================================================================================

		Section( false, RIGHT, 8, /*Color Selector*/XorStr<0x0E,15,0x0AEEF186>("\x4D\x60\x7C\x7E\x60\x33\x47\x70\x7A\x72\x7B\x6D\x75\x69"+0x0AEEF186).s );

		std::array< std::string, 3 > entity = { /*Counter-Terrorists*/XorStr<0x35,19,0x6282FD3F>("\x76\x59\x42\x56\x4D\x5F\x49\x11\x69\x5B\x4D\x32\x2E\x30\x2A\x37\x31\x35"+0x6282FD3F).s,
			/*Terrorists*/XorStr<0x67,11,0x6E59477C>("\x33\x0D\x1B\x18\x04\x1E\x04\x1D\x1B\x03"+0x6E59477C).s,
			/*Weapons*/XorStr<0x2D,8,0xB53B4261>("\x7A\x4B\x4E\x40\x5E\x5C\x40"+0xB53B4261).s };
		PseudoCombo( RIGHT, g_CVars.ColorSelector.Entity, 0, 2, /*Entity*/XorStr<0x45,7,0xB9981DF5>("\x00\x28\x33\x21\x3D\x33"+0xB9981DF5).s, entity.at( g_CVars.ColorSelector.Entity ).c_str( ) );

		std::array< std::string, 2 > element = { /*ESP*/XorStr<0x8F,4,0x3B71755E>("\xCA\xC3\xC1"+0x3B71755E).s, /*Chams*/XorStr<0xE8,6,0x3436330F>("\xAB\x81\x8B\x86\x9F"+0x3436330F).s };
		PseudoCombo( RIGHT, g_CVars.ColorSelector.Element, 0, 1, /*Element*/XorStr<0x2D,8,0x521618D9>("\x68\x42\x4A\x5D\x54\x5C\x47"+0x521618D9).s, element.at( g_CVars.ColorSelector.Element ).c_str( ) );

		std::array< std::string, 3 > colorselectormode = { /*Visible*/XorStr<0x7E,8,0xF96E24E4>("\x28\x16\xF3\xE8\xE0\xEF\xE1"+0xF96E24E4).s,
			/*Not Visible*/XorStr<0x2B,12,0x7125BECB>("\x65\x43\x59\x0E\x79\x59\x42\x5B\x51\x58\x50"+0x7125BECB).s,
			/*Outline*/XorStr<0x8F,8,0xDF99F91F>("\xC0\xE5\xE5\xFE\xFA\xFA\xF0"+0xDF99F91F).s };
		PseudoCombo( RIGHT, g_CVars.ColorSelector.Mode, 0, ( g_CVars.ColorSelector.Element ) ? 2 : 0, /*Mode*/XorStr<0x8C,5,0xF5E68F15>("\xC1\xE2\xEA\xEA"+0xF5E68F15).s, colorselectormode.at( g_CVars.ColorSelector.Mode ).c_str( ) );

		// CurrentColor[ 2 ][ 3 ][ 3 ][ 4 ]
		//               =    =    =    => r, g, b, a
		//               =    =    ======> visible, not visible, outline
		//               =    ===========> cts, tts, wpns
		//               ================> esp, chams

		LoadColors( );

		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0, 255, g_CVars.ColorSelector.CurrentColor[ g_CVars.ColorSelector.Element ][ g_CVars.ColorSelector.Entity ][ g_CVars.ColorSelector.Mode ][ 0 ], /*Red*/XorStr<0x54,4,0x754F1CCC>("\x06\x30\x32"+0x754F1CCC).s );
		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0, 255, g_CVars.ColorSelector.CurrentColor[ g_CVars.ColorSelector.Element ][ g_CVars.ColorSelector.Entity ][ g_CVars.ColorSelector.Mode ][ 1 ], /*Green*/XorStr<0x6D,6,0x9EFE2015>("\x2A\x1C\x0A\x15\x1F"+0x9EFE2015).s );
		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0, 255, g_CVars.ColorSelector.CurrentColor[ g_CVars.ColorSelector.Element ][ g_CVars.ColorSelector.Entity ][ g_CVars.ColorSelector.Mode ][ 2 ], /*Blue*/XorStr<0xFA,5,0x9C2F7C01>("\xB8\x97\x89\x98"+0x9C2F7C01).s );
		//Slider( RIGHT, true, tabs[ 4 ].w - 25, 0, 255, g_CVars.ColorSelector.CurrentColor[ g_CVars.ColorSelector.Element ][ g_CVars.ColorSelector.Entity ][ g_CVars.ColorSelector.Mode ][ 3 ], "Alpha" );

		SetColors( );

		Color curr = Color( g_CVars.ColorSelector.CurrentColor[ g_CVars.ColorSelector.Element ][ g_CVars.ColorSelector.Entity ][ g_CVars.ColorSelector.Mode ][ 0 ],
			g_CVars.ColorSelector.CurrentColor[ g_CVars.ColorSelector.Element ][ g_CVars.ColorSelector.Entity ][ g_CVars.ColorSelector.Mode ][ 1 ],
			g_CVars.ColorSelector.CurrentColor[ g_CVars.ColorSelector.Element ][ g_CVars.ColorSelector.Entity ][ g_CVars.ColorSelector.Mode ][ 2 ],
			255 );

		g_Drawing.FilledRect( columns[ RIGHT ] + 12, itemheight[ 1 ] + 16, tabs[ 4 ].w + 76, 32, curr );
		itemheight[ 1 ] += 32;

		// ========================================================================================================

		if( itemheight[ 0 ] > itemheight[ 1 ] ) g_CVars.Menu.h = itemheight[ 0 ] - menu.y + 44;
		else if( itemheight[ 1 ] > itemheight[ 0 ] ) g_CVars.Menu.h = itemheight[ 1 ] - menu.y + 44;
	}

	// ========================================================================================================

	if( activetab == 3 )
	{
		itemheight[ 0 ] = menu.y + tabs[ 1 ].h + 5;
		itemheight[ 1 ] = menu.y + tabs[ 1 ].h + 5;

		Section( true, LEFT, 12, /*Anti Aim*/XorStr<0x47,9,0x4B5AF1D1>("\x06\x26\x3D\x23\x6B\x0D\x24\x23"+0x4B5AF1D1).s );
		CheckBox( LEFT, g_CVars.Miscellaneous.AntiAim.Active, /*Active*/XorStr<0x77,7,0x8E6102E3>("\x36\x1B\x0D\x13\x0D\x19"+0x8E6102E3).s );

		std::array< std::string, 9 > pitch = { /*Off*/XorStr<0x1D,4,0x3EDE981C>("\x52\x78\x79"+0x3EDE981C).s, /*Normal*/XorStr<0x6F,7,0xE8C880E3>("\x21\x1F\x03\x1F\x12\x18"+0xE8C880E3).s, /*Inverse Normal*/XorStr<0xE5,15,0x9534AE32>("\xAC\x88\x91\x8D\x9B\x99\x8E\xCC\xA3\x81\x9D\x9D\x90\x9E"+0x9534AE32).s, /*Safe*/XorStr<0x47,5,0xD0F7FD03>("\x14\x29\x2F\x2F"+0xD0F7FD03).s, /*Fake Down*/XorStr<0x66,10,0xB0A43ABC>("\x20\x06\x03\x0C\x4A\x2F\x03\x1A\x00"+0xB0A43ABC).s, /*Down*/XorStr<0xCF,5,0xD629CB2A>("\x8B\xBF\xA6\xBC"+0xD629CB2A).s, /*Up*/XorStr<0xC6,3,0xBCF4EC61>("\x93\xB7"+0xBCF4EC61).s, /*Lag Down*/XorStr<0xDC,9,0x743DAFF1>("\x90\xBC\xB9\xFF\xA4\x8E\x95\x8D"+0x743DAFF1).s, /*Lag Up*/XorStr<0x4B,7,0x67EC1A4D>("\x07\x2D\x2A\x6E\x1A\x20"+0x67EC1A4D).s };
		PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.Pitch, 0, 8, /*Pitch*/XorStr<0xCC,6,0xBF4BF8DF>("\x9C\xA4\xBA\xAC\xB8"+0xBF4BF8DF).s, pitch.at( g_CVars.Miscellaneous.AntiAim.Pitch ).c_str( ) );

		//std::array< std::string, 10 > yaw = { /*Forwards*/XorStr<0x0B,9,0xA1AD34E5>("\x4D\x63\x7F\x79\x6E\x62\x75\x61"+0xA1AD34E5).s, /*Backwards*/XorStr<0xFC,10,0x18D98381>("\xBE\x9C\x9D\x94\x77\x60\x70\x67\x77"+0x18D98381).s, /*Sideways*/XorStr<0xE3,9,0xB8A667F1>("\xB0\x8D\x81\x83\x90\x89\x90\x99"+0xB8A667F1).s, /*Jitter*/XorStr<0xA9,7,0xCBA8E6C3>("\xE3\xC3\xDF\xD8\xC8\xDC"+0xCBA8E6C3).s, /*S-Sideways*/XorStr<0xCA,11,0xAA6AD989>("\x99\xE6\x9F\xA4\xAA\xAA\xA7\xB0\xAB\xA0"+0xAA6AD989).s, /*S-R-Sideways*/XorStr<0x25,13,0x00ECE93E>("\x76\x0B\x75\x05\x7A\x43\x4F\x49\x5A\x4F\x56\x43"+0x00ECE93E).s, /*At Spawn*/XorStr<0x41,9,0xEF18F686>("\x00\x36\x63\x17\x35\x27\x30\x26"+0xEF18F686).s, /*M3nly*/XorStr<0xDB,6,0x0ACC595F>("\x96\xEF\xB3\xB2\xA6"+0x0ACC595F).s, /*Fake2*/XorStr<0xCC,6,0xA83573A7>("\x8A\xAC\xA5\xAA\xE2"+0xA83573A7).s, /*Angel*/XorStr<0x2C,6,0x1560D434>("\x6D\x43\x49\x4A\x5C"+0x1560D434).s };
		//PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.Yaw, 0, 9, "Yaw", yaw.at( g_CVars.Miscellaneous.AntiAim.Yaw ).c_str( ) );

		//std::array< std::string, 4 > yawvariation;
		//std::array< std::string, 4 > yawvariation_1 = { /*Normal*/XorStr<0x27,7,0xDB88EBBC>("\x69\x47\x5B\x47\x4A\x40"+0xDB88EBBC).s, /*Fake Side 1*/XorStr<0xD2,12,0x57D4A2C6>("\x94\xB2\xBF\xB0\xF6\x84\xB1\xBD\xBF\xFB\xED"+0x57D4A2C6).s, /*Fake Side 2*/XorStr<0x01,12,0x239182A4>("\x47\x63\x68\x61\x25\x55\x6E\x6C\x6C\x2A\x39"+0x239182A4).s, /*Random*/XorStr<0x02,7,0x9A5761A6>("\x50\x62\x6A\x61\x69\x6A"+0x9A5761A6).s };
		//std::array< std::string, 4 > yawvariation_2 = { /*Normal*/XorStr<0x1E,7,0x8BB7834E>("\x50\x70\x52\x4C\x43\x4F"+0x8BB7834E).s, /*Synced*/XorStr<0xBF,7,0x2BA01156>("\xEC\xB9\xAF\xA1\xA6\xA0"+0x2BA01156).s, /*Static*/XorStr<0xA0,7,0xB1E5541C>("\xF3\xD5\xC3\xD7\xCD\xC6"+0xB1E5541C).s, /*Static Synced*/XorStr<0xC6,14,0x9A8A136B>("\x95\xB3\xA9\xBD\xA3\xA8\xEC\x9E\xB7\xA1\xB3\xB4\xB6"+0x9A8A136B).s };
		//std::array< std::string, 4 > yawvariation_3 = { /*Jitter*/XorStr<0xF6,7,0x11C43E63>("\xBC\x9E\x8C\x8D\x9F\x89"+0x11C43E63).s, /*Jitter Synced*/XorStr<0xD4,14,0xEABC0AA9>("\x9E\xBC\xA2\xA3\xBD\xAB\xFA\x88\xA5\xB3\xBD\xBA\x84"+0xEABC0AA9).s, /*m3nly 1*/XorStr<0xE8,8,0x7E7F79EA>("\x85\xDA\x84\x87\x95\xCD\xDF"+0x7E7F79EA).s, /*m3nly 2*/XorStr<0xCE,8,0x88B1EC50>("\xA3\xFC\xBE\xBD\xAB\xF3\xE6"+0x88B1EC50).s };
		//std::array< std::string, 4 > yawvariation_4 = { /*Forwards*/XorStr<0xD2,9,0xBF510F79>("\x94\xBC\xA6\xA2\xB7\xA5\xBC\xAA"+0xBF510F79).s, /*Backwards*/XorStr<0x7F,10,0xF2203CAA>("\x3D\xE1\xE2\xE9\xF4\xE5\xF7\xE2\xF4"+0xF2203CAA).s, /*Left*/XorStr<0x87,5,0x6DEB0C6B>("\xCB\xED\xEF\xFE"+0x6DEB0C6B).s, /*Right*/XorStr<0x13,6,0x72CF8149>("\x41\x7D\x72\x7E\x63"+0x72CF8149).s };
		//std::array< std::string, 4 > yawvariation_5 = { /*Dynamic Random*/XorStr<0xE4,15,0x347F39C7>("\xA0\x9C\x88\x86\x85\x80\x89\xCB\xBE\x8C\x80\x8B\x9F\x9C"+0x347F39C7).s, /*Dynamic*/XorStr<0x35,8,0xB5627D89>("\x71\x4F\x59\x59\x54\x53\x58"+0xB5627D89).s, /*Static*/XorStr<0xB2,7,0x2CE8DE85>("\xE1\xC7\xD5\xC1\xDF\xD4"+0x2CE8DE85).s, /*Fake*/XorStr<0x46,5,0xD36841D3>("\x00\x26\x23\x2C"+0xD36841D3).s };

		//if( g_CVars.Miscellaneous.AntiAim.Yaw < 3 ) yawvariation = yawvariation_1;
		//else if( g_CVars.Miscellaneous.AntiAim.Yaw == 3 ) yawvariation = yawvariation_2;
		//else if( g_CVars.Miscellaneous.AntiAim.Yaw > 3 && g_CVars.Miscellaneous.AntiAim.Yaw < 7 ) yawvariation = yawvariation_1;
		//else if( g_CVars.Miscellaneous.AntiAim.Yaw == 7 ) yawvariation = yawvariation_3;
		//else if( g_CVars.Miscellaneous.AntiAim.Yaw == 8 ) yawvariation = yawvariation_4;
		//else if( g_CVars.Miscellaneous.AntiAim.Yaw == 9 ) yawvariation = yawvariation_5;

		//PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.Variation, 0, 3, /*Yaw Mode*/XorStr<0x82,9,0xA7195597>("\xDB\xE2\xF3\xA5\xCB\xE8\xEC\xEC"+0xA7195597).s, yawvariation.at( g_CVars.Miscellaneous.AntiAim.Variation ).c_str( ) );

		std::array< std::string, 8 > yaw = { /*Forwards*/XorStr<0x05,9,0x4DFBDAF1>("\x43\x69\x75\x7F\x68\x78\x6F\x7F"+0x4DFBDAF1).s,
			/*Backwards*/XorStr<0x3A,10,0x6034005E>("\x78\x5A\x5F\x56\x49\x5E\x32\x25\x31"+0x6034005E).s,
			/*Sideways*/XorStr<0xB5,9,0xCD062C02>("\xE6\xDF\xD3\xDD\xCE\xDB\xC2\xCF"+0xCD062C02).s,
			/*Jitter*/XorStr<0x20,7,0xC4656858>("\x6A\x48\x56\x57\x41\x57"+0xC4656858).s,
			/*Static*/XorStr<0x0F,7,0x13ED57A7>("\x5C\x64\x70\x66\x7A\x77"+0x13ED57A7).s,
			/*Static Reversed*/XorStr<0x67,16,0x94CD59A8>("\x34\x1C\x08\x1E\x02\x0F\x4D\x3C\x0A\x06\x14\x00\x00\x11\x11"+0x94CD59A8).s,
			/*Lisp*/XorStr<0xD8,5,0x03970457>("\x94\xB0\xA9\xAB"+0x03970457).s,
			"Custom" };
		PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.Yaw, 0, 7, /*Yaw*/XorStr<0xB4,4,0xAE24D11C>("\xED\xD4\xC1"+0xAE24D11C).s, yaw.at( g_CVars.Miscellaneous.AntiAim.Yaw ).c_str( ) );

		std::array< std::string, 4 > yawvariation;
		std::array< std::string, 4 > yawvariation_1 = { /*Normal*/XorStr<0x27,7,0xDB88EBBC>("\x69\x47\x5B\x47\x4A\x40"+0xDB88EBBC).s, /*Fake Side 1*/XorStr<0xD2,12,0x57D4A2C6>("\x94\xB2\xBF\xB0\xF6\x84\xB1\xBD\xBF\xFB\xED"+0x57D4A2C6).s, /*Fake Side 2*/XorStr<0x01,12,0x239182A4>("\x47\x63\x68\x61\x25\x55\x6E\x6C\x6C\x2A\x39"+0x239182A4).s, /*Random*/XorStr<0x02,7,0x9A5761A6>("\x50\x62\x6A\x61\x69\x6A"+0x9A5761A6).s };
		std::array< std::string, 4 > yawvariation_2 = { /*Normal*/XorStr<0x1E,7,0x8BB7834E>("\x50\x70\x52\x4C\x43\x4F"+0x8BB7834E).s, /*Synced*/XorStr<0xBF,7,0x2BA01156>("\xEC\xB9\xAF\xA1\xA6\xA0"+0x2BA01156).s, /*Static*/XorStr<0xA0,7,0xB1E5541C>("\xF3\xD5\xC3\xD7\xCD\xC6"+0xB1E5541C).s, /*Static Synced*/XorStr<0xC6,14,0x9A8A136B>("\x95\xB3\xA9\xBD\xA3\xA8\xEC\x9E\xB7\xA1\xB3\xB4\xB6"+0x9A8A136B).s };
		std::array< std::string, 4 > yawvariation_3 = { "m3nly", "m3nly #2", /*Jitter*/XorStr<0x34,7,0x5DAB1B00>("\x7E\x5C\x42\x43\x5D\x4B"+0x5DAB1B00).s, /*1337*/XorStr<0x9B,5,0x8E46D592>("\xAA\xAF\xAE\xA9"+0x8E46D592).s };
		std::array< std::string, 4 > yawvariation_4 = { "Additional", "Static" };

		switch( g_CVars.Miscellaneous.AntiAim.Yaw )
		{
			default: yawvariation = yawvariation_1; break;
			case 3: yawvariation = yawvariation_2; break;
			case 6: yawvariation = yawvariation_3; break;
			case 7: yawvariation = yawvariation_4; break;
		}

		PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.Variation, 0, ( g_CVars.Miscellaneous.AntiAim.Yaw == 7 ) ? 1 : 3, /*Yaw Mode*/XorStr<0x82,9,0xA7195597>("\xDB\xE2\xF3\xA5\xCB\xE8\xEC\xEC"+0xA7195597).s, yawvariation.at( g_CVars.Miscellaneous.AntiAim.Variation ).c_str( ) );
		Slider( LEFT, true, tabs[ 4 ].w - 25, 0.f, 360.f, g_CVars.Miscellaneous.AntiAim.RealValue, "Custom Real" );
		Slider( LEFT, true, tabs[ 4 ].w - 25, 0.f, 360.f, g_CVars.Miscellaneous.AntiAim.FakeValue, "Custom Fake" );

		//std::array< std::string, 5 > duckpitch = { /*Off*/XorStr<0xCB,4,0xE5D8145A>("\x84\xAA\xAB"+0xE5D8145A).s, /*Normal*/XorStr<0x29,7,0x85C69FCE>("\x67\x45\x59\x41\x4C\x42"+0x85C69FCE).s, /*Fake Down*/XorStr<0x9B,10,0x0D25EF00>("\xDD\xFD\xF6\xFB\xBF\xE4\xCE\xD5\xCD"+0x0D25EF00).s, /*Down*/XorStr<0xAC,5,0x7BDA9889>("\xE8\xC2\xD9\xC1"+0x7BDA9889).s, /*Up*/XorStr<0x2E,3,0x2F21B46D>("\x7B\x5F"+0x2F21B46D).s };
		//PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.DuckPitch, 0, 4, /*Duck Pitch*/XorStr<0x84,11,0x687C5A5A>("\xC0\xF0\xE5\xEC\xA8\xD9\xE3\xFF\xEF\xE5"+0x687C5A5A).s, duckpitch.at( g_CVars.Miscellaneous.AntiAim.DuckPitch ).c_str( ) );

		//std::array< std::string, 4 > duckyaw = { /*Forwards*/XorStr<0x42,9,0x04FF17BC>("\x04\x2C\x36\x32\x27\x35\x2C\x3A"+0x04FF17BC).s, /*Backwards*/XorStr<0x38,10,0x9ACFDCFF>("\x7A\x58\x59\x50\x4B\x5C\x4C\x5B\x33"+0x9ACFDCFF).s, /*Sideways*/XorStr<0xE2,9,0xDD8E6E78>("\xB1\x8A\x80\x80\x91\x86\x91\x9A"+0xDD8E6E78).s, /*Jitter*/XorStr<0x3A,7,0x0F3EA360>("\x70\x52\x48\x49\x5B\x4D"+0x0F3EA360).s };
		//PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.DuckYaw, 0, 3, "Duck Yaw", duckyaw.at( g_CVars.Miscellaneous.AntiAim.DuckYaw ).c_str( ) );

		//std::array< std::string, 4 > duckyawvariation;
		//std::array< std::string, 4 > duckyawvariation_1 = { /*Normal*/XorStr<0xBE,7,0x62534FFA>("\xF0\xD0\xB2\xAC\xA3\xAF"+0x62534FFA).s, /*Fake Side 1*/XorStr<0xF4,12,0x612E2EE1>("\xB2\x94\x9D\x92\xD8\xAA\x93\x9F\x99\xDD\xCF"+0x612E2EE1).s, /*Fake Side 2*/XorStr<0x80,12,0xFAE2CAAA>("\xC6\xE0\xE9\xE6\xA4\xD6\xEF\xE3\xED\xA9\xB8"+0xFAE2CAAA).s, /*Random*/XorStr<0xC2,7,0x7251DD34>("\x90\xA2\xAA\xA1\xA9\xAA"+0x7251DD34).s };
		//std::array< std::string, 4 > duckyawvariation_2 = { /*Normal*/XorStr<0xC6,7,0xE940F053>("\x88\xA8\xBA\xA4\xAB\xA7"+0xE940F053).s, /*Synced*/XorStr<0x9E,7,0xBF024B5A>("\xCD\xE6\xCE\xC2\xC7\xC7"+0xBF024B5A).s, /*Static*/XorStr<0xF9,7,0x6B135F65>("\xAA\x8E\x9A\x88\x94\x9D"+0x6B135F65).s, /*Static Synced*/XorStr<0x1C,14,0x43362D13>("\x4F\x69\x7F\x6B\x49\x42\x02\x70\x5D\x4B\x45\x42\x4C"+0x43362D13).s };

		//if( g_CVars.Miscellaneous.AntiAim.DuckYaw < 3 ) duckyawvariation = duckyawvariation_1;
		//else if( g_CVars.Miscellaneous.AntiAim.DuckYaw == 3 ) duckyawvariation = duckyawvariation_2;

		//PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.DuckVariation, 0, 3, /*Duck Mode*/XorStr<0x13,10,0x25F8F12C>("\x57\x61\x76\x7D\x37\x55\x76\x7E\x7E"+0x25F8F12C).s, duckyawvariation.at( g_CVars.Miscellaneous.AntiAim.DuckVariation ).c_str( ) );

		CheckBox( LEFT, g_CVars.Miscellaneous.AntiAim.Static, /*InAttack Pitch*/XorStr<0x68,15,0x7632C59D>("\x21\x07\x2B\x1F\x18\x0C\x0D\x04\x50\x21\x1B\x07\x17\x1D"+0x7632C59D).s );
		CheckBox( LEFT, g_CVars.Miscellaneous.AntiAim.WallDetection, /*Wall Detection*/XorStr<0x07,15,0x631A8993>("\x50\x69\x65\x66\x2B\x48\x68\x7A\x6A\x73\x65\x7B\x7C\x7A"+0x631A8993).s );

		std::array< std::string, 4 > walldtcmode = { /*Normal*/XorStr<0x85,7,0x1A234FA9>("\xCB\xE9\xF5\xE5\xE8\xE6"+0x1A234FA9).s, /*Fake*/XorStr<0x1A,5,0x41F44943>("\x5C\x7A\x77\x78"+0x41F44943).s, /*Fake Out*/XorStr<0xF9,9,0xCB096A06>("\xBF\x9B\x90\x99\xDD\xB1\x8A\x74"+0xCB096A06).s, /*Jitter*/XorStr<0x82,7,0x4492A445>("\xC8\xEA\xF0\xF1\xE3\xF5"+0x4492A445).s };
		PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.WallDetectionMode, 0, 3, /*Wall DTC Mode*/XorStr<0x1B,14,0x22048303>("\x4C\x7D\x71\x72\x3F\x64\x75\x61\x03\x69\x4A\x42\x42"+0x22048303).s, walldtcmode.at( g_CVars.Miscellaneous.AntiAim.WallDetectionMode ).c_str( ) );

		//std::array< std::string, 3 > attargets = { "Off", "Distance", "Average" };
		//PseudoCombo( LEFT, g_CVars.Miscellaneous.AntiAim.AtTargets, 0, 2, "At Targets", attargets.at( g_CVars.Miscellaneous.AntiAim.AtTargets ).c_str( ) );

		CheckBox( LEFT, g_CVars.Miscellaneous.AntiAim.AtTargets, /*At Targets*/XorStr<0x51,11,0x50E4EE6E>("\x10\x26\x73\x00\x34\x24\x30\x3D\x2D\x29"+0x50E4EE6E).s );
		CheckBox( LEFT, g_CVars.Miscellaneous.AntiAim.DuckInAir, /*Duck In Air*/XorStr<0xAA,12,0x5CB0FBBD>("\xEE\xDE\xCF\xC6\x8E\xE6\xDE\x91\xF3\xDA\xC6"+0x5CB0FBBD).s );
		CheckBox( LEFT, g_CVars.Miscellaneous.AntiAim.TurnOff, /*Enemy Check*/XorStr<0x0D,12,0x8A72D25F>("\x48\x60\x6A\x7D\x68\x32\x50\x7C\x70\x75\x7C"+0x8A72D25F).s );

		// ========================================================================================================

		Section( false, LEFT, 2, /*Config*/XorStr<0x2B,7,0x4480D105>("\x68\x43\x43\x48\x46\x57"+0x4480D105).s );

		ClickBox( LEFT, g_CVars.Miscellaneous.Load, /*Load*/XorStr<0x09,5,0xAEF25B0A>("\x45\x65\x6A\x68"+0xAEF25B0A).s );
		ClickBox( LEFT, g_CVars.Miscellaneous.Save, /*Save*/XorStr<0x24,5,0x66D4295E>("\x77\x44\x50\x42"+0x66D4295E).s );

		// ========================================================================================================

		Section( true, RIGHT, 5, /*Fake Lag*/XorStr<0x91,9,0x0BC94399>("\xD7\xF3\xF8\xF1\xB5\xDA\xF6\xFF"+0x0BC94399).s );

		CheckBox( RIGHT, g_CVars.Miscellaneous.Fakelag.Active, /*Active*/XorStr<0xFA,7,0xA857E2A7>("\xBB\x98\x88\x94\x88\x9A"+0xA857E2A7).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.Fakelag.InAttack, /*In Attack*/XorStr<0x20,10,0x86FCD233>("\x69\x4F\x02\x62\x50\x51\x47\x44\x43"+0x86FCD233).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.Fakelag.AirOnly, /*Air Only*/XorStr<0x17,9,0xFA697DDB>("\x56\x71\x6B\x3A\x54\x72\x71\x67"+0xFA697DDB).s );

		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0, 14, g_CVars.Miscellaneous.Fakelag.Value, /*Value*/XorStr<0xB9,6,0x3D2B5F09>("\xEF\xDB\xD7\xC9\xD8"+0x3D2B5F09).s );

		std::array< std::string, 3 > fakelagmode = { /*Factor*/XorStr<0xD4,7,0x79B0353B>("\x92\xB4\xB5\xA3\xB7\xAB"+0x79B0353B).s, /*Switch*/XorStr<0x70,7,0x6CFBD62C>("\x23\x06\x1B\x07\x17\x1D"+0x6CFBD62C).s, /*Adaptive*/XorStr<0xF4,9,0xD37A3EE8>("\xB5\x91\x97\x87\x8C\x90\x8C\x9E"+0xD37A3EE8).s };
		PseudoCombo( RIGHT, g_CVars.Miscellaneous.Fakelag.Mode, 0, 2, /*Mode*/XorStr<0x85,5,0xE003C724>("\xC8\xE9\xE3\xED"+0xE003C724).s, fakelagmode.at( g_CVars.Miscellaneous.Fakelag.Mode ).c_str( ) );

		// ========================================================================================================

		Section( false, RIGHT, 2, /*Speedhack*/XorStr<0xCB,10,0x3A7025FD>("\x98\xBC\xA8\xAB\xAB\xB8\xB0\xB1\xB8"+0x3A7025FD).s );

		CheckBox( RIGHT, g_CVars.Miscellaneous.Speedhack, /*Active (hold E)*/XorStr<0x96,16,0x6A30CA19>("\xD7\xF4\xEC\xF0\xEC\xFE\xBC\xB5\xF6\xF0\xCC\xC5\x82\xE6\x8D"+0x6A30CA19).s );
		Slider( RIGHT, true, tabs[ 4 ].w - 25, 0, 13, g_CVars.Miscellaneous.SpeedhackValue, /*Value*/XorStr<0xEB,6,0xF795A397>("\xBD\x8D\x81\x9B\x8A"+0xF795A397).s );

		// ========================================================================================================

		Section( false, RIGHT, 8, /*Others*/XorStr<0xEF,7,0x893CA934>("\xA0\x84\x99\x97\x81\x87"+0x893CA934).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.BunnyHop, /*Bunny Hop*/XorStr<0xA0,10,0x2DF824ED>("\xE2\xD4\xCC\xCD\xDD\x85\xEE\xC8\xD8"+0x2DF824ED).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.AutoStrafe, /*Auto Strafe*/XorStr<0x42,12,0xC1365174>("\x03\x36\x30\x2A\x66\x14\x3C\x3B\x2B\x2D\x29"+0xC1365174).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.CircleStrafe, /*Circle Strafe (hold V)*/XorStr<0x52,23,0x5B1BF00C>("\x11\x3A\x26\x36\x3A\x32\x78\x0A\x2E\x29\x3D\x3B\x3B\x7F\x48\x09\x0D\x0F\x00\x45\x30\x4E"+0x5B1BF00C).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.AirStuck, /*Air Stuck (press F)*/XorStr<0x3D,20,0x760F49BE>("\x7C\x57\x4D\x60\x12\x36\x36\x27\x2E\x66\x6F\x38\x3B\x2F\x38\x3F\x6D\x08\x66"+0x760F49BE).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.AutoKnife, /*Auto Knife*/XorStr<0xCB,11,0xBB9AE7C6>("\x8A\xB9\xB9\xA1\xEF\x9B\xBF\xBB\xB5\xB1"+0xBB9AE7C6).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.RoundSay, /*Round Say*/XorStr<0x86,10,0x3D9684FD>("\xD4\xE8\xFD\xE7\xEE\xAB\xDF\xEC\xF7"+0x3D9684FD).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.CheatsBypass, /*sv_cheats Bypass*/XorStr<0xB2,17,0x6A3AA13E>("\xC1\xC5\xEB\xD6\xDE\xD2\xD9\xCD\xC9\x9B\xFE\xC4\xCE\xDE\xB3\xB2"+0x6A3AA13E).s );
		CheckBox( RIGHT, g_CVars.Miscellaneous.ThirdPerson, /*Third Person (sv_cheats)*/XorStr<0x81,25,0xD0EBDE03>("\xD5\xEA\xEA\xF6\xE1\xA6\xD7\xED\xFB\xF9\xE4\xE2\xAD\xA6\xFC\xE6\xCE\xF1\xFB\xF1\xF4\xE2\xE4\xB1"+0xD0EBDE03).s );

		if( itemheight[ 0 ] > itemheight[ 1 ] ) g_CVars.Menu.h = itemheight[ 0 ] - menu.y + 44;
		else if( itemheight[ 1 ] > itemheight[ 0 ] ) g_CVars.Menu.h = itemheight[ 1 ] - menu.y + 44;
	}

	if( activetab == 4 )
	{
		player_info_t pInfo;
		int pIndex = 0;
		for( int Index = 1; Index <= g_pGlobals->maxClients; Index++ )
		{
			BasePlayer* Ent = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( Index );
			if( !Ent || Index == g_pEngineClient->GetLocalPlayer( ) ) continue;

			std::string strname;
			std::string strpitch;
			std::string stryaw;

			int lh = 15;
			int lw = tabs[ 1 ].w + tabs[ 2 ].w - 12;
			int lx = columns[ 0 ] + 8;
			int ly = menu.y + tabs[ 1 ].h + 16 + 5 + ( pIndex * ( lh + 1 ) );

			int lw2 = tabs[ 4 ].w - 6;
			int lx2 = columns[ 1 ] + ( tabs[ 3 ].w / 2 ) - ( lw2 / 2 );
			int ly2 = menu.y + tabs[ 1 ].h + 16 + 5 + ( pIndex * ( lh + 1 ) );

			int lx3 = lx2 + lw2 + 4;

			g_Drawing.MenuStringNormal( true, true, lx + ( lw / 2 ), menu.y + tabs[ 1 ].h + 5 + 7, Color( 255, 255, 255, 200 ), /*Name*/XorStr<0x19,5,0xDF07213B>("\x57\x7B\x76\x79"+0xDF07213B).s );
			g_Drawing.MenuStringNormal( true, true, lx2 + ( lw2 / 2 ), menu.y + tabs[ 1 ].h + 5 + 7, Color( 255, 255, 255, 200 ), /*Pitch*/XorStr<0xE0,6,0x4872094B>("\xB0\x88\x96\x80\x8C"+0x4872094B).s );
			g_Drawing.MenuStringNormal( true, true, lx3 + ( lw2 / 2 ), menu.y + tabs[ 1 ].h + 5 + 7, Color( 255, 255, 255, 200 ), /*Yaw*/XorStr<0x42,4,0x1EB35CF3>("\x1B\x22\x33"+0x1EB35CF3).s );

			int col = 80;
			g_Drawing.FilledRect( lx, ly, lw, 1, Color( col, col, col, 255 ) );
			g_Drawing.FilledRect( lx, ly + 1, lw, 1, Color( col - 2, col - 2, col - 2, 255 ) );
			g_Drawing.FilledRect( lx, ly + 2, lw, 1, Color( col - 4, col - 4, col - 4, 255 ) );
			g_Drawing.FilledRect( lx, ly + 3, lw, 1, Color( col - 8, col - 8, col - 8, 255 ) );
			g_Drawing.FilledRect( lx, ly + 4, lw, 1, Color( col - 12, col - 12, col - 12, 255 ) );
			g_Drawing.FilledRect( lx, ly + 5, lw, 1, Color( col - 14, col - 14, col - 14, 255 ) );
			g_Drawing.FilledRect( lx, ly + 6, lw, lh - 6, Color( col - 16, col - 16, col - 16, 255 ) );

			g_Drawing.FilledRect( lx2, ly2, lw2, 1, Color( col, col, col, 255 ) );
			g_Drawing.FilledRect( lx2, ly2 + 1, lw2, 1,	Color( col - 2, col - 2, col - 2, 255 ) );
			g_Drawing.FilledRect( lx2, ly2 + 2, lw2, 1,	Color( col - 4, col - 4, col - 4, 255 ) );
			g_Drawing.FilledRect( lx2, ly2 + 3, lw2, 1,	Color( col - 8, col - 8, col - 8, 255 ) );
			g_Drawing.FilledRect( lx2, ly2 + 4, lw2, 1,	Color( col - 12, col - 12, col - 12, 255 ) );
			g_Drawing.FilledRect( lx2, ly2 + 5, lw2, 1,	Color( col - 14, col - 14, col - 14, 255 ) );
			g_Drawing.FilledRect( lx2, ly2 + 6, lw2, lh - 6, Color( col - 16, col - 16, col - 16, 255 ) );

			g_Drawing.FilledRect( lx3, ly2, lw2 - 2, 1,	Color( col, col, col, 255 ) );
			g_Drawing.FilledRect( lx3, ly2 + 1, lw2 - 2, 1,	Color( col - 2, col - 2, col - 2, 255 ) );
			g_Drawing.FilledRect( lx3, ly2 + 2, lw2 - 2, 1,	Color( col - 4, col - 4, col - 4, 255 ) );
			g_Drawing.FilledRect( lx3, ly2 + 3, lw2 - 2, 1,	Color( col - 8, col - 8, col - 8, 255 ) );
			g_Drawing.FilledRect( lx3, ly2 + 4, lw2 - 2, 1,	Color( col - 12, col - 12, col - 12, 255 ) );
			g_Drawing.FilledRect( lx3, ly2 + 5, lw2 - 2, 1,	Color( col - 14, col - 14, col - 14, 255 ) );
			g_Drawing.FilledRect( lx3, ly2 + 6, lw2 - 2, lh - 6, Color( col - 16, col - 16, col - 16, 255 ) );

			/*********************************************************************************************************/

			if( g_Stuff.Mouse.IsInBox( lx, ly, lw, lh ) )
				g_Drawing.GradientHorizontal( lx, ly, lw, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
				//g_Drawing.FilledRect( lx, ly, lw, lh, Color( Color::YellowGreen( ).r( ), Color::YellowGreen( ).g( ), Color::YellowGreen( ).b( ), 65 ) );

			if( g_Stuff.Mouse.Click( lx, ly, lw, lh ) )
			{
				g_Drawing.GradientHorizontal( lx, ly, lw, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );
				//g_Drawing.FilledRect( lx, ly, lw, lh, Color( Color::YellowGreen( ).r( ), Color::YellowGreen( ).g( ), Color::YellowGreen( ).b( ), 200 ) );
				g_CVars.PlayerList.Friend[ Index ] = !g_CVars.PlayerList.Friend[ Index ];
			}

			if( g_CVars.PlayerList.Friend[ Index ] )
			{
				strname = /*Friend: %s*/XorStr<0x13,11,0xF774FA2B>("\x55\x66\x7C\x73\x79\x7C\x23\x3A\x3E\x6F"+0xF774FA2B).s;
				g_Drawing.GradientHorizontal( lx, ly, lw, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );
			}
			else
				strname = /*%s*/XorStr<0xAE,3,0xD95C21C7>("\x8B\xDC"+0xD95C21C7).s;

			/*********************************************************************************************************/

			g_pEngineClient->GetPlayerInfo( Index, &pInfo );
			g_Drawing.MenuStringNormal( true, false, lx + ( lw / 2 ), ly + 1, Color( 255, 255, 255, 200 ), strname.c_str( ), pInfo.name );

			/*********************************************************************************************************/

			if( g_Stuff.Mouse.IsInBox( lx2, ly2, lw2, lh ) ) 
				g_Drawing.GradientHorizontal( lx2, ly2, lw2, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
				//g_Drawing.FilledRect( lx2, ly2, lw2, lh, Color( Color::YellowGreen( ).r( ), Color::YellowGreen( ).g( ), Color::YellowGreen( ).b( ), 65 ) );

			if( g_Stuff.Mouse.Click( lx2, ly2, lw2, lh ) )
			{
				//g_Drawing.FilledRect( lx2, ly2, lw2, lh, Color( Color::YellowGreen( ).r( ), Color::YellowGreen( ).g( ), Color::YellowGreen( ).b( ), 200 ) );
				g_Drawing.GradientHorizontal( lx2, ly2, lw2, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );
				g_CVars.PlayerList.Pitch[ Index ]++;
				if( update )
				{
					//g_pEngineClient->ExecuteClientCmd( "cl_fullupdate" );
					update = false;
				}
				if( g_CVars.PlayerList.Pitch[ Index ] > 3 ) g_CVars.PlayerList.Pitch[ Index ] = 0;
			}
			else update = true;

			if( g_Stuff.Mouse.RightClick( lx2, ly2, lw2, lh ) )
			{
				//g_Drawing.FilledRect( lx2, ly2, lw2, lh, Color( Color::YellowGreen( ).r( ), Color::YellowGreen( ).g( ), Color::YellowGreen( ).b( ), 200 ) );
				g_Drawing.GradientHorizontal( lx2, ly2, lw2, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );
				g_CVars.PlayerList.Pitch[ Index ]--;
				if( update )
				{
					//g_pEngineClient->ExecuteClientCmd( "cl_fullupdate" );
					update = false;
				}
				if( g_CVars.PlayerList.Pitch[ Index ] < 0 ) g_CVars.PlayerList.Pitch[ Index ] = 3;
			}
			else update = true;

			if( g_CVars.PlayerList.Pitch[ Index ] == 0 ) strpitch = /*Auto*/XorStr<0x7E,5,0x63C04D2D>("\x3F\x0A\xF4\xEE"+0x63C04D2D).s;
			else if( g_CVars.PlayerList.Pitch[ Index ] == 1 ) strpitch = /*Down*/XorStr<0x06,5,0xC52675D0>("\x42\x68\x7F\x67"+0xC52675D0).s;
			else if( g_CVars.PlayerList.Pitch[ Index ] == 2 ) strpitch = /*Up*/XorStr<0xC1,3,0x153C1010>("\x94\xB2"+0x153C1010).s;
			else if( g_CVars.PlayerList.Pitch[ Index ] == 3 ) strpitch = /*Off*/XorStr<0xDD,4,0x428E0601>("\x92\xB8\xB9"+0x428E0601).s;

			g_Drawing.MenuStringNormal( true, false, lx2 + ( lw2 / 2 ), ly2 + 1, Color( 255, 255, 255, 200 ), strpitch.c_str( ) );

			/*********************************************************************************************************/

			if( g_Stuff.Mouse.IsInBox( lx3, ly2, lw2 - 2, lh ) ) 
				g_Drawing.GradientHorizontal( lx3, ly2, lw2 - 2, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 128 );
				//g_Drawing.FilledRect( lx3, ly2, lw2 - 2, lh, Color( Color::YellowGreen( ).r( ), Color::YellowGreen( ).g( ), Color::YellowGreen( ).b( ), 65 ) );

			if( g_Stuff.Mouse.Click( lx3, ly2, lw2 - 2, lh ) )
			{
				//g_Drawing.FilledRect( lx3, ly2, lw2 - 2, lh, Color( Color::YellowGreen( ).r( ), Color::YellowGreen( ).g( ), Color::YellowGreen( ).b( ), 200 ) );
				g_Drawing.GradientHorizontal( lx3, ly2, lw2 - 2, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );
				g_CVars.PlayerList.Yaw[ Index ]++;
				if( update )
				{
					//g_pEngineClient->ExecuteClientCmd( "cl_fullupdate" );
					update = false;
				}
				if( g_CVars.PlayerList.Yaw[ Index ] > 5 ) g_CVars.PlayerList.Yaw[ Index ] = 0;
			}
			else update = true;

			if( g_Stuff.Mouse.RightClick( lx3, ly2, lw2 - 2, lh ) )
			{
				//g_Drawing.FilledRect( lx3, ly2, lw2 - 2, lh, Color( Color::YellowGreen( ).r( ), Color::YellowGreen( ).g( ), Color::YellowGreen( ).b( ), 200 ) );
				g_Drawing.GradientHorizontal( lx3, ly2, lw2 - 2, lh, g_CVars.Colors.maincolor, g_CVars.Colors.maincolorfade, 255 );
				g_CVars.PlayerList.Yaw[ Index ]--;
				if( update )
				{
					//g_pEngineClient->ExecuteClientCmd( "cl_fullupdate" );
					update = false;
				}
				if( g_CVars.PlayerList.Yaw[ Index ] < 0 ) g_CVars.PlayerList.Yaw[ Index ] = 5;
			}
			else update = true;

			if( g_CVars.PlayerList.Yaw[ Index ] == 0 ) stryaw = /*Auto*/XorStr<0xA2,5,0x525A82D0>("\xE3\xD6\xD0\xCA"+0x525A82D0).s;
			else if( g_CVars.PlayerList.Yaw[ Index ] == 1 ) stryaw = /*Resolver*/XorStr<0x65,9,0x94655996>("\x37\x03\x14\x07\x05\x1C\x0E\x1E"+0x94655996).s;
			else if( g_CVars.PlayerList.Yaw[ Index ] == 2 ) stryaw = /*Half Left*/XorStr<0x17,10,0xC6238288>("\x5F\x79\x75\x7C\x3B\x50\x78\x78\x6B"+0xC6238288).s;
			else if( g_CVars.PlayerList.Yaw[ Index ] == 3 ) stryaw = /*Half Right*/XorStr<0xFB,11,0x60B70137>("\xB3\x9D\x91\x98\xDF\x52\x68\x65\x6B\x70"+0x60B70137).s;
			else if( g_CVars.PlayerList.Yaw[ Index ] == 4 ) stryaw = /*Inverse*/XorStr<0x73,8,0x46BBFF33>("\x3A\x1A\x03\x13\x05\x0B\x1C"+0x46BBFF33).s;
			else if( g_CVars.PlayerList.Yaw[ Index ] == 5 ) stryaw = /*Off*/XorStr<0x1E,4,0x36ED0CBC>("\x51\x79\x46"+0x36ED0CBC).s;

			g_Drawing.MenuStringNormal( true, false, lx3 + ( lw2 / 2 ), ly2 + 1, Color( 255, 255, 255, 200 ), stryaw.c_str( ) );

			/*********************************************************************************************************/

			list_s[ Index ].index = g_CVars.PlayerList.Index;

			g_Drawing.OutlinedRect( lx, ly, lw, lh, Color( 25, 25, 25, 192 ) );
			g_Drawing.OutlinedRect( lx2, ly2, lw2, lh, Color( 25, 25, 25, 192 ) );
			g_Drawing.OutlinedRect( lx3, ly2, lw2 - 2, lh, Color( 25, 25, 25, 192 ) );

			pIndex++;
		}

		g_CVars.Menu.h = 66 + pIndex * 16;
	}
}

void GUI::Radar( int x, int y, int w, int h )
{
	int titlebar = 5;

	g_Stuff.Mouse.DragRadar( x, y, w, h );

	g_Drawing.FilledRect( x, y, w, h, g_CVars.Colors.radar_fill ); // radar fill
	g_Drawing.OutlinedRect( x, y, w, h, g_CVars.Colors.radar_outline ); // radar outline
	g_Drawing.OutlinedRect( x - 1, y - 1, w + 2, h + 2, g_CVars.Colors.radar_outline2 ); // radar outline

	//g_Drawing.MenuStringNormal( true, true, x + w / 2, y + titlebar / 2, Color::White( ), "test" );

	/*********************************************************************************************************/

	int radar_x = x + 5;
	int radar_y = y + 5;
	int radar_w = w - 10;
	int radar_h = h - 10;

	/*********************************************************************************************************/

	g_Drawing.FilledRect( radar_x, radar_y, radar_w, radar_h, g_CVars.Colors.radar_inside_fill ); // inside fill

	for( int i = 0; i < 12; i++ )
	{
		g_pSurface->DrawSetColor( Color( 70, 70, 70, 72 ) );
		g_pSurface->DrawLine( radar_x, radar_y + 20 * i, radar_x + radar_w, radar_y + 20 * i );
	}

	for( int i = 0; i < 12; i++ )
	{
		g_pSurface->DrawSetColor( Color( 70, 70, 70, 72 ) );
		g_pSurface->DrawLine( radar_x + 20 * i, radar_y, radar_x + 20 * i, radar_y + radar_h );
	}

	g_Drawing.FilledRect( radar_x, radar_y + ( radar_h / 2 ), radar_w, 1, g_CVars.Colors.radar_separator ); // separator
	g_Drawing.FilledRect( radar_x + ( radar_w / 2 ), radar_y, 1, radar_h, g_CVars.Colors.radar_separator ); // separator #2
	g_Drawing.OutlinedRect( radar_x, radar_y, radar_w, radar_h, g_CVars.Colors.radar_inside_outline ); // inside outline

	BasePlayer* LocalPlayer = ( BasePlayer* )g_pClientEntityList->GetClientEntity( g_pEngineClient->GetLocalPlayer( ) );
	if( !LocalPlayer ) return;

	player_info_t PlayerInfo;
	Color colour;

	for( int Index = 1; Index <= g_pGlobals->maxClients; Index++ )
	{
		BasePlayer* Ent = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( Index );
		if( !Ent || Ent == LocalPlayer ) continue;
		if( Ent->IsDormant( ) ) continue;
		if( !( Ent->m_lifeState( ) == 0 ) ) continue;

		if( g_CVars.PlayerList.Friend[ Index ] ) colour = Color::White( );
		else
		{
			if( Ent->m_iTeamNum( ) == 2 ) colour = Color::Red( );
			else if( Ent->m_iTeamNum( ) == 3 ) colour = Color::LightBlue( );
		}

		static int x1, yx1;
		float dx = Ent->GetAbsOrigin( ).x - LocalPlayer->GetAbsOrigin( ).x;
		float dy = Ent->GetAbsOrigin( ).y - LocalPlayer->GetAbsOrigin( ).y;
		float flAngle = g_Stuff.radarangles.y;
		float yaw = ( flAngle ) * ( M_PI / 180.0 );
		float mainViewAngles_CosYaw = cos( yaw );
		float mainViewAngles_SinYaw = sin( yaw );
		float ax = dy * ( -mainViewAngles_CosYaw ) + dx * mainViewAngles_SinYaw;
		float ay = dx * ( -mainViewAngles_CosYaw ) - dy * mainViewAngles_SinYaw;
		float range = 100 * 30;

		if( fabs( ax ) > range || fabs( ay ) > range )
		{
			if( ay > ax )
			{
				if( ay > -ax )
				{
					ax = range * ax / ay;
					ay = range;
				}
				else
				{
					ay = -range * ay / ax;
					ax = -range;
				}
			}
			else
			{
				if( ay > -ax )
				{
					ay = range * ay / ax;
					ax = range;
				}
				else
				{
					ax = -range * ax / ay;
					ay = -range;
				}
			}
		}

		int ScreenX = radar_x + ( radar_w / 2 ) + int( ax / range * float( 125 ) );
		int ScreenY = radar_y + ( radar_h / 2 ) + int( ay / range * float( 125 ) );
		int size = g_CVars.Radar.w;
		size -= 10;

		if( ScreenX < radar_x - size ) ScreenX = radar_x - size + 5;
		else if( ScreenX > radar_x + size ) ScreenX = radar_x + size - 5;

		if( ScreenY < radar_y - size ) ScreenY = radar_y - size + 5;
		else if( ScreenY > radar_y + size ) ScreenY = radar_y + size - 5;

		g_Drawing.FilledRect( ScreenX - 3, ScreenY - 1, 7, 3, Color::Black( ) );
		g_Drawing.FilledRect( ScreenX - 1, ScreenY - 3, 3, 7, Color::Black( ) );

		g_Drawing.FilledRect( ScreenX - 2, ScreenY, 5, 1, colour );
		g_Drawing.FilledRect( ScreenX, ScreenY - 2, 1, 5, colour );
	}
}

void GUI::ColorSchemes( )
{
	if( g_CVars.Colors.Scheme == 1 )
	{
		g_CVars.Colors.gui_fill = Color( 40, 40, 40, 245 );
		g_CVars.Colors.gui_fill2 = Color( 100, 100, 100, 220 );
		g_CVars.Colors.gui_outline = Color( 60, 60, 60, 255 );
		g_CVars.Colors.gui_outline2 = Color::Black( );
		g_CVars.Colors.gui_sections = Color( 90, 90, 90, 128 );
		g_CVars.Colors.inside_fill = Color( 40, 40, 40, 192 );
		g_CVars.Colors.inside_outline = Color( 60, 60, 60, 255 );

		g_CVars.Colors.tabs_fill = Color( 110, 110, 110, 200 );
		g_CVars.Colors.tabs_outline = Color( 30, 30, 30, 200 );

		g_CVars.Colors.radar_fill = Color( 40, 40, 40, 245 );
		g_CVars.Colors.radar_fill2 = Color( 100, 100, 100, 220 );
		g_CVars.Colors.radar_outline = Color( 60, 60, 60, 255 );
		g_CVars.Colors.radar_outline2 = Color::Black( );
		g_CVars.Colors.radar_inside_fill = Color( 50, 50, 50, 192 );
		g_CVars.Colors.radar_inside_outline = Color( 60, 60, 60, 255 );
		g_CVars.Colors.radar_separator = Color( 70, 70, 70, 192 );

		g_CVars.Colors.maincolor = Color( 175, 255, 0, 255 );
		g_CVars.Colors.maincolorfade = Color( 120, 175, 0, 255 );
		g_CVars.Colors.mouseoutline = Color::Black( );
	}
	else if( g_CVars.Colors.Scheme == 2 )
	{
		g_CVars.Colors.gui_fill = Color( 215, 215, 215, 220 );
		g_CVars.Colors.gui_fill2 = Color( 150, 150, 150, 220 );
		g_CVars.Colors.gui_outline = Color( 195, 195, 195, 255 );
		g_CVars.Colors.gui_outline2 = Color( 60, 60, 60, 200 );
		g_CVars.Colors.gui_sections = Color( 90, 90, 90, 128 );
		g_CVars.Colors.inside_fill = Color( 170, 170, 170, 200 );
		g_CVars.Colors.inside_outline = Color( 60, 60, 60, 255 );

		g_CVars.Colors.tabs_fill = Color( 125, 125, 125, 200 );
		g_CVars.Colors.tabs_outline = Color( 90, 90, 90, 200 );

		g_CVars.Colors.radar_fill = Color( 215, 215, 215, 220 );
		g_CVars.Colors.radar_fill2 = Color( 150, 150, 150, 220 );
		g_CVars.Colors.radar_outline = Color( 195, 195, 195, 255 );
		g_CVars.Colors.radar_outline2 = Color( 60, 60, 60, 200 );
		g_CVars.Colors.radar_inside_fill = Color( 170, 170, 170, 200 );
		g_CVars.Colors.radar_inside_outline = Color( 60, 60, 60, 255 );
		g_CVars.Colors.radar_separator = Color( 70, 70, 70, 192 );

		g_CVars.Colors.maincolor = Color::CyanBlue( );
		g_CVars.Colors.maincolorfade = Color( 0, 170, 85, 255 );
		g_CVars.Colors.mouseoutline = Color( 60, 60, 60, 200 );
	}
}

void GUI::Draw( )
{
	ColorSchemes( );

	if( g_pEngineClient->IsInGame( ) && g_CVars.Visuals.Radar ) Radar( g_CVars.Radar.x, g_CVars.Radar.y, g_CVars.Radar.w, g_CVars.Radar.h );

	if( GetAsyncKeyState( VK_INSERT ) & 1 ) bMouse = !bMouse;
	if( !bMouse ) return;

	g_Stuff.Mouse.Wrapper( );

	if( g_CVars.Miscellaneous.Load )
	{
		g_Config.Load( );
		g_CVars.Miscellaneous.Load = false;
	}

	if( g_CVars.Miscellaneous.Save )
	{
		g_Config.Save( );
		g_CVars.Miscellaneous.Save = false;
	}

	Menu( g_CVars.Menu.x, g_CVars.Menu.y, g_CVars.Menu.w, g_CVars.Menu.h );	
	g_Stuff.Mouse.Draw( g_CVars.Colors.maincolor, g_CVars.Colors.mouseoutline );

	if( g_CVars.Radar.x < 0 ) g_CVars.Radar.x = 0;
	if( g_CVars.Radar.y < 0 ) g_CVars.Radar.y = 0;
	int radarx = screen_x - g_CVars.Radar.h;
	int radary = screen_y - g_CVars.Radar.w;
	if( g_CVars.Radar.x > radarx ) g_CVars.Radar.x = radarx;
	if( g_CVars.Radar.y > radary ) g_CVars.Radar.y = radary;

	if( g_CVars.Menu.x < 0 ) g_CVars.Menu.x = 0;
	if( g_CVars.Menu.y < 0 ) g_CVars.Menu.y = 0;
	int menux = screen_x - g_CVars.Menu.w;
	int menuy = screen_y - g_CVars.Menu.h;
	if( g_CVars.Menu.x > menux ) g_CVars.Menu.x = menux;
	if( g_CVars.Menu.y > menuy ) g_CVars.Menu.y = menuy;
}