/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __CVAR_H__
#define __CVAR_H__
#include "VfuncTemplates.h"
#include "InterfaceManager.h"

namespace Valve
{
	#define FCVAR_NONE				0 
	#define FCVAR_UNREGISTERED		(1<<0)	
	#define FCVAR_LAUNCHER			(1<<1) 
	#define FCVAR_GAMEDLL			(1<<2)	
	#define FCVAR_CLIENTDLL			(1<<3) 
	#define FCVAR_MATERIAL_SYSTEM	(1<<4)	
	#define FCVAR_PROTECTED			(1<<5) 
	#define FCVAR_SPONLY			(1<<6) 
	#define	FCVAR_ARCHIVE			(1<<7)	
	#define	FCVAR_NOTIFY			(1<<8)	
	#define	FCVAR_USERINFO			(1<<9)	
	#define FCVAR_PRINTABLEONLY		(1<<10)
	#define FCVAR_UNLOGGED			(1<<11)
	#define FCVAR_NEVER_AS_STRING	(1<<12)
	#define FCVAR_REPLICATED		(1<<13)
	#define FCVAR_CHEAT				(1<<14)
	#define FCVAR_STUDIORENDER		(1<<15)
	#define FCVAR_DEMO				(1<<16)
	#define FCVAR_DONTRECORD		(1<<17)
	#define FCVAR_PLUGIN			(1<<18)

#define CLASSNAME ConVar
	class ConVar
	{
	public:
		VFUNCR0(GetName, 0x10, const char*);
		float GetFloat( )
        {
			return m_fValue;
        }
 
        int GetInt( )
        {
			return m_nValue;
        }
 
        bool GetBool( )
        {
			return !!GetInt( );
        }

		VFUNCN1(SetValue, Index2Offset( 11 ), const char* );
		VFUNCN1(SetValue, Index2Offset( 10 ), float);
		VFUNCN1(SetValue, Index2Offset( 9 ), int);

	private:
		unsigned char __pad0[0x28];
		float m_fValue;
        int m_nValue;
	};

#define CLASSNAME ConCommandBase
	class ConCommandBase
	{
	public:
		ConCommandBase( void );
		ConCommandBase( char const *pName, char const *pHelpString = 0, int flags = 0 );
		virtual						~ConCommandBase( void );
		virtual	bool				IsCommand( void ) const;
		virtual bool				IsBitSet( int flag ) const;
		virtual void				AddFlags( int flags );
		virtual char const			*GetName( void ) const;
		virtual char const			*GetHelpText( void ) const;	
		const ConCommandBase		*GetNext( void ) const;
		virtual bool				IsRegistered( void ) const;
		virtual void				Create( char const *pName, char const *pHelpString = 0, int flags = 0 );
		virtual void				Init();
		ConCommandBase				*m_pNext;
		int							m_nFlags;
	};

	#define COMMAND_COMPLETION_MAXITEMS		64
	#define COMMAND_COMPLETION_ITEM_LENGTH	64
	typedef void ( *FnChangeCallback )( ConVar *var, char const *pOldString );
	typedef void ( *FnCommandCallback )( void );
	typedef int  ( *FnCommandCompletionCallback )( char const *partial, char commands[ COMMAND_COMPLETION_MAXITEMS ][ COMMAND_COMPLETION_ITEM_LENGTH ] );

#define CLASSNAME ConCommand
	class ConCommand
	{
	friend class ConCommandBaseMgr;
	friend class CCvar;

	public:
		typedef ConCommandBase BaseClass;

									ConCommand( void );
									ConCommand( char const *pName, FnCommandCallback callback, 
										char const *pHelpString = 0, int flags = 0, FnCommandCompletionCallback completionFunc = 0 );

		virtual						~ConCommand( void );
		virtual	bool				IsCommand( void ) const;
		virtual int					AutoCompleteSuggest( char const *partial, char commands[ COMMAND_COMPLETION_MAXITEMS ][ COMMAND_COMPLETION_ITEM_LENGTH ] );
		virtual bool				CanAutoComplete( void );
		virtual void				Dispatch( void );
		virtual void				Create( char const *pName, FnCommandCallback callback, 
										char const *pHelpString = 0, int flags = 0, FnCommandCompletionCallback completionFunc = 0 );
	};

#define CLASSNAME ICvar
	class ICvar
	{
	public:
		VFUNCN1(RegisterConCommandBase, 0x10, ConCommandBase* );
		VFUNCR1(FindVar, 0x1C, ConVar*, const char*);
		VFUNCR0(GetCommands, 0x24, ConCommandBase*);
	};
};

#endif //__CVAR_H__