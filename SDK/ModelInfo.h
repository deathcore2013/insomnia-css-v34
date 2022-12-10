/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __MODELINFO_H__
#define __MODELINFO_H__

#include "VfuncTemplates.h"
#include "ClientClass.h"
#include "Vector.h"
typedef unsigned char byte;

namespace Valve
{
	struct model_t;
	struct mstudiobbox_t
	{

		int					bone;
		int					group;
		Vector				bbmin;
		Vector				bbmax;	
		int					szhitboxnameindex;
		int					unused[8];
		char* pszHitboxName()
		{
			if( szhitboxnameindex == 0 )
				return "";

			return ((char*)this) + szhitboxnameindex;
		}
	};

	struct mstudiohitboxset_t
	{
		int					sznameindex;
		inline char * const	pszName( void ) const { return ((char *)this) + sznameindex; }
		int					numhitboxes;
		int					hitboxindex;
		inline mstudiobbox_t *pHitbox( int i ) const { return (mstudiobbox_t *)(((byte *)this) + hitboxindex) + i; };
	};

	struct mstudioposeparamdesc_t
	{
		int					sznameindex;
		inline char * const pszName( void ) const { return ((char *)this) + sznameindex; }
		int					flags;	// ????
		float				start;	// starting value
		float				end;	// ending value
		float				loop;	// looping range, 0 for no looping, 360 for rotations, etc.
	};

	struct studiohdr_t
	{
		int					id;
		int					version;
		long				checksum;
		char				name[64];
		int					length;
		Vector				eyeposition;
		Vector				illumposition;
		Vector				hull_min;
		Vector				hull_max;
		Vector				view_bbmin;
		Vector				view_bbmax;
		int					flags;
		int					numbones;
		int					boneindex;
		int					numbonecontrollers;
		int					bonecontrollerindex;
		int					numhitboxsets;
		int					hitboxsetindex;
		mstudiohitboxset_t	*pHitboxSet( int i ) const 
		{ 
			return (mstudiohitboxset_t *)(((byte *)this) + hitboxsetindex ) + i; 
		};
		inline mstudiobbox_t *pHitbox( int i, int set ) const 
		{ 
			mstudiohitboxset_t const *s = pHitboxSet( set );
			if ( !s )
				return 0;

			return s->pHitbox( i );
		};
		inline int			iHitboxCount( int set ) const
		{
			mstudiohitboxset_t const *s = pHitboxSet( set );
			if ( !s )
				return 0;

			return s->numhitboxes;
		};
		int					numlocalanim;
		int					localanimindex;
		int					numlocalseq;
		int					localseqindex;
		mutable int			activitylistversion;
		mutable int			eventsindexed;
		int					numtextures;
		int					textureindex;
		int					numcdtextures;
		int					cdtextureindex;
		int					numskinref;
		int					numskinfamilies;
		int					skinindex;
		int					numbodyparts;		
		int					bodypartindex;
		int					numlocalattachments;
		int					localattachmentindex;
		int					numlocalnodes;
		int					localnodeindex;
		int					localnodenameindex;
		int					numflexdesc;
		int					flexdescindex;
		int					numflexcontrollers;
		int					flexcontrollerindex;
		int					numflexrules;
		int					flexruleindex;
		int					numikchains;
		int					ikchainindex;
		int					nummouths;
		int					mouthindex;
		int					numlocalposeparameters;
		int					localposeparamindex;
		int					surfacepropindex;
		int					keyvalueindex;
		int					keyvaluesize;
		int					numlocalikautoplaylocks;
		int					localikautoplaylockindex;
		float				mass;
		int					contents;
		int					numincludemodels;
		int					includemodelindex;
		mutable void		*virtualModel;
		int					szanimblocknameindex;
		int					numanimblocks;
		int					animblockindex;
		mutable void		*animblockModel;
		int					bonetablebynameindex;
		void				*pVertexBase;
		void				*pIndexBase;
		byte				constdirectionallightdot;
		byte				rootLOD;
		byte				numAllowedRootLODs;
		byte				unused[1];
		int					unused4;
		int					numflexcontrollerui;
		int					flexcontrolleruiindex;
		int					unused3[2];
		int					studiohdr2index;
		int					unused2[1];
	};

#define CLASSNAME IVModelInfo
	class IVModelInfo
	{
	public:
		VFUNCR1( GetModelName, Index2Offset( 3 ), const char*, const model_t* );
		VFUNCR1( GetStudiomodel, 0x6C, Valve::studiohdr_t*, void* );
		VFUNCN3( GetModelMaterials, Index2Offset( 16 ), const model_t*, int, IMaterial** );
	};

};

#endif //__MODELINFO_H__