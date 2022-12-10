/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __BASEENTITY_H__
#define __BASEENTITY_H__

#include "ClientEntity.h"
#include "VfuncTemplates.h"
#include "NetvarManager.h"
#include "Vector.h"
#include "Color.h"

namespace Valve
{
	class CSPlayer;

#define CLASSNAME BaseEntity
	class BaseEntity:
		public Valve::IClientEntity
	{
	public:
		Valve::CSPlayer* ToCSPlayer()
		{
			return (Valve::CSPlayer*) this;
		}
		NETVAR(bool, DT_BaseEntity, m_bSpotted);
		NETVAR(Vector, DT_BaseEntity, m_vecOrigin);
		//NETVAR(Vector, DT_BaseEntity, m_vecVelocity);
		NETVAR(int, DT_BasePlayer, m_nTickBase);
		NETVAR(int, DT_CSPlayer, m_ArmorValue);
		NETVAR(int, DT_BaseAnimating, m_nHitboxSet);
		NETVAR(float, DT_BasePlayer, m_flSimulationTime);
		NETVAR(int, DT_BasePlayer, m_iHealth);
		NETVAR(int, DT_BasePlayer, m_lifeState);
		NETVAR(int, DT_BaseEntity, m_iTeamNum);
		NETVAR(bool, DT_CSPlayer, m_bHasHelmet);
		NETVAR(Color, DT_BaseEntity, m_clrRender);
		NETVAR(EHANDLE, DT_BaseEntity, m_hOwnerEntity);
		NETVAR(EHANDLE, DT_BaseEntity, m_hOwner);

		inline matrix3x4_t m_rgflCoordinateFrame( )
		{
			return *( matrix3x4_t* )( ( DWORD_PTR ) this + 0x26C );
		}
		inline Vector& m_vecViewOffset( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0xD4 );
		}
		inline float& m_flOldSimulationTime( )
		{
			return *( float* )( ( DWORD_PTR ) this + 0x6C );
		}
		inline QAngle& m_angEyeAngles( )
		{
			return *( QAngle* )( ( DWORD ) this + 0x101C );
		}
		inline Vector& m_vecVelocity( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0xE0 );
		}
		inline Vector EyePosition( )
		{
			return GetAbsOrigin( ) + m_vecViewOffset( );
		}

		inline Vector m_vecMins( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0x168 );
		}

		inline Vector m_vecMaxs( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0x174 );
		}

		VFUNCR0(IsPlayer, 0x240, bool);
		VFUNCR0(IsBaseCombatWeapon, 0x244, bool);

		enum thinkmethods_t
		{
			THINK_FIRE_ALL_FUNCTIONS,
			THINK_FIRE_BASE_ONLY,
			THINK_FIRE_ALL_BUT_BASE,
		};
	};
};

#endif //__BASEENTITY_H__