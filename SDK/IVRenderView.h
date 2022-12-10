#ifndef __IVRENDERVIEW_H__
#define __IVRENDERVIEW_H__
#include "VfuncTemplates.h"

namespace Valve
{
#define CLASSNAME IVRenderView
	class IVRenderView
	{
	public:
		VFUNCN1( SetBlend, Index2Offset( 4 ), float );
		VFUNCN1( SetColorModulation, Index2Offset( 6 ), float const* );
	};
};

#endif //__IVRENDERVIEW_H__