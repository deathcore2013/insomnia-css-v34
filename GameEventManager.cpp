#include "Main.h"

cGameEvent g_GameEventManager;

void cGameEvent::FireGameEvent( IGameEvent* event )
{
	const char* eventName = event->GetName( );
	if( !eventName ) return;

	if( strcmp( eventName, /*player_connect*/XorStr<0x1F,15,0xE6504059>("\x6F\x4C\x40\x5B\x46\x56\x7A\x45\x48\x46\x47\x4F\x48\x58"+0xE6504059).s ) == 0 )
	{
		std::string playerinfo = /*echo */XorStr<0xB3,6,0x7C8193A2>("\xD6\xD7\xDD\xD9\x97"+0x7C8193A2).s;
		playerinfo += event->GetString( /*name*/XorStr<0x98,5,0x86D9D33B>("\xF6\xF8\xF7\xFE"+0x86D9D33B).s, "" );
		playerinfo += ", ";
		playerinfo += event->GetString( /*address*/XorStr<0x50,8,0xA5C98DB9>("\x31\x35\x36\x21\x31\x26\x25"+0xA5C98DB9).s, "" );
		playerinfo += ", ";
		playerinfo += event->GetString( /*networkid*/XorStr<0xBB,10,0xB3ECAF1C>("\xD5\xD9\xC9\xC9\xD0\xB2\xAA\xAB\xA7"+0xB3ECAF1C).s, "" );

		g_pEngineClient->ExecuteClientCmd( playerinfo.c_str( ) );
		g_pEngineClient->ExecuteClientCmd( /*echo */XorStr<0xE9,6,0x93668CDD>("\x8C\x89\x83\x83\xCD"+0x93668CDD).s );
	}	

	if( strcmp( eventName, /*round_start*/XorStr<0x2F,12,0x8913A370>("\x5D\x5F\x44\x5C\x57\x6B\x46\x42\x56\x4A\x4D"+0x8913A370).s ) == 0 )
	{
		if( g_CVars.Miscellaneous.RoundSay ) g_pEngineClient->ClientCmd( "say twojstary 4.0 vip" );
	}

	if( strcmp( eventName, /*player_hurt*/XorStr<0xC5,12,0x41F135CF>("\xB5\xAA\xA6\xB1\xAC\xB8\x94\xA4\xB8\xBC\xBB"+0x41F135CF).s ) == 0 )
	{
		int iKiller = g_pEngineClient->GetPlayerForUserID( event->GetInt( /*attacker*/XorStr<0xD5,9,0x71615992>("\xB4\xA2\xA3\xB9\xBA\xB1\xBE\xAE"+0x71615992).s, false ) );
		int iVictim = g_pEngineClient->GetPlayerForUserID( event->GetInt( /*userid*/XorStr<0x20,7,0x8EFF66DE>("\x55\x52\x47\x51\x4D\x41"+0x8EFF66DE).s, false ) );
		int iDamage = event->GetInt( /*dmg_health*/XorStr<0x72,11,0x9F8B268B>("\x16\x1E\x13\x2A\x1E\x12\x19\x15\x0E\x13"+0x9F8B268B).s, false );

		if( iKiller == g_pEngineClient->GetLocalPlayer( ) && iVictim != g_pEngineClient->GetLocalPlayer( ) )
		{
			BasePlayer* Ent = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( iVictim );

			if( Ent )
			{
				hit_s kek;
				kek.idx = iVictim;
				kek.time = g_pGlobals->curtime + TICKS_TO_TIME( 60 );
				kek.dmg = iDamage;
				kek.pos = Ent->GetAbsOrigin( );
				hit.push_back( kek );
			}
		}
	}

	if( strcmp( eventName, /*player_death*/XorStr<0x8A,13,0x411D0F9E>("\xFA\xE7\xED\xF4\xEB\xFD\xCF\xF5\xF7\xF2\xE0\xFD"+0x411D0F9E).s ) == 0 )
	{
		int iKiller = g_pEngineClient->GetPlayerForUserID( event->GetInt( /*attacker*/XorStr<0x31,9,0xAC07C770>("\x50\x46\x47\x55\x56\x5D\x52\x4A"+0xAC07C770).s, false ) );
		int iVictim = g_pEngineClient->GetPlayerForUserID( event->GetInt( /*userid*/XorStr<0xAA,7,0xAC29B4E9>("\xDF\xD8\xC9\xDF\xC7\xCB"+0xAC29B4E9).s, false ) );

		if( iKiller == g_pEngineClient->GetLocalPlayer( ) && iVictim != g_pEngineClient->GetLocalPlayer( ) )
		{
			// g_pEngineClient->ClientCmd( "say $$$ 1 TAP LAFF $$$" );
		}
	}
}

void cGameEvent::RegisterSelf( )
{
	g_pGameEventManager->AddListener( this, /*round_start*/XorStr<0x4A,12,0x00451BD2>("\x38\x24\x39\x23\x2A\x10\x23\x25\x33\x21\x20"+0x00451BD2).s, false );
	g_pGameEventManager->AddListener( this, /*player_hurt*/XorStr<0x40,12,0xF561EE05>("\x30\x2D\x23\x3A\x21\x37\x19\x2F\x3D\x3B\x3E"+0xF561EE05).s, false );
	g_pGameEventManager->AddListener( this, /*player_death*/XorStr<0x82,13,0x7FA6859F>("\xF2\xEF\xE5\xFC\xE3\xF5\xD7\xED\xEF\xEA\xF8\xE5"+0x7FA6859F).s, false );
	g_pGameEventManager->AddListener( this, /*player_connect*/XorStr<0x1F,15,0xEF243F3D>("\x6F\x4C\x40\x5B\x46\x56\x7A\x45\x48\x46\x47\x4F\x48\x58"+0xEF243F3D).s, false );
}