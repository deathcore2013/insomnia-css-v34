#pragma once

#include <algorithm>
#include <string>
#include <memory>
#include <array>
#include "XOR.h"
#include "SdkIncludes.h"
using namespace Valve;

#define BASE_ENGINE 0x20000000
#define BASE_SERVER 0x22000000
#define BASE_CLIENT 0x24000000
#define HISTORY_MAX 128
#define MULTIPLAYER_BACKUP 90
#define LAGCOMP_MAX 64

#define ASSIGNXIFNZERODO(x, y) x = y; if (x)
#define ASSIGNVARANDIFNZERODO(x, y) auto x = y; if (x)
#define DESTORY_INTERFACE(x) if(x) { delete x; x = 0; }
#define ZEROPOINTER(x) if(x) x = 0;

#define TICK_INTERVAL 0.015
#define TIME_TO_TICKS( dt )	( ( int )( 0.5f + ( float )( dt ) / g_pGlobals->interval_per_tick ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL * ( t ) )
#define ROUND_TO_TICKS( t )		( TICK_INTERVAL * TIME_TO_TICKS( t ) )
#define TICK_NEVER_THINK		(-1)

#define makeptr( cast, ptr, addValue ) (cast)( (DWORD_PTR)(ptr) + (DWORD_PTR)(addValue))

static char* memdup( const char* s, size_t n )
{
	char* t = ( char* )malloc( n );
	memcpy( t, s, n );
	return t;
}
#define _memdup( object ) memdup( object, sizeof( object ) )

enum
{
	MAX_JOYSTICKS = 1,
	MOUSE_BUTTON_COUNT = 5,
	MAX_NOVINT_DEVICES = 2,
};

enum JoystickAxis_t
{
	JOY_AXIS_X = 0,
 	JOY_AXIS_Y,
	JOY_AXIS_Z,
	JOY_AXIS_R,
	JOY_AXIS_U,
	JOY_AXIS_V,
	MAX_JOYSTICK_AXES,
};

enum
{
	JOYSTICK_MAX_BUTTON_COUNT = 32,
	JOYSTICK_POV_BUTTON_COUNT = 4,
	JOYSTICK_AXIS_BUTTON_COUNT = MAX_JOYSTICK_AXES * 2,
};

#define JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_BUTTON + ((_joystick) * JOYSTICK_MAX_BUTTON_COUNT) + (_button) )
#define JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_POV_BUTTON + ((_joystick) * JOYSTICK_POV_BUTTON_COUNT) + (_button) )
#define JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) ( JOYSTICK_FIRST_AXIS_BUTTON + ((_joystick) * JOYSTICK_AXIS_BUTTON_COUNT) + (_button) )

#define JOYSTICK_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_POV_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_POV_BUTTON_INTERNAL( _joystick, _button ) )
#define JOYSTICK_AXIS_BUTTON( _joystick, _button ) ( (ButtonCode_t)JOYSTICK_AXIS_BUTTON_INTERNAL( _joystick, _button ) )

enum ButtonCode_t
{
	BUTTON_CODE_INVALID = -1,
	BUTTON_CODE_NONE = 0,

	KEY_FIRST = 0,

	KEY_NONE = KEY_FIRST,
	KEY_0,
	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_A,
	KEY_B,
	KEY_C,
	KEY_D,
	KEY_E,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_I,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_M,
	KEY_N,
	KEY_O,
	KEY_P,
	KEY_Q,
	KEY_R,
	KEY_S,
	KEY_T,
	KEY_U,
	KEY_V,
	KEY_W,
	KEY_X,
	KEY_Y,
	KEY_Z,
	KEY_PAD_0,
	KEY_PAD_1,
	KEY_PAD_2,
	KEY_PAD_3,
	KEY_PAD_4,
	KEY_PAD_5,
	KEY_PAD_6,
	KEY_PAD_7,
	KEY_PAD_8,
	KEY_PAD_9,
	KEY_PAD_DIVIDE,
	KEY_PAD_MULTIPLY,
	KEY_PAD_MINUS,
	KEY_PAD_PLUS,
	KEY_PAD_ENTER,
	KEY_PAD_DECIMAL,
	KEY_LBRACKET,
	KEY_RBRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKQUOTE,
	KEY_COMMA,
	KEY_PERIOD,
	KEY_SLASH,
	KEY_BACKSLASH,
	KEY_MINUS,
	KEY_EQUAL,
	KEY_ENTER,
	KEY_SPACE,
	KEY_BACKSPACE,
	KEY_TAB,
	KEY_CAPSLOCK,
	KEY_NUMLOCK,
	KEY_ESCAPE,
	KEY_SCROLLLOCK,
	KEY_INSERT,
	KEY_DELETE,
	KEY_HOME,
	KEY_END,
	KEY_PAGEUP,
	KEY_PAGEDOWN,
	KEY_BREAK,
	KEY_LSHIFT,
	KEY_RSHIFT,
	KEY_LALT,
	KEY_RALT,
	KEY_LCONTROL,
	KEY_RCONTROL,
	KEY_LWIN,
	KEY_RWIN,
	KEY_APP,
	KEY_UP,
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,
	KEY_CAPSLOCKTOGGLE,
	KEY_NUMLOCKTOGGLE,
	KEY_SCROLLLOCKTOGGLE,

