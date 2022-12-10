/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __INPUT_H__
#define __INPUT_H__

#include "VfuncTemplates.h"
#include "checksum_crc.h"
#include "Vector.h"

namespace Valve
{
	class IInput;
	class CUserCmd;

	class CUserCmd
	{
	public:
		virtual ~CUserCmd();
		
		CUserCmd& operator =( const CUserCmd& src )
		{
			if ( this == &src )
				return *this;

			command_number		= src.command_number;
			tick_count			= src.tick_count;
			viewangles			= src.viewangles;
			forwardmove			= src.forwardmove;
			sidemove			= src.sidemove;
			upmove				= src.upmove;
			buttons				= src.buttons;
			impulse				= src.impulse;
			weaponselect		= src.weaponselect;
			weaponsubtype		= src.weaponsubtype;
			random_seed			= src.random_seed;
			mousedx				= src.mousedx;
			mousedy				= src.mousedy;

			hasbeenpredicted	= src.hasbeenpredicted;
			return *this;
		}
		
		CRC32_t GetChecksum( void ) const
		{
			CRC32_t crc;

			CRC32_Init( &crc );
			CRC32_ProcessBuffer( &crc, &command_number, sizeof( command_number ) );
			CRC32_ProcessBuffer( &crc, &tick_count, sizeof( tick_count ) );
			CRC32_ProcessBuffer( &crc, &viewangles, sizeof( viewangles ) );    
			CRC32_ProcessBuffer( &crc, &forwardmove, sizeof( forwardmove ) );   
			CRC32_ProcessBuffer( &crc, &sidemove, sizeof( sidemove ) );      
			CRC32_ProcessBuffer( &crc, &upmove, sizeof( upmove ) );         
			CRC32_ProcessBuffer( &crc, &buttons, sizeof( buttons ) );		
			CRC32_ProcessBuffer( &crc, &impulse, sizeof( impulse ) );        
			CRC32_ProcessBuffer( &crc, &weaponselect, sizeof( weaponselect ) );	
			CRC32_ProcessBuffer( &crc, &weaponsubtype, sizeof( weaponsubtype ) );
			CRC32_ProcessBuffer( &crc, &random_seed, sizeof( random_seed ) );
			CRC32_ProcessBuffer( &crc, &mousedx, sizeof( mousedx ) );
			CRC32_ProcessBuffer( &crc, &mousedy, sizeof( mousedy ) );
			CRC32_Final( &crc );

			return crc;
		}

		// For matching server and client commands for debugging
		int		command_number;
	
		// the tick the client created this command
		int		tick_count;
	
		// Player instantaneous view angles.
		QAngle	viewangles;     
		// Intended velocities
		//	forward velocity.
		float	forwardmove;   
		//  sideways velocity.
		float	sidemove;      
		//  upward velocity.
		float	upmove;         
		// Attack button states
		int		buttons;		
		// Impulse command issued.
		unsigned char    impulse;        
		// Current weapon id
		int		weaponselect;	
		int		weaponsubtype;

		int		random_seed;	// For shared random functions

		short	mousedx;		// mouse accum in x from create move
		short	mousedy;		// mouse accum in y from create move

		// Client only, tracks whether we've predicted this command at least once
		bool	hasbeenpredicted;

	};
#define CLASSNAME IInput
	class IInput
	{
	public:
		VFUNCR1(GetUserCmd, 0x20, CUserCmd*, int);
		VFUNCR0(CAM_IsThirdPerson, Index2Offset( 26 ), bool); // lub 28
		VFUNCN0(CAM_ToThirdPerson, Index2Offset( 28 ) );

		inline bool& m_fCameraInThirdPerson( )
		{ 
			return *( bool* )( 0x8D + ( DWORD_PTR ) this ); 
		}

		inline Vector& m_vecCameraOffset( )
		{
			return *( Vector* )( 0x25 + ( DWORD_PTR ) this ); 
		}
	};

#define CLASSNAME IClientMode
	class IClientMode
	{
	public:
		VFUNCN1( OverrideView, Index2Offset( 16 ), CViewSetup* );
		VFUNCN2( CreateMove, Index2Offset( 21 ), float, CUserCmd* );
	};	

#define CLASSNAME IGameEvent
	class IGameEvent
	{
	public:
		VFUNCR0(GetName, Index2Offset( 1 ), const char*);
		VFUNCR2(GetBool, Index2Offset( 5 ), bool, const char*, bool );
		VFUNCR2(GetInt, Index2Offset( 6 ), int, const char*, int);
		VFUNCR2(GetFloat, Index2Offset( 7 ), float, const char*, float);
		VFUNCR2(GetString, Index2Offset( 8 ), const char*, const char*, const char*);
	};

	class IGameEventListener2
	{
	public:
		virtual ~IGameEventListener2( ) { };
		virtual void FireGameEvent( IGameEvent* ) = 0;
	};
 
#define CLASSNAME IGameEventManager2
	class IGameEventManager2
	{
	public:
		VFUNCR3( AddListener, Index2Offset( 3 ), bool, IGameEventListener2*, const char*, bool );
		VFUNCR1( FireEventClientSide, Index2Offset( 8 ), bool, IGameEvent* );
	};
};

#endif //__INPUT_H__