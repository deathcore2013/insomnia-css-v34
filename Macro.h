#ifndef __MACRO_H__
#define __MACRO_H__

class Macro
{
public:

	static void SaveMacro( CRecord* movement, Vector *DrawPath, int &TickEnd, const char* filename );
	static void ReadMacro( CRecord* movement, Vector *DrawPath, int &TickEnd, const char* filename );
	static void ReadMacro2( SRecord* movement, int &tick_count, Vector &StartPosition, const char* filename );
	char *CurrentName;
	bool Save;
	bool Load;
	bool Load2;
};

extern Macro g_Macro;

#endif