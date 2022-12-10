/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __BASEPLAYER_H__
#define __BASEPLAYER_H__
#include "NetvarManager.h"

#include "BaseCombatCharacter.h"
#define	FL_ONGROUND	( 1 << 0 )
#define FL_DUCKING ( 1 << 1 )
#define FL_WATERJUMP ( 1 << 2 )

namespace Valve
{
	template< class T >
	inline void RangeCheck( const T &value, int minValue, int maxValue )
	{
	#ifdef _DEBUG
		extern bool g_bDoRangeChecks;
		if ( g_bDoRangeChecks )
		{
			// Ignore the min/max stuff for now.. just make sure it's not a NAN.
			Assert( _finite( value ) );
		}
	#endif
	}

	inline void RangeCheck( const Vector &value, int minValue, int maxValue )
	{
	#ifdef _DEBUG
		RangeCheck( value.x, minValue, maxValue );
		RangeCheck( value.y, minValue, maxValue );
		RangeCheck( value.z, minValue, maxValue );
	#endif
	}


	template< class T, int minValue, int maxValue, int startValue >
	class CRangeCheckedVar
	{
	public:

		inline CRangeCheckedVar()
		{
			m_Val = startValue;
		}

		inline CRangeCheckedVar( const T &value )
		{
			*this = value;
		}

		// Clamp the value to its limits. Interpolation code uses this after interpolating.
		inline void Clamp()
		{
			if ( m_Val < minValue )
				m_Val = minValue;
			else if ( m_Val > maxValue )
				m_Val = maxValue;
		}

		inline operator const T&() const
		{
			return m_Val;
		}

		inline CRangeCheckedVar<T, minValue, maxValue, startValue>& operator=( const T &value )
		{
			RangeCheck( value, minValue, maxValue );
			m_Val = value;
			return *this;
		}

		inline CRangeCheckedVar<T, minValue, maxValue, startValue>& operator+=( const T &value )
		{
			return (*this = m_Val + value);
		}

		inline CRangeCheckedVar<T, minValue, maxValue, startValue>& operator-=( const T &value )
		{
			return (*this = m_Val - value);
		}

		inline CRangeCheckedVar<T, minValue, maxValue, startValue>& operator*=( const T &value )
		{
			return (*this = m_Val * value);
		}

		inline CRangeCheckedVar<T, minValue, maxValue, startValue>& operator/=( const T &value )
		{
			return (*this = m_Val / value);
		}

		T m_Val;
	};

	class C_AnimationLayer
	{
	public:
		C_AnimationLayer( );

		void SetOrder( int order );

	public:

		CRangeCheckedVar<int, -1, 1000, 0>	nSequence;
		CRangeCheckedVar<float, -2, 2, 0>	flPrevCycle;
		CRangeCheckedVar<float, -5, 5, 0>	flWeight;
		int		nOrder;

		// used for automatic crossfades between sequence changes
		CRangeCheckedVar<float, -50, 50, 1>		flPlaybackrate;
		CRangeCheckedVar<float, -2, 2, 0>		flCycle;

		float	flAnimtime;
		float	flFadeOuttime;
	};

	inline C_AnimationLayer::C_AnimationLayer( )
	{
		nSequence = 0;
		flPrevCycle = 0;
		flWeight = 0;
		flPlaybackrate = 0;
		flCycle = 0;
		flAnimtime = 0;
		flFadeOuttime = 0;
	}

	inline void C_AnimationLayer::SetOrder( int order )
	{
		nOrder = order;
	}


	enum MoveType_t
	{
		MOVETYPE_NONE		= 0,	// never moves
		MOVETYPE_ISOMETRIC,			// For players -- in TF2 commander view, etc.
		MOVETYPE_WALK,				// Player only - moving on the ground
		MOVETYPE_STEP,				// gravity, special edge handling -- monsters use this
		MOVETYPE_FLY,				// No gravity, but still collides with stuff
		MOVETYPE_FLYGRAVITY,		// flies through the air + is affected by gravity
		MOVETYPE_VPHYSICS,			// uses VPHYSICS for simulation
		MOVETYPE_PUSH,				// no clip to world, push and crush
		MOVETYPE_NOCLIP,			// No gravity, no collisions, still do velocity/avelocity
		MOVETYPE_LADDER,			// Used by players only when going onto a ladder
		MOVETYPE_OBSERVER,			// Observer movement, depends on player's observer mode
		MOVETYPE_CUSTOM,			// Allows the entity to describe its own physics

		// should always be defined as the last item in the list
		MOVETYPE_LAST		= MOVETYPE_CUSTOM,

