/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __DEBUGOVERLAY_H__
#define __DEBUGOVERLAY_H__
#include "VfuncTemplates.h"
#include "Vector.h"

namespace Valve
{
#define CLASSNAME IVDebugOverlay
	class IVDebugOverlay
	{
	public:
		VFUNCR2(ScreenPosition, 0x24, int, const Vector&, const Vector&);
	};

};

#endif //__DEBUGOVERLAY_H__