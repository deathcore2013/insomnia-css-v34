#include "Main.h"
#include <limits>

DWORD dwReturnAddress = NULL;
DWORD dwCreateMove = 0x24087270;
static bool bSendPacket;
int sequence_number = 0;

float _clamp( float val, float minVal, float maxVal )
{
	if ( maxVal < minVal )
		return maxVal;
	else if( val < minVal )
		return minVal;
	else if( val > maxVal )
		return maxVal;
	else
		return val;
}

static bool pass = false;
static int queue = 0;
static bool angelfix = false;

void AntiAimPitch( CUserCmd* pCmd, BasePlayer* LocalPlayer )
{
	// note: lisp doesnt do shit in css, needs max float

	switch( g_CVars.Miscellaneous.AntiAim.Pitch )
	{
		case 0: break;
		case 1: pCmd->viewangles.x = 180.f; break;																// normal
		case 2: pCmd->viewangles.x = -180.f; break; 															// inverse normal
		case 3: pCmd->viewangles.x = 70.f; break;																// safe
		case 4: pCmd->viewangles.x = -179.990005f; break; 														// fakedown
		case 5: pCmd->viewangles.x = 697049.f; break;															// lisp down
		case 6: pCmd->viewangles.x = 696871.f; break; 															// lisp up
		case 7: pCmd->viewangles.x = ( bSendPacket ) ? 697049.f : 696871.f; break; 								// fake lisp down
		case 8: pCmd->viewangles.x = ( bSendPacket ) ? 696871.f : 697049.f; break; 								// fake lisp up
	}
}

static bool twitch, twitchfake, edgetwitch, edgetwitchfake;

void AntiAimYaw( CUserCmd* pCmd, BasePlayer* LocalPlayer, bool fake, bool half )
{
	Vector Velocity = LocalPlayer->m_vecVelocity( );
	
	if( fake )
	{
		switch( g_CVars.Miscellaneous.AntiAim.Yaw )
		{
			case 0: 
			{
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: break;
					case 1: pCmd->viewangles.y += ( half ) ? 270.f : 181.f; break;
					case 2: pCmd->viewangles.y += ( half ) ? 90.f : 179.f; break;
					case 3: pCmd->viewangles.y += 180.f; break;
				}
				break;
			}
			case 1:
			{
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y += 180.f; break;
					case 1: pCmd->viewangles.y += ( half ) ? 90.f : 1.f; break;
					case 2: pCmd->viewangles.y += ( half ) ? 270.f : 359.f; break;
					case 3: break;
				}
				break;
			}
			case 2:
			{
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y += 270.f; break;
					case 1: pCmd->viewangles.y += ( half ) ? 180.f : 91.f; break;
					case 2: pCmd->viewangles.y += ( half ) ? 360.f : 89.f; break;
					case 3: pCmd->viewangles.y += 90.f; break;
				}
				break;
			}
			case 3:
			{
				twitchfake = !twitch;
				twitchfake = !twitchfake;
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y += ( twitchfake ) ? 180.f : 0.f; break;
					case 1: pCmd->viewangles.y += 180.f + ( ( twitchfake ) ? -179.990005f : 0.f ); break;
					case 2: pCmd->viewangles.y = ( twitchfake ) ? 90.f : -90.f; break;
					case 3: pCmd->viewangles.y = 180.f + ( ( twitchfake ) ? 90.f : -89.990005f ); break;
				}
				break;
			}
			case 4:
			{
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y = 180.f; break;
					case 1: pCmd->viewangles.y = ( half ) ? 90.f : 1.f; break;
					case 2: pCmd->viewangles.y = ( half ) ? 280.f : 359.f; break;
					case 3: pCmd->viewangles.y = 360.f; break;
				}
				break;
			}
			case 5:
			{
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y = 360.f; break;
					case 1: pCmd->viewangles.y = ( half ) ? 270.f : 181.f; break;
					case 2: pCmd->viewangles.y = ( half ) ? 90.f : 179.f; break;
					case 3: pCmd->viewangles.y = 180.f; break;
				}
				break;
			}
			case 6:
			{
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					twitchfake = !twitch;
					twitchfake = !twitchfake;
					case 0: pCmd->viewangles.y += 697075.087936f; break;
					case 1: pCmd->viewangles.y += 697018.087936f; break;
					case 2: pCmd->viewangles.y += ( twitchfake ) ? 696960.f : 697140.f; break;
					case 3:
					{
						int value = ( g_iGameTicks % 4 );
						switch ( value ) 
						{					
							case 0: pCmd->viewangles.y = 697140.f; break;
							case 1: pCmd->viewangles.y = 697230.f; break;
							case 2: pCmd->viewangles.y = 696960.f; break;
							case 3: pCmd->viewangles.y = 697050.f; break;
						}
					}
				}
				break;
			}
			case 7:
			{
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y += g_CVars.Miscellaneous.AntiAim.FakeValue; break;
					case 1: pCmd->viewangles.y = g_CVars.Miscellaneous.AntiAim.FakeValue; break;
				}
				break;
			}
		}
	}
	else
	{
		switch( g_CVars.Miscellaneous.AntiAim.Yaw )
		{
			case 0: break;
			case 1: pCmd->viewangles.y += 180.f; break;
			case 2: pCmd->viewangles.y += 270.f; break;
			case 3:
			{
				twitch = !twitch;
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y += ( twitch ) ? 180.f : 0.f; break;
					case 1: pCmd->viewangles.y += 180.f + ( ( twitch ) ? -179.990005f : 0.f ); break;
					case 2: pCmd->viewangles.y = ( twitch ) ? 90.f : -90.f; break;
					case 3: pCmd->viewangles.y = 180.f + ( ( twitch ) ? 90.f : -89.990005f ); break;
				}
				break;
			}
			case 4: pCmd->viewangles.y = 180.f; break;
			case 5: pCmd->viewangles.y = 0.f; break;
			case 6:
			{
				twitch = !twitch;
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y -= 696805.f; break;
					case 1: pCmd->viewangles.y -= 696805.f; break;
					case 2: pCmd->viewangles.y += ( twitch ) ? 696960.f : 697140.f; break; 
					case 3: // fake 4-step spin
					{
						int value = ( g_iGameTicks % 4 );
						switch ( value ) 
						{
							case 0: pCmd->viewangles.y = 696960.f; break;
							case 1: pCmd->viewangles.y = 697050.f; break;
							case 2: pCmd->viewangles.y = 697140.f; break;
							case 3: pCmd->viewangles.y = 697230.f; break;
						}
					}
				}
				break;
			}
			case 7:
			{
				switch( g_CVars.Miscellaneous.AntiAim.Variation )
				{
					case 0: pCmd->viewangles.y += g_CVars.Miscellaneous.AntiAim.RealValue; break;
					case 1: pCmd->viewangles.y = g_CVars.Miscellaneous.AntiAim.RealValue; break;
				}
				break;
			}
		}
	}
}

