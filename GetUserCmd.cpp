#include "Main.h"

CUserCmd* __stdcall Hooked_GetUserCmd( int sequence_number )
{
	return &( *( CUserCmd** )( ( DWORD ) g_pInput + 0xC4 ) )[ sequence_number % 90 ]; 
}
