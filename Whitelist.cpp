#include "Main.h"

Whitelist g_Whitelist;

void Whitelist::Init( )
{

}

bool Whitelist::List( int index )
{
	if( index == g_pEngineClient->GetLocalPlayer( ) ) return false;

	player_info_t pInfo;
	g_pEngineClient->GetPlayerInfo( index, &pInfo );

	std::string guid = pInfo.guid;
	return false;
}