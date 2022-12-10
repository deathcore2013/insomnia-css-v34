#include "Main.h"

typedef void( __thiscall* FrameStageNotify_t )( void*, ClientFrameStage_t );
void __fastcall Hooked_FrameStageNotify( void* ecx, void* edx, ClientFrameStage_t curStage )
{
	BasePlayer* LocalPlayer = ( BasePlayer* )g_pClientEntityList->GetClientEntity( g_pEngineClient->GetLocalPlayer( ) );
	QAngle *pPunchAngle;
	QAngle PunchAngle, PunchAngle_old;

	if( g_pEngineClient->IsInGame( ) )
	{
		if( curStage == FRAME_UNDEFINED ) return;
	}

	static bool once;
	
	if( LocalPlayer && LocalPlayer->m_lifeState( ) == 0 )
	{
		if( g_CVars.Miscellaneous.CheatsBypass && g_CVars.Miscellaneous.ThirdPerson )
		{
			*( float* )( ( DWORD ) LocalPlayer + 0xD14 ) = g_qThirdPerson.y; // pl + deadflag + 0x4

			if( once )
			{
				g_pEngineClient->ExecuteClientCmd( /*thirdperson*/XorStr<0x20,12,0x7A808928>("\x54\x49\x4B\x51\x40\x55\x43\x55\x5B\x46\x44"+0x7A808928).s );
				once = false;
			}
			else once = true;
		}
	}

	CreateMoveVMT->Function< FrameStageNotify_t >( 32 )( ecx, curStage );

	if( !g_pEngineClient->IsInGame( ) ) return;

	static float tempYaw[ 64 ];

	if( curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START )
	{
		for( auto Index = g_pGlobals->maxClients; Index >= 1; --Index )
		{
			BasePlayer* Entity = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( Index );
			if( Entity == 0 ) continue;
			if( Index == g_pEngineClient->GetLocalPlayer( ) ) continue;
			if( Entity->m_lifeState( ) != 0 ) continue;
			if( Entity->m_iHealth( ) > 0 && Entity->m_iHealth( ) < 500 );
			if( !g_CVars.Aimbot.FriendlyFire )
			{
				if( Entity->m_iTeamNum( ) == LocalPlayer->m_iTeamNum( ) ) continue;
			}
			if( Entity->IsDormant( ) ) continue;

			if( !g_Whitelist.List( Index ) && g_CVars.Aimbot.Resolver.Active )
			{
				tempYaw[ Index ] = g_CVars.PlayerList.ViewAngles[ Index ].y;

				bool ret = true;
				if( g_CVars.Aimbot.Resolver.Mode == 1 && g_CVars.PlayerList.Yaw[ Index ] != 1 ) ret = false;
				
				// todo: not random, adaptive side resolvers
				// those below suck dick

				if( ret )
				{
					if( g_CVars.Aimbot.Resolver.Smart )
					{
						Vector resultLocal = EyePosition;
						Vector resultentity = Entity->EyePosition( );	
						Vector m_vTraceVector = Vector( resultLocal - resultentity );
						QAngle m_vAimAngles;
						static float yawDelta[ 64 ];
						static int yawMode[ 64 ];
	
						if( !resultLocal.IsValid( ) || !resultentity.IsValid( ) || !m_vTraceVector.IsValid( ) ) continue;

						VectorAngles( m_vTraceVector, m_vAimAngles );
						m_vAimAngles.x *= -1;

						if( !m_vAimAngles.IsValid( ) ) continue;

						yawDelta[ Index ] = m_vAimAngles.y - tempYaw[ Index ];
						yawDelta[ Index ] = g_Stuff.GuwopNormalize( yawDelta[ Index ] );
						if( yawDelta[ Index ] < 0.f ) yawDelta[ Index ] += 360.f;

						if( yawDelta[ Index ] <= 20.f || yawDelta[ Index ] >= 340.f ) yawMode[ Index ] = 1;
						else if( ( yawDelta[ Index ] >= 70.f && yawDelta[ Index ] <= 110.f ) || ( yawDelta[ Index ] >= 250.f && yawDelta[ Index ] <= 290.f ) ) yawMode[ Index ] = 2;
						else if( yawDelta[ Index ] >= 160.f && yawDelta[ Index ] <= 200.f ) yawMode[ Index ] = 3;
						else yawMode[ Index ] = 0;

						if( yawMode[ Index ] == 2 ) g_CVars.Aimbot.AutoHeightMode[ Index ] = 1;
						else g_CVars.Aimbot.AutoHeightMode[ Index ] = 0;

						if( ( g_CVars.PlayerList.ViewAngles[ Index ].x == 89.f || g_CVars.PlayerList.ViewAngles[ Index ].x == -89.f ) && yawMode[ Index ] != 2 )
						{
							if( g_CVars.Aimbot.Resolver.Type == 0 )
							{
								int lol = ( g_iGameTicks % 4 );
								switch ( lol ) 
								{
									case 0: Entity->m_angEyeAngles( ).y = 0.f; break;
									case 1: Entity->m_angEyeAngles( ).y = 90.f; break;
									case 2: Entity->m_angEyeAngles( ).y = 180.f; break;
									case 3: Entity->m_angEyeAngles( ).y = 270.f; break;
								}
							}
							else if( g_CVars.Aimbot.Resolver.Type == 1 )
							{
								int lol = ( g_iGameTicks % 4 );
								static bool half[ 64 ];

								switch ( lol ) 
								{
									case 0: Entity->m_angEyeAngles( ).y = ( half[ Index ] ) ? 0.f : 180.f; break;
									case 1: Entity->m_angEyeAngles( ).y = ( half[ Index ] ) ? 45.f : 225.f; break;
									case 2: Entity->m_angEyeAngles( ).y = ( half[ Index ] ) ? 90.f : 270.f; break;
									case 3: Entity->m_angEyeAngles( ).y = ( half[ Index ] ) ? 135.f : 315.f; half[ Index ] = !half[ Index ]; break;
								}
							}
							else if( g_CVars.Aimbot.Resolver.Type == 2 )
							{
								Entity->m_angEyeAngles( ).y = ( g_iGameTicks % 2 == 0 ) ? 90.f : -90.f;
								if( g_iGameTicks % 4 == 0 ) Entity->m_angEyeAngles( ).y += 0.087936f;
							}
							else if( g_CVars.Aimbot.Resolver.Type == 3 )
							{

							}
						}
					}
					else
					{
						g_CVars.Aimbot.AutoHeightMode[ Index ] = 0;

						if( g_CVars.Aimbot.Resolver.Type == 0 )
						{
							int lol = ( g_iGameTicks % 4 );
							switch ( lol ) 
							{
								case 0: Entity->m_angEyeAngles( ).y = 0.f; break;
								case 1: Entity->m_angEyeAngles( ).y = 90.f; break;
								case 2: Entity->m_angEyeAngles( ).y = 180.f; break;
								case 3: Entity->m_angEyeAngles( ).y = 270.f; break;
							}
						}
						else if( g_CVars.Aimbot.Resolver.Type == 1 )
						{
							int lol = ( g_iGameTicks % 4 );
							static bool half[ 64 ];

							switch ( lol ) 
							{
								case 0: Entity->m_angEyeAngles( ).y = ( half[ Index ] ) ? 0.f : 180.f; break;
								case 1: Entity->m_angEyeAngles( ).y = ( half[ Index ] ) ? 45.f : 225.f; break;
								case 2: Entity->m_angEyeAngles( ).y = ( half[ Index ] ) ? 90.f : 270.f; break;
								case 3: Entity->m_angEyeAngles( ).y = ( half[ Index ] ) ? 135.f : 315.f; half[ Index ] = !half[ Index ]; break;
							}
						}
						else if( g_CVars.Aimbot.Resolver.Type == 2 )
						{
							Entity->m_angEyeAngles( ).y = ( g_iGameTicks % 2 == 0 ) ? 90.f : -90.f;
							if( g_iGameTicks % 4 == 0 ) Entity->m_angEyeAngles( ).y += 0.087936f;
						}
						else if( g_CVars.Aimbot.Resolver.Type == 3 )
						{

						}
					}
				}
			}

			if( pPlayerHistory[ Index ][ 0 ].m_SimulationTime != Entity->m_flSimulationTime( ) )
			{
				for( int tick = 31; tick > 0; tick-- ) pPlayerHistory[ Index ][ tick ] = pPlayerHistory[ Index ][ tick - 1 ];
				g_Stuff.StoreTickRecord( Entity, &pPlayerHistory[ Index ][ 0 ] );
			}
		}
	}
}