	KEY_LAST = KEY_SCROLLLOCKTOGGLE,
	KEY_COUNT = KEY_LAST - KEY_FIRST + 1,

	// Mouse
	MOUSE_FIRST = KEY_LAST + 1,

	MOUSE_LEFT = MOUSE_FIRST,
	MOUSE_RIGHT,
	MOUSE_MIDDLE,
	MOUSE_4,
	MOUSE_5,
	MOUSE_WHEEL_UP,		// A fake button which is 'pressed' and 'released' when the wheel is moved up 
	MOUSE_WHEEL_DOWN,	// A fake button which is 'pressed' and 'released' when the wheel is moved down

	MOUSE_LAST = MOUSE_WHEEL_DOWN,
	MOUSE_COUNT = MOUSE_LAST - MOUSE_FIRST + 1,

	// Joystick
	JOYSTICK_FIRST = MOUSE_LAST + 1,

	JOYSTICK_FIRST_BUTTON = JOYSTICK_FIRST,
	JOYSTICK_LAST_BUTTON = JOYSTICK_BUTTON_INTERNAL( MAX_JOYSTICKS-1, JOYSTICK_MAX_BUTTON_COUNT-1 ),
	JOYSTICK_FIRST_POV_BUTTON,
	JOYSTICK_LAST_POV_BUTTON = JOYSTICK_POV_BUTTON_INTERNAL( MAX_JOYSTICKS-1, JOYSTICK_POV_BUTTON_COUNT-1 ),
	JOYSTICK_FIRST_AXIS_BUTTON,
	JOYSTICK_LAST_AXIS_BUTTON = JOYSTICK_AXIS_BUTTON_INTERNAL( MAX_JOYSTICKS-1, JOYSTICK_AXIS_BUTTON_COUNT-1 ),

	JOYSTICK_LAST = JOYSTICK_LAST_AXIS_BUTTON,

#if !defined ( _X360 )
	NOVINT_FIRST = JOYSTICK_LAST + 2, // plus 1 missing key. +1 seems to cause issues on the first button.
	
	NOVINT_LOGO_0 = NOVINT_FIRST,
	NOVINT_TRIANGLE_0,
	NOVINT_BOLT_0,
	NOVINT_PLUS_0,
	NOVINT_LOGO_1,
	NOVINT_TRIANGLE_1,
	NOVINT_BOLT_1,
	NOVINT_PLUS_1,
	
	NOVINT_LAST = NOVINT_PLUS_1,
#endif

	BUTTON_CODE_LAST,
	BUTTON_CODE_COUNT = BUTTON_CODE_LAST - KEY_FIRST + 1,

	// Helpers for XBox 360
	KEY_XBUTTON_UP = JOYSTICK_FIRST_POV_BUTTON,	// POV buttons
	KEY_XBUTTON_RIGHT,
	KEY_XBUTTON_DOWN,
	KEY_XBUTTON_LEFT,

	KEY_XBUTTON_A = JOYSTICK_FIRST_BUTTON,		// Buttons
	KEY_XBUTTON_B,
	KEY_XBUTTON_X,
	KEY_XBUTTON_Y,
	KEY_XBUTTON_LEFT_SHOULDER,
	KEY_XBUTTON_RIGHT_SHOULDER,
	KEY_XBUTTON_BACK,
	KEY_XBUTTON_START,
	KEY_XBUTTON_STICK1,
	KEY_XBUTTON_STICK2,

	KEY_XSTICK1_RIGHT = JOYSTICK_FIRST_AXIS_BUTTON,	// XAXIS POSITIVE
	KEY_XSTICK1_LEFT,							// XAXIS NEGATIVE
	KEY_XSTICK1_DOWN,							// YAXIS POSITIVE
	KEY_XSTICK1_UP,								// YAXIS NEGATIVE
	KEY_XBUTTON_LTRIGGER,						// ZAXIS POSITIVE
	KEY_XBUTTON_RTRIGGER,						// ZAXIS NEGATIVE
	KEY_XSTICK2_RIGHT,							// UAXIS POSITIVE
	KEY_XSTICK2_LEFT,							// UAXIS NEGATIVE
	KEY_XSTICK2_DOWN,							// VAXIS POSITIVE
	KEY_XSTICK2_UP,								// VAXIS NEGATIVE
};

#include "Main.h"

#include <time.h>
#include "ade32.h"
#include "detours2.h"
#include "VMTHook.h"
#include "Hook.h"
#include "Config.h"
#include "Stuff.h"
#include "Whitelist.h"
#include "Prediction.h"
#include "NoSpread.h"
#include "Aimbot.h"
#include "GameEventManager.h"
#include "Drawing.h"
#include "GUI.h"
#include "Recorder.h"
#include "Macro.h"

