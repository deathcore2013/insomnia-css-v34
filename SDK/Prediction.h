/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __PREDICTION_H__
#define __PREDICTION_H__
#include "VfuncTemplates.h"

namespace Valve
{
	class BaseEntity;
	class CUserCmd;
	class IMoveHelper;
	class CMoveData;

#define CLASSNAME IPrediction
	class IPrediction
	{
	public:
		VFUNCR0(InPrediction, 0x40, bool);		
		VFUNCN4(Update, 0xC, int, bool, int, int );
		VFUNCN4(_Update, 0x5C, bool, bool, int, int );		
		VFUNCN3(FinishMove, 0x54, BaseEntity*, CUserCmd*, void*);
		VFUNCN1(SetViewAngles, Index2Offset( 16 ), QAngle& );
		VFUNCN1(SetLocalViewAngles, Index2Offset( 18 ), QAngle& );
		VFUNCN2(PreEntityPacketReceived, Index2Offset( 4 ), int, int );
		VFUNCN3(RunCommand, 0x4C, BaseEntity*, CUserCmd*, IMoveHelper*);
		VFUNCN4(SetupMove, 0x50, BaseEntity*, CUserCmd*, IMoveHelper*, void*);
	};
	class CMoveData
	{
		char _crap[ 0x200 ];
	};
};

#endif //__PREDICTION_H__