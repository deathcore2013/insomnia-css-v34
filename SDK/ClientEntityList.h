/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __CLIENTENTITYLIST_H__
#define __CLIENTENTITYLIST_H__
#include "VfuncTemplates.h"
#include "ClientEntity.h"


namespace Valve
{
	class IClientNetworkable;
	class IClientUnknown;
	class IClientEntity;
	typedef void* EHANDLE;

#define CLASSNAME IClientEntityList
	class IClientEntityList
	{
	public:
		VFUNCR1(GetClientNetworkable, 0, Valve::IClientNetworkable*, int);
		VFUNCR1(GetClientNetworkableFromHandle, 4, Valve::IClientNetworkable*, EHANDLE);
		VFUNCR1(GetClientUnknownFromHandle, 8, Valve::IClientUnknown*, EHANDLE);
		VFUNCR1(GetClientEntity, 0xC, Valve::IClientEntity*, int);
		VFUNCR1(GetClientEntityFromHandle, 0x10, Valve::IClientEntity*, EHANDLE);
		VFUNCR1(NumberOfEntities, 0x14, int, bool);
		VFUNCR0(GetHighestEntityIndex, 0x18, int);
		VFUNCR0(GetMaxEntities, Index2Offset( 8 ), int);
	};

};

#endif //__CLIENTENTITYLIST_H__