extern char *m_pszDllPath;
extern int mouse_x;
extern int mouse_y;
extern bool bMouse;
extern void printconsole( const char*, ... );

inline void**& getvtable( void* inst, size_t offset = 0 )
{
	return *reinterpret_cast<void***>( (size_t)inst + offset );
}
inline const void** getvtable( const void* inst, size_t offset = 0 )
{
	return *reinterpret_cast<const void***>( (size_t)inst + offset );
}
template< typename Fn >
inline Fn getvfunc( const void* inst, size_t index, size_t offset = 0 )
{
	return reinterpret_cast<Fn>( getvtable( inst, offset )[ index ] );
}
template< typename type >
type GetFuncModule( char * szModule, char * szFunc, DWORD dwPadd = 0 )
{
	return ( type )( ( DWORD )GetProcAddress( GetModuleHandleA( szModule ), szFunc ) + dwPadd );
}

/*
typedef struct _UNICODE_STRING
{
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
 
typedef struct _PEB_LDR_DATA
{
	ULONG Length;
	BOOLEAN Initialized;
	PVOID SsHandle;
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;
 
typedef struct _LDR_MODULE
{
	LIST_ENTRY InLoadOrderModuleList;
	LIST_ENTRY InMemoryOrderModuleList;
	LIST_ENTRY InInitializationOrderModuleList;
	PVOID BaseAddress;
	PVOID EntryPoint;
	ULONG SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	ULONG Flags;
	SHORT LoadCount;
	SHORT TlsIndex;
	LIST_ENTRY HashTableEntry;
	ULONG TimeDateStamp;
} LDR_MODULE, *PLDR_MODULE;
 
void x_wcstombs( wchar_t* src, size_t len, char* dest )
{
	int i;
	char tmpc;
	if( !src || !dest ) return;

	// iterate our wide str
	for( i = 0; i < len; i++ )
	{
		// truncate to 8-bit
		tmpc = src[ i ] & 255;
		if( (tmpc >= 'A') && (tmpc <= 'Z') ) tmpc += 32;
		// copy to buffer
		dest[ i ] = tmpc;
	}

	// zero-terminator fix
	dest[ len ] = '\0';
}
 
DWORD_PTR GetModuleBase( const char* lpModuleName )
{
	int iLenght;
	char lpBuffer[ 255 ];
	DWORD_PTR dwPEB;
	PEB_LDR_DATA* pPEB;
	LIST_ENTRY* pHead, *pNode;
	LDR_MODULE* pModule;
	
	dwPEB = *makeptr( DWORD_PTR*, __readfsdword( 0x18 ), 0x30 );
	dwPEB = *makeptr( DWORD_PTR*, dwPEB, 0xC );
	
	if( !dwPEB ) return NULL;
	
	pPEB = ( PEB_LDR_DATA* ) dwPEB;
	pHead = &pPEB->InLoadOrderModuleList;
	
	for( pNode = pHead->Flink; pNode != pHead; pNode = pNode->Flink )
	{
		pModule = CONTAINING_RECORD( pNode, LDR_MODULE, InLoadOrderModuleList );
		
		if( pModule )
		{
			iLenght = pModule->BaseDllName.Length >> 1;
			x_wcstombs( pModule->BaseDllName.Buffer, iLenght, lpBuffer );
			
			if( !strcmp( lpModuleName, lpBuffer ) )
			{
				return ( DWORD_PTR ) pModule->BaseAddress;
			}
		}
	}
}
*/

extern void CL_Move( void );
extern void FX_FireBullets( void );
extern void CL_RunPrediction( void );
extern void ClientInterpolation( void );
extern void Hooked_SetViewAngles( void );

extern float __stdcall Hooked_GetLastTimeStamp( );
extern CUserCmd* __stdcall Hooked_GetUserCmd( int );
extern bool __fastcall Hooked_InPrediction( void*, int );
extern void __fastcall Hooked_OverrideView( void*, void*, CViewSetup* );
extern void __fastcall Hooked_Update( void*, void*, bool, bool, int, int );
extern int __stdcall Hooked_IN_KeyEvent( int, int, const char* );
extern void __fastcall Hooked_FrameStageNotify( void*, void*, ClientFrameStage_t );
extern int __stdcall Hooked_DrawModelEx( ModelRenderInfo_t& );
extern void __fastcall Hooked_CreateMove( void*, void*, int, float, bool );
extern void __fastcall Hooked_RunCommand( void*, void*, BasePlayer*, CUserCmd*, IMoveHelper* );
extern bool __fastcall Hooked_ClientModeCreateMove( void*, int, float, CUserCmd* );
extern void __fastcall Hooked_PaintTraverse( void*, int, unsigned int, bool, bool );
extern IMaterial* __stdcall Hooked_FindMaterial( const char*, const char*, bool, const char* );