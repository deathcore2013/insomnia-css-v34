#include "Main.h"
#include "detours.h"

Prediction g_Prediction;

static bool update = true;
void Prediction::Start( CUserCmd* pCmd, BasePlayer* LocalPlayer )
{
	CSWeapon* Weapon = ( CSWeapon* ) LocalPlayer->GetActiveBaseCombatWeapon( );

	m_nTickBase = LocalPlayer->m_nTickBase( );
	
	OldCurtime = g_pGlobals->curtime;
	OldFrametime = g_pGlobals->frametime;

	g_pGlobals->curtime = g_pGlobals->interval_per_tick * m_nTickBase;
	g_pGlobals->frametime = g_pGlobals->interval_per_tick;

	*( DWORD* )( ( DWORD ) LocalPlayer + 0xD60 ) = ( DWORD ) pCmd;
	*( int* )( ( DWORD ) BASE_CLIENT + 0x38FF74 ) = pCmd->random_seed;
	*( BasePlayer** )( ( DWORD ) BASE_CLIENT + 0x3B2EF8 ) = LocalPlayer;

	if( pCmd->weaponselect != 0 )
	{
		CSWeapon* selectedweapon = dynamic_cast< CSWeapon* >( g_pClientEntityList->GetClientEntity( pCmd->weaponselect ) );
		if( selectedweapon ) ( *( void( __thiscall** )( const char*, int ) )( ( DWORD ) LocalPlayer + 0x34C ) )( selectedweapon->GetWeaponAlias( ), pCmd->weaponsubtype );
	}

	/*
	if( Weapon )
	{
		int WeaponID = Weapon->GetWeaponID( );
		if( WeaponID == WEAPON_GLOCK )
		{
			if( Weapon->SpecialMode( ) )
			{
				if( Weapon->m_flGlock18Shoot( ) > 0.f ) update = false;
			}
		}
		else if( WeaponID == WEAPON_FAMAS )
		{
			if( Weapon->SpecialMode( ) )
			{
				if( Weapon->m_flFamasShoot( ) > 0.f ) update = false;
			}
		}
	}

	//if( update )
	typedef bool( __thiscall* PhysicsRunThink_t )( void*, BaseEntity::thinkmethods_t );
	if( ( ( PhysicsRunThink_t )( ( DWORD ) BASE_CLIENT + 0x1180E0 ) )( LocalPlayer, BaseEntity::thinkmethods_t::THINK_FIRE_ALL_FUNCTIONS ) )
	{
		//( *( void( __thiscall** )( void* ) )( ( DWORD ) LocalPlayer + 0x324 ) )( LocalPlayer );
	}
	
	*/

	typedef int( __thiscall* GetNextThinkTick )( void*, const char* );
	int valid = ( ( GetNextThinkTick )( ( ( DWORD ) BASE_CLIENT + 0x14DB0 ) ) )( LocalPlayer, 0 );
	if( valid > 0 && valid <= m_nTickBase )
	{

		typedef void( __thiscall* SetNextThinkTick )( void*, float, const char* );
		( ( SetNextThinkTick )( ( ( DWORD ) BASE_CLIENT + 0x16030 ) ) )( LocalPlayer, -1, 0 );
		( *( void( __thiscall** )( void* ) )( ( DWORD ) LocalPlayer + 0x1B0 ) )( LocalPlayer );
	}

	CMoveData Data;
	memset( &Data, 0, sizeof( Data ) );
	g_pPrediction->SetupMove( LocalPlayer, pCmd, Move, &Data );
	g_pGameMovement->ProcessMovement( LocalPlayer, &Data );
	g_pPrediction->FinishMove( LocalPlayer, pCmd, &Data );

	LocalPlayer->GetAbsVelocity( ) = ( LocalPlayer->m_vecBaseVelocity( ) + LocalPlayer->m_vecVelocity( ) );
}