		MOVETYPE_MAX_BITS	= 4
	};

#define CLASSNAME BasePlayer
	class BasePlayer:
		public BaseCombatCharacter
	{
	public:
		NETVAR(float, DT_CSPlayer, m_flJumpTime);
		NETVAR(float, DT_CSPlayer, m_flDucktime);
		NETVAR(bool, DT_CSPlayer, m_bInDuckJump);
		NETVAR(bool, DT_CSPlayer, m_bDucked);
		NETVAR(bool, DT_CSPlayer, m_bDucking);
		NETVAR(int, DT_BasePlayer, m_fFlags);
		NETVAR(int, DT_BaseAnimating, m_nHitboxSet);
		NETVAR(float, DT_BasePlayer, m_flSimulationTime);
		NETVAR(float, DT_BasePlayer, m_flAnimTime);
		NETVAR(float, DT_BasePlayer, m_flNextAttack);
		NETVAR(QAngle, DT_BasePlayer, m_angRotation);
		NETVAR(int, DT_BasePlayer, m_lifeState);
		NETVAR(int, DT_BasePlayer, m_iHealth);
		NETVAR(Valve::EHANDLE, DT_BasePlayer, m_hObserverTarget);
		NETVAR(int, DT_BasePlayer, m_iObserverMode);
		NETVAR(int, DT_CSPlayer, m_ArmorValue);
		NETVAR(bool, DT_CSPlayer, m_bHasHelmet);
		NETVAR(float, DT_BasePlayer, m_flLaggedMovementValue);
		NETVAR(int, DT_BasePlayer, m_nTickBase);
		NETVAR(QAngle, DT_BasePlayer, m_vecPunchAngleVel);
		NETVAR(QAngle, DT_BasePlayer, m_vecPunchAngle);
		NETVAR(Vector, DT_BasePlayer, m_vecBaseVelocity);
		NETVAR(int, DT_BaseEntity, m_CollisionGroup);
		NETVAR(int, DT_BaseEntity, m_Collision);
		NETVAR(int, DT_BasePlayer, m_iShotsFired);
		NETVAR(float, DT_BasePlayer, m_flFallVelocity);
		NETVAR(float, DT_BasePlayer, m_flCycle);
		NETVAR(int, DT_BasePlayer, m_nSequence);
		NETVAR(float, DT_CSPlayer, m_flVelocityModifier);
		NETVAR(float, DT_BaseAnimating, m_flPlaybackRate);
		NETVAR(Vector, DT_BaseViewModel, m_vecLadderDir);
		NETVAR(Valve::EHANDLE, DT_BasePlayer, m_hGroundEntity);
		NETVAR(Vector, DT_BaseFlex, m_viewtarget);
		//NETVAR(Vector, DT_BaseEntity, m_vecOrigin);
		//NETVAR(Vector, DT_BasePlayer, m_vecViewOffset);
		VFUNCN0( ItemPreFrame, 0x324 );
		VFUNCN0( ItemPostFrame, 0x328 );

		Color m_clrRender( )
		{
			return *( Color* )( ( DWORD ) this + 0x58 );
		}

		bool IsSpawnProtectedPlayer( )
		{
			return ( this->m_clrRender( ).a( ) < 255 );
		}

		inline Vector m_vecOrigin( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0x29C );
		}

