/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __MATERIALSYSTEM_H__
#define __MATERIALSYSTEM_H__
#include "VfuncTemplates.h"
#include <Windows.h>

#define SIZEOFKEYVALUES 40
namespace Valve
{
	enum MaterialVarFlags_t
	{
		MATERIAL_VAR_DEBUG					  = (1 << 0),
		MATERIAL_VAR_NO_DEBUG_OVERRIDE		  = (1 << 1),
		MATERIAL_VAR_NO_DRAW				  = (1 << 2),
		MATERIAL_VAR_USE_IN_FILLRATE_MODE	  = (1 << 3),
		MATERIAL_VAR_VERTEXCOLOR			  = (1 << 4),
		MATERIAL_VAR_VERTEXALPHA			  = (1 << 5),
		MATERIAL_VAR_SELFILLUM				  = (1 << 6),
		MATERIAL_VAR_ADDITIVE				  = (1 << 7),
		MATERIAL_VAR_ALPHATEST				  = (1 << 8),
		MATERIAL_VAR_MULTIPASS				  = (1 << 9),
		MATERIAL_VAR_ZNEARER				  = (1 << 10),
		MATERIAL_VAR_MODEL					  = (1 << 11),
		MATERIAL_VAR_FLAT					  = (1 << 12),
		MATERIAL_VAR_NOCULL					  = (1 << 13),
		MATERIAL_VAR_NOFOG					  = (1 << 14),
		MATERIAL_VAR_IGNOREZ				  = (1 << 15),
		MATERIAL_VAR_DECAL					  = (1 << 16),
		MATERIAL_VAR_ENVMAPSPHERE			  = (1 << 17),
		MATERIAL_VAR_NOALPHAMOD				  = (1 << 18),
		MATERIAL_VAR_ENVMAPCAMERASPACE	      = (1 << 19),
		MATERIAL_VAR_BASEALPHAENVMAPMASK	  = (1 << 20),
		MATERIAL_VAR_TRANSLUCENT              = (1 << 21),
		MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
		MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING  = (1 << 23),
		MATERIAL_VAR_OPAQUETEXTURE			  = (1 << 24),
		MATERIAL_VAR_ENVMAPMODE				  = (1 << 25),
		MATERIAL_VAR_SUPPRESS_DECALS		  = (1 << 26),
		MATERIAL_VAR_HALFLAMBERT			  = (1 << 27),
		MATERIAL_VAR_WIREFRAME                = (1 << 28),
	};

	class KeyValues;
	class IMaterial;
	class IMaterialSystem;
	typedef unsigned short MaterialHandle_t;

#define CLASSNAME IMaterialSystem
	class IMaterialSystem
	{
	public:
		VFUNCR0( FirstMaterial, Index2Offset( 23 ), MaterialHandle_t );
		VFUNCR1( NextMaterial, Index2Offset( 24 ), MaterialHandle_t, MaterialHandle_t );
		VFUNCR0( InvalidMaterial, Index2Offset( 25 ), MaterialHandle_t );
		VFUNCR1( GetMaterial, Index2Offset( 26 ), IMaterial*, MaterialHandle_t );
		VFUNCR4( FindMaterial, Index2Offset( 27 ), IMaterial*, const char*, const char*, bool, const char* );
		VFUNCR2( CreateMaterial, Index2Offset( 123 ), IMaterial*, const char*, KeyValues* );
	};

#define CLASSNAME IMaterial
	class IMaterial
	{
	public:
		VFUNCR0( GetName, Index2Offset( 0 ), const char* );
		VFUNCR0( GetTextureGroupName, Index2Offset( 1 ), const char* );
		VFUNCN0( IncrementReferenceCount, Index2Offset( 12 ) );
		VFUNCN1( AlphaModulate, Index2Offset( 29 ), float );
		VFUNCN3( ColorModulate, Index2Offset( 30 ), float, float, float );
		VFUNCN2( SetMaterialVarFlag, Index2Offset( 31 ), MaterialVarFlags_t, bool );
	};

	class IBaseFileSystem;
	class CUtlBuffer;
	class Color;

	class KeyValues
	{
	public:
		KeyValues( const char* szName )
		{
			static DWORD dwInitKeyValues = ( ( DWORD ) GetModuleHandleA( "client.dll" ) + 0x211B00 );
			typedef void ( __thiscall* Constr_t )( KeyValues*, const char* );
			static Constr_t Constr = 0;
			( ( Constr_t )( dwInitKeyValues ) )( this, szName );
		}

		inline void InitKeyValues( KeyValues* keyValues, const char* szName )
		{
			static DWORD dwInitKeyValues = ( ( DWORD ) GetModuleHandleA( "client.dll" ) + 0x211B00 );
			typedef void (__thiscall* InitKeyValues_t )( KeyValues*, const char* );
			( ( InitKeyValues_t )( dwInitKeyValues ) )( keyValues, szName );
		}

		inline void LoadFromBuffer( const char* resourceName, const char* pBuffer )
		{
			static DWORD dwLoadFromBuffer = ( ( DWORD ) GetModuleHandleA( "client.dll" ) + 0x214720 );
			typedef void( __thiscall* LoadFromBuffer )( void*, const char*, const char*, void*, const char* );
			( ( LoadFromBuffer )( dwLoadFromBuffer ) )( this, resourceName, pBuffer, NULL, NULL );
		}

		KeyValues& operator=( KeyValues& src );

		enum types_t
		{
			TYPE_NONE = 0,
			TYPE_STRING,
			TYPE_INT,
			TYPE_FLOAT,
			TYPE_PTR,
			TYPE_WSTRING,
			TYPE_COLOR,
			TYPE_NUMTYPES, 
		};

	private:
		KeyValues( KeyValues& );
		~KeyValues( );

		int m_iKeyName;
		char *m_sValue;
		wchar_t *m_wsValue;

		// we don't delete these
		union
		{
			int m_iValue;
			float m_flValue;
			void *m_pValue;
			unsigned char m_Color[4];
		};
	
		types_t m_iDataType;
		short m_iAllocationSize;

		KeyValues *m_pPeer;
		KeyValues *m_pSub;
		KeyValues *m_pChain;
		bool	   m_bHasEscapeSequences;

		char _crap[SIZEOFKEYVALUES];
	};
};
#endif //__MATERIALSYSTEM_H__