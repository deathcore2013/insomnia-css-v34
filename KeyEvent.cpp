#include "Main.h"

typedef int( __stdcall* InKeyEvent_t )( int, int, const char* );
int __stdcall Hooked_IN_KeyEvent( int eventcode, int keynum, const char *pszCurrentBinding )
{
	if( keynum == 147 && eventcode ) return 0;
	if( bMouse && ( keynum >= 239 && keynum <= 244 ) && keynum != 147 ) return 0;

	int ret = CreateMoveVMT->Function< InKeyEvent_t >( 17 )( eventcode, keynum, pszCurrentBinding );
	return ret;
}