void AntiAim( BasePlayer* LocalPlayer, CUserCmd* pCmd, int LagValue )
{
	int MoveType = LocalPlayer->m_MoveType( );
	Vector Velocity = LocalPlayer->m_vecVelocity( );

	bool WallDTC = false;
	bool ret = true;
	bool ShouldChoke = false;

	bool inair = !( LocalPlayer->m_fFlags( ) & FL_ONGROUND );

	int tmpLagticks;
	if( g_CVars.Miscellaneous.Fakelag.AirOnly )
	{
		tmpLagticks = ( inair ) ? LagValue : 1;
	}
	else tmpLagticks = LagValue;

	// creds to machete for giving me this brilliant idea lol
	int DeltaTicks = _clamp( abs( queue - tmpLagticks ), 0, 15 );

	if( g_CVars.Miscellaneous.Fakelag.Active )
	{
		if( g_CVars.Miscellaneous.Fakelag.Mode == 0 )
		{
			if( DeltaTicks > 0 ) ShouldChoke = true;
		}
		else if( g_CVars.Miscellaneous.Fakelag.Mode == 1 )
		{
			if( ( pCmd->command_number % 30 ) < 15 )
			{
				if( DeltaTicks > 0 ) ShouldChoke = true;
			}
		}
		else if( g_CVars.Miscellaneous.Fakelag.Mode == 2 ) // thx polak
		{
			float Velocity2D = Velocity.Length2D( ) * g_pGlobals->interval_per_tick;

			while( tmpLagticks - 2 <= 14 )
			{
				tmpLagticks -= 2;
				if( ( tmpLagticks * Velocity2D ) > 68.f ) break;

				tmpLagticks -= 1;
				if( ( tmpLagticks * Velocity2D ) > 68.f ) break;

				if( ( tmpLagticks * Velocity2D ) > 68.f ) break;

				tmpLagticks += 1;
				if( ( tmpLagticks * Velocity2D ) > 68.f ) break;

				tmpLagticks += 2;
				if( ( tmpLagticks * Velocity2D ) > 68.f ) break;

				tmpLagticks += 5;
			};

			if( DeltaTicks > 0 ) ShouldChoke = true;
		}
	}
	else
	{
		if( g_CVars.Miscellaneous.AntiAim.Active )
		{
			static bool flip;
			flip = !flip;
			if( flip ) ShouldChoke = true;
		}
	}

	if( pass ) ShouldChoke = false;

	bSendPacket = ( ShouldChoke ) ? false : true;

	if( !bSendPacket )
	{
		if( queue >= 14 )
		{
			bSendPacket = true;
			queue = 0;
		}
		else ++queue;
	}
	else queue = 0;

	if( g_CVars.Miscellaneous.AntiAim.Active )
	{
		for( int i = g_pGlobals->maxClients; i >= 1; i-- )
		{
			if( i == g_pEngineClient->GetLocalPlayer( ) ) continue;			
			BasePlayer* Ent = ( BasePlayer* )g_pClientEntityList->GetClientEntity( i );
			if( !Ent ) continue;
			if( !( *( int* )( ( DWORD ) Ent + 0x87 ) == 0 ) ) continue;
			if( Ent->m_iTeamNum( ) == LocalPlayer->m_iTeamNum( ) ) continue;

			ret = false;
		}

		if( g_CVars.Miscellaneous.AntiAim.TurnOff )
		{
			if( ret ) return;
		}

		if( ( MoveType == Valve::MoveType_t::MOVETYPE_LADDER ) && ( pCmd->buttons & IN_DUCK ) )
		{
			if( !bSendPacket ) pCmd->buttons &= ~IN_DUCK;
		}

		if( g_CVars.Miscellaneous.AntiAim.AtTargets ) g_Stuff.AntiAim.AtTargets( LocalPlayer, pCmd );

		if( g_CVars.Miscellaneous.AntiAim.WallDetection && Velocity.Length( ) < 300.f )
		{
			if( g_CVars.Miscellaneous.AntiAim.WallDetectionMode == 0 ) WallDTC = g_Stuff.AntiAim.WallDetection( LocalPlayer, pCmd, 0.f );
			else if( g_CVars.Miscellaneous.AntiAim.WallDetectionMode == 1 ) WallDTC = g_Stuff.AntiAim.WallDetection( LocalPlayer, pCmd, ( bSendPacket ) ? 0.f : 180.f );
			else if( g_CVars.Miscellaneous.AntiAim.WallDetectionMode == 2 ) WallDTC = g_Stuff.AntiAim.WallDetection( LocalPlayer, pCmd, ( bSendPacket ) ? 180.f : 0.f );
			else if( g_CVars.Miscellaneous.AntiAim.WallDetectionMode == 3 )
			{
				if( bSendPacket )
				{
					edgetwitch = !edgetwitch;
					WallDTC = g_Stuff.AntiAim.WallDetection( LocalPlayer, pCmd, ( edgetwitch ) ? 0.f : 180.f );
				}
				else
				{
					edgetwitchfake = !edgetwitch;
					edgetwitchfake = !edgetwitchfake;
					WallDTC = g_Stuff.AntiAim.WallDetection( LocalPlayer, pCmd, ( edgetwitch ) ? 0.f : 180.f );
				}
			}
		}

		if( MoveType != Valve::MoveType_t::MOVETYPE_LADDER )
		{
			if( WallDTC ) pCmd->viewangles.x = 89.f;
			else
			{
				AntiAimPitch( pCmd, LocalPlayer );
				if( bSendPacket ) AntiAimYaw( pCmd, LocalPlayer, false, false );
				else
				{
					AntiAimYaw( pCmd, LocalPlayer, true, true );
					if( g_CVars.Miscellaneous.AntiAim.DuckInAir && LocalPlayer->GetVelocity( ).z > 0 ) pCmd->buttons |= IN_DUCK;
				}
			}
		}
	}

	pass = false;
}

