#ifndef __IVMODELRENDER_H__
#define __IVMODELRENDER_H__
#include "VfuncTemplates.h"

namespace Valve
{
	struct ModelRenderInfo_t
	{
		int flags;
		IClientRenderable* pRenderable;
		unsigned short instance;
		int entity_index;
		const void* pModel;
		Vector origin;
		Vector angles;
		int skin;
		int body;
		int hitboxset;
		const matrix3x4_t *pModelToWorld;
		const matrix3x4_t *pLightingOffset;
		const Vector *pLightingOrigin;

		ModelRenderInfo_t( )
		{
			pModelToWorld = NULL;
			pLightingOffset = NULL;
			pLightingOrigin = NULL;
		}
	};

#define CLASSNAME IVModelRender
	class IVModelRender
	{
	public:
		VFUNCN1( ForcedMaterialOverride, Index2Offset( 1 ), IMaterial* );
		VFUNCR1( DrawModelEx, Index2Offset( 19 ), int, ModelRenderInfo_t& );
	};
};

#endif //__IVMODELRENDER_H__