void Prediction::End( CUserCmd* pCmd, BasePlayer* LocalPlayer )
{	
	//( *( void( __thiscall** )( BasePlayer* ) )( ( DWORD ) LocalPlayer + 0x328 ) )( LocalPlayer );

	*( DWORD* )( ( DWORD ) LocalPlayer + 0xD60 ) = 0;
	*( int* )( ( DWORD ) BASE_CLIENT + 0x38FF74 ) = -1;
	*( BasePlayer** )( ( DWORD ) BASE_CLIENT + 0x3B2EF8 ) = 0;

	if( ( g_CVars.Miscellaneous.Speedhack && !GetAsyncKeyState( 0x45 ) ) || !g_CVars.Miscellaneous.Speedhack )
	{
		if( m_nTickBase == m_nOldTickBase )
		{
			++PushTickBase;
			m_nTickBase += PushTickBase;
		}
		else PushTickBase = 0;

		LocalPlayer->SetTickBase( m_nTickBase );
	}

	m_nOldTickBase = m_nTickBase;
}

void RunSimulation( CUserCmd* pCmd, BasePlayer* LocalPlayer )
{
	g_pGlobals->curtime = LocalPlayer->m_nTickBase( ) * g_pGlobals->interval_per_tick;
	g_pGlobals->frametime = g_pGlobals->interval_per_tick;

	typedef void( __thiscall * RunSimulationFn )( void*, int, float, CUserCmd*, BasePlayer* );
	( ( RunSimulationFn )( ( DWORD ) BASE_CLIENT + 0x12B650 ) )( g_pPrediction, pCmd->command_number, g_pGlobals->curtime, pCmd, LocalPlayer );
}

typedef void( *CL_RunPrediction_t )( void );
CL_RunPrediction_t _CL_RunPrediction;

typedef void( *CL_PreprocessEntities_t )( void );
CL_PreprocessEntities_t _CL_PreprocessEntities;

void Hooked_CL_RunPrediction( )
{
	if( *( int* )( ( DWORD ) BASE_ENGINE + 0x390AA8 ) != 6 ) return;
	if( *( int* )( ( DWORD ) BASE_ENGINE + 0x390B0C ) < 0 ) return;

	g_pPrediction->Update( *( int* )( ( DWORD ) BASE_ENGINE + 0x390B0C ),
		*( int* )( ( DWORD ) BASE_ENGINE + 0x390B0C ) > 0,
		*( int* )( ( DWORD ) BASE_ENGINE + 0x3953A4 ),
		*( int* )( ( DWORD ) BASE_ENGINE + 0x39539C ) + *( int* )( ( DWORD ) BASE_ENGINE + 0x3953A0 ) );
}

void Hooked_CL_PreprocessEntities( )
{
    g_pPrediction->Update( *( int* )( ( DWORD ) BASE_ENGINE + 0x390B0C ),
		*( int* )( ( DWORD ) BASE_ENGINE + 0x390B0C ) > 0,
		*( int* )( ( DWORD ) BASE_ENGINE + 0x3953A4 ),
		*( int* )( ( DWORD ) BASE_ENGINE + 0x39539C ) + *( int* )( ( DWORD ) BASE_ENGINE + 0x3953A0 ) );

    //*( int* ) e_struct->E_Unknown = *( int* ) e_struct->E_Unknown2;

    g_pPrediction->PreEntityPacketReceived( *( int* )( ( DWORD ) BASE_ENGINE + 0x3953A8 ) - *( int* )( ( DWORD ) BASE_ENGINE + 0x3953A4 ), *( int* )( ( DWORD ) BASE_ENGINE + 0x390ABC ) );
}

void CL_RunPrediction( void )
{
	_CL_RunPrediction = ( CL_RunPrediction_t ) DetourFunction( ( PBYTE ) ( ( DWORD ) BASE_ENGINE + 0x464C0 ), ( PBYTE ) Hooked_CL_RunPrediction );
	_CL_PreprocessEntities = ( CL_PreprocessEntities_t ) DetourFunction( ( PBYTE ) ( ( DWORD ) BASE_ENGINE + 0x3EC70 ), ( PBYTE ) Hooked_CL_PreprocessEntities );
}
