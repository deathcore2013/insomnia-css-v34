/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __SDK_INCLUDES_H__
#define __SDK_INCLUDES_H__
#define SECURITY_WIN32

//Macro redefinition and double -> float 
#pragma warning( disable : 4005 4244 )

#include <Windows.h>

#define Index2Offset( index ) ( DWORD )( ( int )( index * 0x4 ) )

#pragma comment( lib, "SDK/tier1.lib" )
#include "SDK/NetvarManager.h"
#include "SDK/Buttons.h"
#include "SDK/BaseClient.h"
#include "SDK/INetChannelInfo.h"
#include "SDK/EngineClient.h"
#include "SDK/ClientEntityList.h"
#include "SDK/Physics.h"
#include "SDK/Prediction.h"
#include "SDK/MaterialSystem.h"
#include "SDK/ModelInfo.h"
#include "SDK/MoveHelper.h"
#include "SDK/Input.h"
#include "SDK/DebugOverlay.h"
#include "SDK/IPanel.h"
#include "SDK/ISurface.h"
#include "SDK/GameMovement.h"
#include "SDK/Cvar.h"
#include "SDK/CSPlayer.h"
#include "SDK/CSWeapon.h"
#include "SDK/IVModelRender.h"
#include "SDK/IVRenderView.h"
#include "SDK/InterfaceManager.h"
#include "SDK/EngineTrace.h"

#endif //__SDK_INCLUDES_H__