#include "Main.h"

typedef void( __cdecl* FX_FireBullets_t )( int, const Vector&, const QAngle&, int, int, int, float );

FX_FireBullets_t FX_FireBulletsServer;
FX_FireBullets_t FX_FireBulletsClient;

void __cdecl Hooked_FX_FireBulletsServer( int iPlayerIndex, const Vector &vOrigin, const QAngle &vAngles, int iWeaponID, int iMode, int iSeed, float flSpread )
{
	FX_FireBulletsServer( iPlayerIndex, vOrigin, vAngles, iWeaponID, iMode, iSeed, flSpread );
}

void __cdecl Hooked_FX_FireBulletsClient( int iPlayerIndex, const Vector &vOrigin, const QAngle &vAngles, int iWeaponID, int iMode, int iSeed, float flSpread )
{
	FX_FireBulletsClient( iPlayerIndex, vOrigin, vAngles, iWeaponID, iMode, iSeed, flSpread );
}

void FX_FireBullets( void )
{
	FX_FireBulletsServer = ( FX_FireBullets_t ) g_Detour.DetourFunction( ( ( DWORD ) BASE_SERVER + 0x2FD320 ), ( PBYTE ) Hooked_FX_FireBulletsServer );
	FX_FireBulletsClient = ( FX_FireBullets_t ) g_Detour.DetourFunction( ( ( DWORD ) BASE_CLIENT + 0x1D5060 ), ( PBYTE ) Hooked_FX_FireBulletsClient );
}
