/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __GLOBALVARSBASE_H__
#define __GLOBALVARSBASE_H__

namespace Valve
{

#define CLASSNAME CGlobalVarsBase
	class CGlobalVarsBase
	{
	public:
		float			realtime;
		int				framecount;
		float			absoluteframetime;
		float			curtime; //0x0C
		float			frametime; //0x10
		int				maxClients;
		int				tickcount;
		float			interval_per_tick; //0x1C
		float			interpolation_amount;
		int				simTicksThisFrame;
		int				network_protocol;
		void*			pSaveData;
		bool			m_bClient;
		int				nTimestampNetworkingBase;   
		int				nTimestampRandomizeWindow;  
	};

};

#endif //__GLOBALVARSBASE_H__