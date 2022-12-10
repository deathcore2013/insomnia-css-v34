#include "Main.h"

typedef bool ( __thiscall *Interpolate_t )( void*, float );
typedef void ( __thiscall *Interpolation_t )( void*, float, float );
typedef void ( __thiscall *SetInterpolationAmount_t )( void*, float );
typedef int ( __thiscall *BaseInterpolatePart1_t )( void*, float, Vector, QAngle, int );

Interpolate_t Interpolate;
Interpolation_t Interpolation;
BaseInterpolatePart1_t BaseInterpolatePart1;
SetInterpolationAmount_t SetInterpolationAmount;

bool __fastcall Hooked_Interpolate( void* ptr, int edx, float currentTime )
{
	return Interpolate( ptr, currentTime );
}

void __fastcall Hooked_ClientInterpolation( void* ptr, int edx, float currentTime, float interpolation_amount )
{
	Interpolation( ptr, currentTime, -( g_pGlobals->interval_per_tick ) );
}

int __fastcall Hooked_BaseInterpolatePart1( void* thisptr, int edx, float &currentTime, Vector &oldOrigin, QAngle &oldAngles, int &bNoMoreChanges )
{
    BaseEntity *thisent = ( BaseEntity* ) thisptr;
	return 0;//BaseInterpolatePart1( thisptr, currentTime, oldOrigin, oldAngles, bNoMoreChanges );
}

void __fastcall Hooked_SetInterpolationAmount( void* ptr, int edx, float seconds )
{
	SetInterpolationAmount( ptr, -( g_pGlobals->interval_per_tick ) );
}


void ClientInterpolation( void )
{
	//Interpolate = ( Interpolate_t ) g_Detour.DetourFunction( ( ( DWORD ) BASE_CLIENT + 0x4C250 ), Hooked_Interpolate );
	//Interpolation = ( Interpolation_t ) g_Detour.DetourFunction( ( ( DWORD ) BASE_CLIENT + 0x39D40 ), Hooked_ClientInterpolation );	
	//BaseInterpolatePart1 = ( BaseInterpolatePart1_t ) g_Detour.DetourFunction( ( ( DWORD ) BASE_CLIENT + 0x47170 ), Hooked_BaseInterpolatePart1 );
	//SetInterpolationAmount = ( SetInterpolationAmount_t ) g_Detour.DetourFunction( ( ( DWORD ) BASE_CLIENT + 0x34670 ), Hooked_SetInterpolationAmount );
}

