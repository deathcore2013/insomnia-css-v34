/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __CSPLAYER_H__
#define __CSPLAYER_H__

#include "NetvarManager.h"
#include "BasePlayer.h"
#include "InterfaceManager.h"

namespace Valve
{
#define CLASSNAME CSPlayer
	class CSPlayer:
		public BasePlayer
	{
	public:
		//NETVAR(bool, DT_CSPlayer, m_bHasMovedSinceSpawn);
		inline int GetDefaultFov()
		{
			typedef int (__thiscall* pfnGetDefaultFov_t)(Valve::CSPlayer*);
			static pfnGetDefaultFov_t pfnGetDefaultFov = (pfnGetDefaultFov_t) ( 0x18700 +
				HackInterfaces::InterfaceManager( ).m_clientDll.dwModuleBase);
			return pfnGetDefaultFov(this);
		}
		VFUNCR0(GetFov, 0x354, float);
	};
};

#endif //__CSPLAYER_H__