		inline Vector& m_vecViewOffset( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0xD4 );
		}

		inline Vector& m_vecNetworkOrigin( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0x204 );
		}

		inline QAngle& m_angNetworkAngles( )
		{
			return *( QAngle* )( ( DWORD_PTR ) this + 0x238 );
		}

		inline int& m_MoveType( )
		{
			return *( int* )( ( DWORD_PTR ) this + 0x134 );
		}

		/*
		class m_flPoseParameter
		{
		public:
			inline float& _000( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 ); }
			inline float& _001( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 ); }
			inline float& _002( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 2 ); }
			inline float& _003( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 3 ); }
			inline float& _004( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 4 ); }
			inline float& _005( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 5 ); }
			inline float& _006( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 6 ); }
			inline float& _007( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 7 ); }
			inline float& _008( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 8 ); }
			inline float& _009( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 9 ); }
			inline float& _010( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 10 ); }
			inline float& _011( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 11 ); }
			inline float& _012( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 12 ); }
			inline float& _013( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 13 ); }
			inline float& _014( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 14 ); }
			inline float& _015( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 15 ); }
			inline float& _016( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 16 ); }
			inline float& _017( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 17 ); }
			inline float& _018( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 18 ); }
			inline float& _019( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 19 ); }
			inline float& _020( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 20 ); }
			inline float& _021( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 21 ); }
			inline float& _022( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 22 ); }
			inline float& _023( ){ return *( float* )( ( DWORD_PTR ) this + 0x518 + 0x4 * 23 ); }
		};
		m_flPoseParameter m_flPoseParameter;
		*/

		inline float& m_flFriction( )
		{
			return *( float* )( ( DWORD_PTR ) this + 0x1D0 );
		}

		inline float& m_flMaxspeed( )
		{
			return *( float* )( ( DWORD_PTR ) this + 0xDA0 );
		}

		inline float& m_flOldAnimTime( )
		{
			return *( float* )( ( DWORD_PTR ) this + 0x64 );
		}

		inline float& m_flOldSimulationTime( )
		{
			return *( float* )( ( DWORD_PTR ) this + 0x6C );
		}

		inline PVOID CollisionProperty( )
		{
			return ( PVOID )( ( DWORD_PTR ) this + 0x2B8 );
		}

		inline void AddEFlags( DWORD flags )
		{
			PINT piEFlags = ( PINT )( ( DWORD_PTR ) this + 0x130 );
			*piEFlags |= flags;
		}

		inline matrix3x4_t m_rgflCoordinateFrame( )
		{
			return *( matrix3x4_t* )( ( DWORD_PTR ) this + 0x2B8 - 0x4C );
		}

		inline Vector m_vecMins( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0x168 );
		}

		inline Vector m_vecMaxs( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0x174 );
		}

		inline QAngle& m_angEyeAngles( )
		{
			/*
			QAngle angEyeAngles;
			angEyeAngles[ 0 ] = *( float* )( ( DWORD_PTR ) this + 0x101C );
			angEyeAngles[ 1 ] = *( float* )( ( DWORD_PTR ) this + 0x1020 );
			return angEyeAngles;
			*/
			return *( QAngle* )( ( DWORD ) this + 0x101C );
		}

		/*
		inline float& m_flFallVelocity( )
		{
			return *( float* )( ( DWORD_PTR ) this + 0x58 );
		}
		*/

		inline Vector& GetVelocity( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0xE0 );
		}

		inline Vector& EyePosition( )
		{
			return GetAbsOrigin( ) + m_vecViewOffset( ); // + m_vecVelocity( ) * g_pGlobals->interval_per_tick;
		}

		inline Vector& GetAbsVelocity( )
		{
			return *( Vector* )( ( DWORD_PTR ) this + 0xEC );
		}

		inline bool IsNextAttack( )
		{
			return ( m_flNextAttack( ) <= g_pGlobals->curtime );
		}

		inline void SetTickBase( int TickBase )
		{
			int *TickBasePtr = ( int* )( ( DWORD_PTR ) this + 0xE08 );
			*TickBasePtr = TickBase;
		}

		inline QAngle& GetPunchAngle( )
		{
			return *( QAngle* )( ( DWORD_PTR ) this + 0xBB0 );
		}

		inline QAngle& GetFixedPunchAngle( )
		{
			
		}

		inline int LookupPoseParameter( const char* name )
		{
			typedef int( __thiscall* LookupPoseParameter_t )( void*, const char* );
			return ( ( LookupPoseParameter_t )( ( ( DWORD ) 0x24033F40 ) ) )( this, name );
		}

		inline void SetAbsOrigin( const Vector& absOrigin )
		{
			typedef void( __thiscall* SetAbsOrigin_t )( void*, const Vector& );
			( ( SetAbsOrigin_t )( ( DWORD ) 0x24045620 ) )( this, absOrigin );
		}

		inline void SetAbsAngles( const QAngle& absAngles )
		{
			typedef void( __thiscall* SetAbsAngles_t )( void*, const QAngle& );
			( ( SetAbsAngles_t )( ( DWORD ) 0x24045720 ) )( this, absAngles );
		}

		inline void SetCycle( const float& flCycle )
		{
			typedef void( __thiscall* SetCycle_t )( void*, const float& );
			( ( SetCycle_t )( ( DWORD ) 0x24031BD0 ) )( this, flCycle );
		}

		inline void SetSequence( const int& nSequence )
		{
			typedef void( __thiscall* SetSequence_t )( void*, const int& );
			( ( SetSequence_t )( ( DWORD ) 0x24038800 ) )( this, nSequence );
		}

		inline void InvalidateBoneCache( )
		{
			typedef void( __thiscall* InvalidateBoneCache_t )( void* );
			( ( InvalidateBoneCache_t )( ( DWORD ) 0x240317F0 ) )( this );
		}

		inline void SetLocalOrigin( const Vector& vecLocalOrigin )
		{
			typedef void( __thiscall* SetLocalOrigin_t )( void*, const Vector& );
			( ( SetLocalOrigin_t )( ( DWORD ) 0x240417B0 ) )( this, vecLocalOrigin );
		}

		inline void SetLocalAngles( const QAngle& angLocalAngles )
		{
			typedef void( __thiscall* SetLocalAngles_t )( void*, const QAngle& );
			( ( SetLocalAngles_t )( ( DWORD ) 0x24041880 ) )( this, angLocalAngles );
		}
	};
};

#endif //__BASEPLAYER_H__