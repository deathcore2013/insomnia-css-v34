/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __IPANEL_H__
#define __IPANEL_H__

#include "VfuncTemplates.h"


namespace Valve
{
	namespace vgui
	{
		typedef unsigned int VPANEL;

#define CLASSNAME IPanel
		class IPanel
		{
		public:
			VFUNCN3( PaintTraverse, 0xA0, VPANEL, bool, bool );
			VFUNCR1( GetName, Index2Offset( 35 ), const char*, VPANEL );
		};
	};
};


#endif //__IPANEL_H__