void sendcmd( const char* input, ... )
{
	va_list va_alist;
	char buf[ 256 ];

	va_start( va_alist, input );
	vsprintf( buf, input, va_alist );
	va_end( va_alist );

	g_pEngineClient->ExecuteClientCmd( buf );
}

void ForceFullUpdate( BasePlayer* Ent )
{
	typedef void( __thiscall* ForceFullUpdate_t )( void* );
	( ( ForceFullUpdate_t )( ( DWORD ) BASE_ENGINE + 0x9E0D0 ) )( Ent );
}

void CorrectTickCount( CUserCmd* pCmd )
{
	if( !g_CVars.Aimbot.Interpolation.LagPrediction ) return;

	static ConVar* cvar_cl_interp = g_pCvar->FindVar( /*cl_interp*/XorStr<0x24,10,0x7F9B18B0>("\x47\x49\x79\x4E\x46\x5D\x4F\x59\x5C"+0x7F9B18B0).s );
	static ConVar* cvar_cl_updaterate = g_pCvar->FindVar( /*cl_updaterate*/XorStr<0xC6,14,0xD9FFF99F>("\xA5\xAB\x97\xBC\xBA\xAF\xAD\xB9\xAB\xBD\xB1\xA5\xB7"+0xD9FFF99F).s );
	static ConVar* cvar_cl_interp_ratio = g_pCvar->FindVar( /*cl_interp_ratio*/XorStr<0xBF,16,0x298E884B>("\xDC\xAC\x9E\xAB\xAD\xB0\xA0\xB4\xB7\x97\xBB\xAB\xBF\xA5\xA2"+0x298E884B).s );
	static ConVar* cvar_sv_minupdaterate = g_pCvar->FindVar( /*sv_minupdaterate*/XorStr<0xF6,17,0x99ECD573>("\x85\x81\xA7\x94\x93\x95\x89\x8D\x9A\x9E\x74\x64\x70\x62\x70\x60"+0x99ECD573).s );
	static ConVar* cvar_sv_maxupdaterate = g_pCvar->FindVar( /*sv_maxupdaterate*/XorStr<0x6A,17,0x6C62999F>("\x19\x1D\x33\x00\x0F\x17\x05\x01\x16\x12\x00\x10\x04\x16\x0C\x1C"+0x6C62999F).s );
	static ConVar* cvar_sv_client_min_interp_ratio = g_pCvar->FindVar( /*sv_client_min_interp_ratio*/XorStr<0x9B,27,0x783554E3>("\xE8\xEA\xC2\xFD\xF3\xC9\xC4\xCC\xD7\xFB\xC8\xCF\xC9\xF7\xC0\xC4\xDF\xC9\xDF\xDE\xF0\xC2\xD0\xC6\xDA\xDB"+0x783554E3).s );
	static ConVar* cvar_sv_client_max_interp_ratio = g_pCvar->FindVar( /*sv_client_max_interp_ratio*/XorStr<0xAF,27,0xED44D950>("\xDC\xC6\xEE\xD1\xDF\xDD\xD0\xD8\xC3\xE7\xD4\xDB\xC3\xE3\xD4\xD0\xCB\xA5\xB3\xB2\x9C\xB6\xA4\xB2\xAE\xA7"+0xED44D950).s );

	float cl_interp = cvar_cl_interp->GetFloat( );
	int cl_updaterate = cvar_cl_updaterate->GetInt( ),
	sv_maxupdaterate = cvar_sv_maxupdaterate->GetInt( ),
	sv_minupdaterate = cvar_sv_minupdaterate->GetInt( ),
	cl_interp_ratio = cvar_cl_interp_ratio->GetInt( ),
	sv_client_min_interp_ratio = cvar_sv_client_min_interp_ratio->GetInt( ),
	sv_client_max_interp_ratio = cvar_sv_client_max_interp_ratio->GetInt( );

	if( sv_client_min_interp_ratio > cl_interp_ratio ) cl_interp_ratio = sv_client_min_interp_ratio;
	if( cl_interp_ratio > sv_client_max_interp_ratio ) cl_interp_ratio = sv_client_max_interp_ratio;
	if( sv_maxupdaterate <= cl_updaterate ) cl_updaterate = sv_maxupdaterate;
	if( sv_minupdaterate > cl_updaterate ) cl_updaterate = sv_minupdaterate;

	float interp = cl_interp_ratio / cl_updaterate;
	if( interp > cl_interp ) cl_interp = interp;

	BasePlayer* LocalPlayer = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( g_pEngineClient->GetLocalPlayer( ) );

	int tick;

	if( g_Aimbot.TargetIndex != -1 )
	{
		tick = TIME_TO_TICKS( pPlayerHistory[ g_Aimbot.TargetIndex ][ 0 ].m_SimulationTime );
		bool timeout = ( tick < ( pCmd->tick_count - 50 ) );
		if( !timeout ) pCmd->tick_count = tick;
	}
}

