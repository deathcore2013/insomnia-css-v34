/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __BASECLIENT_H__
#define __BASECLIENT_H__
#include "VfuncTemplates.h"
#include "ClientClass.h"

namespace Valve
{
	enum ClientFrameStage_t
	{
		FRAME_UNDEFINED=-1,			// (haven't run any frames yet)
		FRAME_START,

		// A network packet is being recieved
		FRAME_NET_UPDATE_START,
			// Data has been received and we're going to start calling PostDataUpdate
			FRAME_NET_UPDATE_POSTDATAUPDATE_START,
			// Data has been received and we've called PostDataUpdate on all data recipients
			FRAME_NET_UPDATE_POSTDATAUPDATE_END,
		// We've received all packets, we can now do interpolation, prediction, etc..
		FRAME_NET_UPDATE_END,

		// We're about to start rendering the scene
		FRAME_RENDER_START,
		// We've finished rendering the scene.
		FRAME_RENDER_END
	};

	class ClientClass;

	class CViewSetup
	{
	public:
		int			context;			
		int			x;					
		int			y;					
		int			width;				
		int			height;				
		bool		clearColor;			
		bool		clearDepth;			
		bool		bForceClearWholeRenderTarget;
		bool		m_bOrtho;			
		float		m_OrthoLeft;		
		float		m_OrthoTop;
		float		m_OrthoRight;
		float		m_OrthoBottom;
		float		fov;				
		float		fovViewmodel;		
	};

#define CLASSNAME IBaseClientDLL
	class IBaseClientDLL
	{
	public:
		VFUNCR0(GetAllClasses, 0x14, Valve::ClientClass*);
		VFUNCR3(IN_KeyEvent, 0x44, int, int, int, const char* );
		VFUNCN3(CreateMove, 0x48, int, float, bool);
		VFUNCN1(FrameStageNotify, 0x80, ClientFrameStage_t);
		VFUNCN3(RenderView, 0x60, CViewSetup&, int, bool );
	};
};

#endif //__BASECLIENT_H__