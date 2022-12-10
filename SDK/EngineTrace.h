/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __ENGINETRACE_H__
#define __ENGINETRACE_H__
#include "VfuncTemplates.h"
#include "Vector.h"

namespace Valve
{
	//class BaseEntity;
	class IHandleEntity;

	struct cplane_t
	{
		Vector  normal;
		float   dist;
		BYTE    type;
		BYTE    signbits;
		BYTE    pad[2];
	};

	struct csurface_t
	{
		const char* name;
		short surfaceProps;
		unsigned short flags;
	};

	class trace_t
	{
	public:
		Vector startpos;
		Vector endpos;
		cplane_t plane;
		float fraction;
		int  contents;
		unsigned short dispFlags;
		bool allsolid;
		bool startsolid;
		float fractionleftsolid;
		csurface_t surface;
		int hitgroup;
		short physicsbone;
		BaseEntity* m_pEnt;
		int hitbox;
	};

	class Ray_t
	{
	public:
		Vector  m_Start;
		Vector  m_Delta;
		Vector  m_StartOffset;
		Vector  m_Extents;

		bool    m_IsRay;
		bool    m_IsSwept;

		inline void Init( const Vector& vecStart, const Vector& vecEnd )
		{
			m_Delta = vecEnd - vecStart;
			m_IsSwept = ( m_Delta.LengthSqr( ) != 0 );
			m_Extents.x = m_Extents.y = m_Extents.z = 0.0f;
			m_IsRay = true;
			m_StartOffset.x = m_StartOffset.y = m_StartOffset.z = 0.0f;
			m_Start = vecStart;
		}

		inline void Init( const Vector& vecStart, const Vector& vecEnd, const Vector& vecMins, const Vector& vecMaxs )
		{
			VectorSubtract( vecEnd, vecStart, m_Delta );

			m_IsSwept = ( m_Delta.LengthSqr( ) != 0 );

			VectorSubtract( vecMins, vecMaxs, m_Extents );
			m_Extents *= 0.5f;
			m_IsRay = ( m_Extents.LengthSqr( ) < 1e-6 );

			VectorAdd( vecMins, vecMaxs, m_StartOffset );
			m_StartOffset *= 0.5f;
			VectorAdd( vecStart, m_StartOffset, m_Start );
			m_StartOffset *= -1.0f;
		}
	};

	class ITraceFilter
	{
	public:
		virtual bool ShouldHitEntity( IHandleEntity* pEntity, int contentsMask ) = 0;
		virtual int GetTraceType( ) const = 0;
	};

	class TraceFilterSkipTwoEntities:
		public ITraceFilter
	{
	public:
		TraceFilterSkipTwoEntities( IHandleEntity* skip1, IHandleEntity* skip2 )
		{
			m_passEntity1 = skip1;
			m_passEntity2 = skip2;
		}
		virtual bool ShouldHitEntity( IHandleEntity* pEntity, int contentsMask )
		{
			return ( ( pEntity != m_passEntity1 ) && ( pEntity != m_passEntity2 ) );
		}
		virtual int GetTraceType() const
		{
			return 0;
		}
		void Set( IHandleEntity* skip1, IHandleEntity* skip2 )
		{
			m_passEntity1 = skip1;
			m_passEntity2 = skip2;
		}

		IHandleEntity* m_passEntity1;
		IHandleEntity* m_passEntity2;
	};

	/*
	class CTraceFilterWorldOnly:
		public ITraceFilter
	{
	public:
		CTraceFilterWorldOnly( IHandleEntity* skip )
		{
			m_passEntity1 = skip;
		}

		bool ShouldHitEntity( IHandleEntity *pServerEntity, int contentsMask )
		{
			return ( pServerEntity != m_passEntity1 );
		}

		virtual int GetTraceType() const
		{
			return 1;
		}

		IHandleEntity* m_passEntity1;
	};*/

	class CTraceFilterWorldOnly : public ITraceFilter
	{
	public:
		bool ShouldHitEntity( IHandleEntity *pServerEntity , int contentsMask )
		{
			Valve::BaseEntity *Entity = ( Valve::BaseEntity* ) g_pClientEntityList->GetClientEntityFromHandle( pServerEntity->GetRefEHandle( ) );
			return( Entity->entindex( ) <= 0 && Entity->entindex( ) > 64 );
		}
		virtual int GetTraceType() const
		{
			return 0;
		}
	};




#define CLASSNAME IEngineTrace
	class IEngineTrace
	{
	public:
		VFUNCR2(GetPointContents, Index2Offset( 0 ), int, const Vector &, Valve::IHandleEntity**);
		VFUNCN4(TraceRay, 0x10, const Ray_t &, unsigned int, ITraceFilter*, trace_t*);
		VFUNCN4(ClipRayToEntity, 0x8, const Ray_t&, unsigned int, IHandleEntity*, trace_t*);
	};
};

#endif //__ENGINETRACE_H__