typedef void( __thiscall* CreateMove_t )( void*, int, float, bool );
void __fastcall CreateMove( void* ecx, void* edx, int sequence_number, float input_sample_frametime, bool active )
{
	CreateMoveVMT->Function< CreateMove_t >( 18 )( edx, sequence_number, input_sample_frametime, active );

	BasePlayer* LocalPlayer = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( g_pEngineClient->GetLocalPlayer( ) );
	CSWeapon* Weapon = ( CSWeapon* ) LocalPlayer->GetActiveBaseCombatWeapon( );
	if( !LocalPlayer ) return;

	if( !g_pInput ) return;

	bSendPacket = true;
	CUserCmd* pCmd = g_pInput->GetUserCmd( sequence_number );

	g_TickCount = pCmd->tick_count;

	if( g_GUI.ShouldDisableInput( ) )
	{
		pCmd->buttons &= ~IN_ATTACK;
		pCmd->buttons &= ~IN_ATTACK2;
		pCmd->buttons &= ~IN_FORWARD;
		pCmd->buttons &= ~IN_BACK;
		pCmd->buttons &= ~IN_MOVELEFT;
		pCmd->buttons &= ~IN_MOVERIGHT;
	}

	g_Stuff.sidemove_old = pCmd->sidemove;
	g_Stuff.forwardmove_old = pCmd->forwardmove;
	g_Stuff.radarangles = pCmd->viewangles;
	g_Stuff.viewangles_old = pCmd->viewangles;
	g_Stuff.ForceCVars( );

	g_iGameTicks++;

	if( g_CVars.MovementRecorder.Active ) // todo: fix
	{
		if( GetAsyncKeyState( VK_F6 ) ) MovementRecorder.State = RECORDING; // record
		if( GetAsyncKeyState( VK_F7 ) ) // save
		{
			g_Macro.CurrentName = /*demo_1*/XorStr<0x15,7,0xEF9CCFF8>("\x71\x73\x7A\x77\x46\x2B"+0xEF9CCFF8).s;
			g_Macro.Save = true;
			g_Macro.Load = false;
		}
		if( GetAsyncKeyState( VK_F8 ) ) // load
		{
			g_Macro.CurrentName = /*demo_1*/XorStr<0x3E,7,0x37290FEA>("\x5A\x5A\x2D\x2E\x1D\x72"+0x37290FEA).s;
			g_Macro.Load = true;
			g_Macro.Save = false;
		}
		if( GetAsyncKeyState( VK_F9 ) ) MovementRecorder.State = PLAYING; // play
		if( GetAsyncKeyState( VK_F10 ) ) MovementRecorder.State = NOTHING; // stop playing/recording
		if( GetAsyncKeyState( VK_F11 ) ) MovementRecorder.State = STARTPOS; // find startposition

		MovementRecorder.RecordMovement( pCmd, LocalPlayer, pCmd->viewangles );
	}

	if( LocalPlayer->m_lifeState( ) != 0 ) return;

	if( g_CVars.Miscellaneous.BunnyHop ) g_Stuff.BunnyHop( pCmd, LocalPlayer );
	//if( g_CVars.Miscellaneous.EdgeJump ) g_Stuff.EdgeJump( pCmd, LocalPlayer );

	g_Prediction.Start( pCmd, LocalPlayer );
	EyePosition = LocalPlayer->EyePosition( );

	if( g_CVars.Miscellaneous.AutoKnife ) g_Stuff.Knifebot.Main( pCmd, LocalPlayer, Weapon );

	if( Weapon && Weapon->IsWeapon( ) )
	{
		if( g_CVars.Triggerbot.Active ) g_Stuff.SeedTrigger( pCmd, LocalPlayer, Weapon );
		if( g_CVars.Aimbot.Active )
		{
			QAngle tmp = pCmd->viewangles;
			g_Aimbot.Main( pCmd, LocalPlayer );

			if( g_CVars.Aimbot.SnapLimiter )
			{
				float delta_x, delta_y, limit;
				delta_x = g_Stuff.GuwopNormalize( pCmd->viewangles.x - tmp.x );
				delta_y = g_Stuff.GuwopNormalize( pCmd->viewangles.y - tmp.y );

				if( g_CVars.Aimbot.AngleLimit >= 180 ) limit = 180;
				else limit = float( g_CVars.Aimbot.AngleLimit ) + g_CVars.Aimbot.AngleLimitTens; // eks dee

				if( !( ( delta_x < limit && delta_x > -limit ) && ( delta_y < limit && delta_y > -limit ) ) ) pCmd->viewangles = tmp;
			}
		}

		if( pCmd->buttons & IN_ATTACK )
		{
			if( g_Stuff.IsReadyToShoot( LocalPlayer, Weapon ) )	
			{
				if( g_Aimbot.TargetIndex != -1 ) g_iBulletsFired[ g_Aimbot.TargetIndex ]++;
				angelfix = false;
				pass = true;
				queue = 0;

				bool trigger = ( g_CVars.Triggerbot.Active && !g_CVars.Triggerbot.IsShooting );

				if( !g_CVars.Triggerbot.Active || trigger )
				{
					if( g_CVars.Accuracy.ForceSeed ) g_Stuff.ForceSeed( pCmd );
					if( g_CVars.Accuracy.PerfectAccuracy )
					{
						switch( g_CVars.Accuracy.NoSpreadMode )
						{
							case 1: g_NoSpread.Main( pCmd, pCmd->viewangles, LocalPlayer, Weapon, g_CVars.Miscellaneous.AntiAim.Static ); break;
							case 2: g_NoSpread.Iterative( pCmd, pCmd->viewangles, LocalPlayer, Weapon, g_CVars.Miscellaneous.AntiAim.Static ); break;
							case 3: g_NoSpread.CoolNospreee( pCmd, pCmd->viewangles, LocalPlayer, Weapon, g_CVars.Miscellaneous.AntiAim.Static ); break;
							default: g_NoSpread.Main( pCmd, pCmd->viewangles, LocalPlayer, Weapon, g_CVars.Miscellaneous.AntiAim.Static ); break;
						}
						g_Stuff.NoRecoil( pCmd, LocalPlayer, g_CVars.Miscellaneous.AntiAim.Static );
					}
				}

				if( g_CVars.Aimbot.PerfectSilent ) bSendPacket = false;

				CorrectTickCount( pCmd );
			}
			else
			{
				if( g_CVars.Aimbot.AntiSMAC ) pCmd->viewangles = QAngle( 0, 0, 0 );
				else AntiAim( LocalPlayer, pCmd, ( g_CVars.Miscellaneous.Fakelag.InAttack ) ? g_CVars.Miscellaneous.Fakelag.Value : 1 );

				pCmd->buttons &= ~IN_ATTACK;
			}
		}
		else
		{
			if( g_CVars.Aimbot.AntiSMAC ) pCmd->viewangles = QAngle( 0, 0, 0 );
			else AntiAim( LocalPlayer, pCmd, g_CVars.Miscellaneous.Fakelag.Value );
		}
	}

	if( g_CVars.Miscellaneous.AutoStrafe ) g_Stuff.AutoStrafe( pCmd, LocalPlayer );
	g_Stuff.MovementFix.FixMove( LocalPlayer, pCmd, angelfix );

	g_Prediction.End( pCmd, LocalPlayer );

	if( g_CVars.Miscellaneous.AirStuck )
	{
		// todo: fix local pos so the shots while stuck are accurate
		if( GetAsyncKeyState( 'F' ) & 1 ) g_CVars.Miscellaneous.AirStuckPress = !g_CVars.Miscellaneous.AirStuckPress;

		if( g_CVars.Miscellaneous.AirStuckPress )
		{
			if( !( pCmd->buttons & IN_ATTACK ) ) pCmd->tick_count = INT_MAX;
		}
	}
	
	if( bSendPacket ) g_qThirdPerson = pCmd->viewangles;
}

void __declspec( naked ) __fastcall Hooked_CreateMove( void* ecx, void* edx, int sequence_number, float input_sample_frametime, bool active )
{
	__asm
	{
		push ebp
		mov ebp, esp
		mov bSendPacket, bl			   
		movzx eax, active
		push eax
		mov eax, input_sample_frametime
		push eax
		mov eax, sequence_number
		push eax
		call CreateMove			   
		mov bl, bSendPacket			   
		mov esp, ebp
		pop ebp			   
		retn 0xC
	}
}