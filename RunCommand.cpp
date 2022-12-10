#include "Main.h"

bool Validate( const float &stored, const float &current )
{
	return ( abs( stored - current ) < .5f );
}

bool Validate( const Vector &stored, const Vector &current )
{
	return ( ( abs( stored.x - current.x ) < .5f ) && ( abs( stored.y - current.y ) < .5f ) && ( abs( stored.z - current.z ) < .5f ) );
}

bool Validate( const QAngle &stored, const QAngle &current )
{
	return ( ( abs( stored.x - current.x ) < .5f ) && ( abs( stored.y - current.y ) < .5f ) && ( abs( stored.z - current.z ) < .5f ) );
}

typedef void( __thiscall* RunCommand_t )( void*, BasePlayer*, CUserCmd*, IMoveHelper* );
void __fastcall Hooked_RunCommand( void* ecx, void* edx, BasePlayer* LocalPlayer, CUserCmd* pCmd, IMoveHelper* MoveHelper )
{
	g_Prediction.Move = MoveHelper;
	static int tick_count = 0;
	bool norun = ( tick_count == pCmd->tick_count );
	tick_count = pCmd->tick_count;

	int TickBase = LocalPlayer->m_nTickBase( );

	CSWeapon* Weapon = ( CSWeapon* ) LocalPlayer->GetActiveBaseCombatWeapon( );
	if( Weapon && Validate( g_flAccuracy[ TickBase % MULTIPLAYER_BACKUP ], Weapon->m_flAccuracy( ) ) ) Weapon->m_flAccuracy( ) = g_flAccuracy[ TickBase % MULTIPLAYER_BACKUP ];
	if( Validate( g_vecPunchAngle[ TickBase % MULTIPLAYER_BACKUP ], LocalPlayer->GetPunchAngle( ) ) ) LocalPlayer->GetPunchAngle( ) = g_vecPunchAngle[ TickBase % MULTIPLAYER_BACKUP ];
	if( Validate( g_vecViewOffset[ TickBase % MULTIPLAYER_BACKUP ], LocalPlayer->m_vecViewOffset( ) ) ) LocalPlayer->m_vecViewOffset( ) = g_vecViewOffset[ TickBase % MULTIPLAYER_BACKUP ];
	if( Validate( g_flFallVelocity[ TickBase % MULTIPLAYER_BACKUP ], LocalPlayer->m_flFallVelocity( ) ) ) LocalPlayer->m_flFallVelocity( ) = g_flFallVelocity[ TickBase % MULTIPLAYER_BACKUP ];
	if( Validate( g_vecVelocity[ TickBase % MULTIPLAYER_BACKUP ], LocalPlayer->m_vecVelocity( ) ) ) LocalPlayer->m_vecVelocity( ) = g_vecVelocity[ TickBase % MULTIPLAYER_BACKUP ];
	if( Validate( g_vecBaseVelocity[ TickBase % MULTIPLAYER_BACKUP ], LocalPlayer->m_vecBaseVelocity( ) ) ) LocalPlayer->m_vecBaseVelocity( ) = g_vecBaseVelocity[ TickBase % MULTIPLAYER_BACKUP ];

	if( g_CVars.Miscellaneous.Speedhack )
	{
		if( norun )
		{
			g_Prediction.Start( pCmd, LocalPlayer );
			g_Prediction.End( pCmd, LocalPlayer );
		}
		else PredictionVMT->Function< RunCommand_t >( 19 )( ecx, LocalPlayer, pCmd, MoveHelper );
	}
	else PredictionVMT->Function< RunCommand_t >( 19 )( ecx, LocalPlayer, pCmd, MoveHelper );

	TickBase++;

	if( Weapon ) g_flAccuracy[ TickBase % MULTIPLAYER_BACKUP ] = Weapon->m_flAccuracy( );
	g_vecVelocity[ TickBase % MULTIPLAYER_BACKUP ] = LocalPlayer->m_vecVelocity( );
	g_vecPunchAngle[ TickBase % MULTIPLAYER_BACKUP ] = LocalPlayer->GetPunchAngle( );
	g_vecViewOffset[ TickBase % MULTIPLAYER_BACKUP ] = LocalPlayer->m_vecViewOffset( );
	g_flFallVelocity[ TickBase % MULTIPLAYER_BACKUP ] = LocalPlayer->m_flFallVelocity( );
	g_vecBaseVelocity[ TickBase % MULTIPLAYER_BACKUP ] = LocalPlayer->m_vecBaseVelocity( );
}

typedef void ( __thiscall* Update_t )( void*, bool, bool, int, int );
void __fastcall Hooked_Update( void* ecx, void* edx, bool received_new_world_update, bool validframe, int incoming_acknowledged, int outgoing_command )
{
	PredictionVMT->Function< Update_t >( 23 )( ecx, true, validframe, incoming_acknowledged, outgoing_command );
}