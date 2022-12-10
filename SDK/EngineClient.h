/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __ENGINECLIENT_H__
#define __ENGINECLIENT_H__
#include "VfuncTemplates.h"

#include "Vector.h"

namespace Valve
{
	
	typedef unsigned long CRC32_t;
	typedef struct player_info_s
	{
		// scoreboard information
		char			name[32];
		// local server user ID, unique while server is running
		int				userID;
		// global unique player identifer
		char			guid[33];
		// friends identification number
		unsigned int	friendsID;
		// friends name
		char			friendsName[32];
		// true, if player is a bot controlled by game.dll
		bool			fakeplayer;
		// true if player is the HLTV proxy
		bool			ishltv;
		// custom files CRC for this player
		CRC32_t			customFiles[4];
		// this counter increases each time the server downloaded a new file
		unsigned char	filesDownloaded;
	} player_info_t;

	
#define CLASSNAME IVEngineClient

	class IVEngineClient
	{
	public:
		VFUNCN2(GetScreenSize, Index2Offset( 5 ), int&, int&);
		VFUNCR0(Con_IsVisible, Index2Offset( 11 ), bool );
		VFUNCR0(Time, Index2Offset( 14 ), float );
		VFUNCR0(GetLastTimeStamp, Index2Offset( 15 ), float );
		VFUNCR0(GetLocalPlayer, 0x30, int);
		VFUNCN1(GetViewAngles, 0x4C, QAngle&);
		VFUNCN1(SetViewAngles, 0x50, const QAngle&);
		VFUNCN1(ClientCmd, 0x1C, const char*);
		VFUNCR2(GetPlayerInfo, 0x20, bool, int, player_info_t*);
		VFUNCR0(IsInGame, Index2Offset( 26 ), bool);
		VFUNCR0(WorldToScreenMatrix, Index2Offset( 38 ), const VMatrix&);
		VFUNCR0(GetNetChannelInfo, Index2Offset( 72 ), INetChannelInfo*);
		VFUNCR0(IsPlayingDemo, Index2Offset( 76 ), bool);
		VFUNCR0(GetEngineBuildNumber, Index2Offset( 92 ), unsigned int);
		VFUNCR0(GetProductVersionString, Index2Offset( 93 ), const char*);
		VFUNCN1(ExecuteClientCmd, Index2Offset( 97 ), const char*);
		VFUNCR1(GetPlayerForUserID, Index2Offset( 9 ), int, int );
	};


#define CLASSNAME IVEngineServer

	class IVEngineServer
	{
	public:
		VFUNCR1(GetPlayerNetInfo, Index2Offset( 20 ), INetChannelInfo*, int);
	};
};
#endif //__ENGINECLIENT_H__