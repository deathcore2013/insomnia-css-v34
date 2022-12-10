/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __BASECOMBATCHARACTER_H__
#define __BASECOMBATCHARACTER_H__

#include "BaseEntity.h"
#include "BaseCombatWeapon.h"
#include "ClientEntityList.h"
extern Valve::IClientEntityList* g_pClientEntityList;


namespace Valve
{
#define CLASSNAME BaseCombatCharacter
	class BaseCombatCharacter:
		public BaseEntity
	{
	public:
		//NETVAR(EHANDLE, DT_BaseCombatCharacter, m_hActiveWeapon); // 0xB38
		inline EHANDLE& m_hActiveWeapon( )
		{
			return *( EHANDLE* )( ( DWORD_PTR ) this + 0xB38 );
		}
		inline BaseCombatWeapon* GetActiveBaseCombatWeapon( )
		{
			IClientEntity* pEnt = g_pClientEntityList->GetClientEntityFromHandle( m_hActiveWeapon( ) );
			if( !pEnt ) return NULL;
			BaseCombatWeapon* pW = ( BaseCombatWeapon* )pEnt->GetBaseEntity( );
			return pW;
		}
	};
};
#endif //__BASECOMBATCHARACTER_H__