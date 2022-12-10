/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __BASECOMBATWEAPON_H__
#define __BASECOMBATWEAPON_H__

#include "GlobalVarsBase.h"
#include "BaseEntity.h"

extern Valve::CGlobalVarsBase* g_pGlobals;
extern float g_fPredictedCurtime;

#define CLASSNAME BaseCombatWeapon
namespace Valve
{
	class CSWeapon;

	class BaseCombatWeapon:
		public BaseEntity
	{
	public:
		CSWeapon* ToCSWeapon( )
		{
			return ( CSWeapon* )this;
		}
		//NETVAR(float, DT_BaseCombatWeapon, m_flNextPrimaryAttack);
		//NETVAR(int, DT_BaseCombatWeapon, m_iClip1);
		//NETVAR(int, DT_BaseCombatWeapon, m_iClip2);
		NETVAR( int, DT_BaseCombatWeapon, m_iState );
		NETVAR( EHANDLE, DT_BaseCombatWeapon, m_hOwner );
		inline float& m_flNextPrimaryAttack( )
		{
			return *( float* )( ( DWORD_PTR ) this + 0x6B8 );
		}
		inline int& m_nNextThinkTick( )
		{
			return *( int* )( ( DWORD_PTR ) this + 0x7C );
		}
		inline int& m_iClip1( )
		{
			return *( int* )( ( DWORD_PTR ) this + 0x6FC );
		}
		inline int& m_iClip2( )
		{
			return *( int* )( ( DWORD_PTR ) this + 0x700 );
		}
		inline bool ShouldReload( )
		{
			return ( m_iClip1( ) <= 0 );
		}
		inline bool IsReadyToShoot( )
		{
			return ( m_flNextPrimaryAttack( ) <= g_pGlobals->curtime && m_iClip1( ) > 0 );
		}
	};

};
#endif //__BASECOMBATWEAPON_H__