/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __GAMEMOVEMENT_H__
#define __GAMEMOVEMENT_H__
#include "VfuncTemplates.h"

inline void**& get_vtable( void* inst, size_t offset = 0 )
{
	return *reinterpret_cast<void***>( (size_t)inst + offset );
}
inline const void** get_vtable( const void* inst, size_t offset = 0 )
{
	return *reinterpret_cast<const void***>( (size_t)inst + offset );
}
template< typename Fn >
inline Fn call_vfunc( const void* inst, size_t index, size_t offset = 0 )
{
	return reinterpret_cast<Fn>( get_vtable( inst, offset )[ index ] );
}

namespace Valve
{
	class BaseEntity;
	class CMoveData;
#define CLASSNAME IGameMovement
	class IGameMovement
	{
	public:
		VFUNCN2(ProcessMovement, 0x4, Valve::BaseEntity*, void*);
		VFUNCN0(DecayPunchAngle, Index2Offset( 7 ));
	};

};

#endif //__GAMEMOVEMENT_H__