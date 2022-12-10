/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#include "InterfaceManager.h"
#include "../SdkIncludes.h"

using namespace HackInterfaces;

InterfaceManager* g_pInterfaceManager = NULL;

Valve::IBaseClientDLL*			g_pBaseClientDll;
Valve::IClientEntityList*		g_pClientEntityList;
Valve::IPrediction*				g_pPrediction;
Valve::IGameMovement*			g_pGameMovement;
Valve::IVEngineClient*			g_pEngineClient;
Valve::ICvar*					g_pCvar;
Valve::IVModelInfo*				g_pModelInfo;
Valve::IEngineTrace*			g_pEngineTrace;
Valve::IPhysicsSurfaceProps*	g_pPhysicsSurfaceProps;
Valve::vgui::IPanel*			g_pPanel;
Valve::vgui::ISurface*			g_pSurface;
Valve::IVDebugOverlay*			g_pDebugOverlay;
Valve::IVRenderView*			g_pRender;
Valve::IVModelRender*			g_pModelRender;
Valve::IMaterialSystem*			g_pMaterialSystem;
Valve::IInput*					g_pInput;
Valve::CGlobalVarsBase*			g_pGlobals;

InterfaceManager::InterfaceManager():
	m_mainModule("hl2.exe"),
	m_clientDll("client.dll"),
	m_engineDll("engine.dll"),
	m_vgui2Dll("vgui2.dll"),
	m_vguiMatSurfaceDll("vguimatsurface.dll"),
	m_materialSystemDll("MaterialSystem.dll"),
	m_vphysicsDll("vphysics.dll"),
	//m_tier0Dll("tier0.dll"),
	m_vstdlibDll("vstdlib.dll")
{
	m_ready = false;
}

bool InterfaceManager::init()
{
	printf("Init started\n");
	g_pBaseClientDll = (Valve::IBaseClientDLL*) m_clientDll.FindInterface("VClient");
	printf("%p\n", g_pBaseClientDll);
	g_pClientEntityList = (Valve::IClientEntityList*) m_clientDll.FindInterface("VClientEntityList");
	g_pPrediction = (Valve::IPrediction*) m_clientDll.FindInterface("VClientPrediction");	
	g_pGameMovement = (Valve::IGameMovement*) m_clientDll.FindInterface("GameMovement");
	g_pEngineClient = (Valve::IVEngineClient*) m_engineDll.FindInterface("VEngineClient");	
	g_pEngineTrace = (Valve::IEngineTrace*) m_engineDll.FindInterface("EngineTraceClient");	
	g_pDebugOverlay = (Valve::IVDebugOverlay*) m_engineDll.FindInterface("VDebugOverlay");
	g_pPanel = (Valve::vgui::IPanel*) m_vgui2Dll.FindInterface("VGUI_Panel");	
	g_pSurface = (Valve::vgui::ISurface*) m_vguiMatSurfaceDll.FindInterface("VGUI_Surface");	
	g_pPhysicsSurfaceProps = (Valve::IPhysicsSurfaceProps*) m_vphysicsDll.FindInterface("VPhysicsSurfaceProps");
	g_pModelInfo = (Valve::IVModelInfo*) m_engineDll.FindInterface("VModelInfoClient");
	g_pCvar = (Valve::ICvar*) m_engineDll.FindInterfaceNoBruteforce("VEngineCvar003");
	g_pRender = (Valve::IVRenderView*) m_engineDll.FindInterface("VEngineRenderView");
	g_pModelRender = (Valve::IVModelRender*) m_engineDll.FindInterface("VEngineModel");
	g_pDebugOverlay = (Valve::IVDebugOverlay*) m_engineDll.FindInterface("VDebugOverlay");
	g_pMaterialSystem = (Valve::IMaterialSystem*)  m_materialSystemDll.FindInterface("VMaterialSystem");

	PDWORD pdwClient = ( PDWORD )*( PDWORD ) g_pBaseClientDll;
	DWORD dwInitAddr = ( DWORD )( pdwClient[0] );

	for ( DWORD dwIter = 0; dwIter <= 0xFF; dwIter++ )
	{
		if ( *( PBYTE )( dwInitAddr + dwIter ) == 0xA3 )
		{
			g_pGlobals = ( Valve::CGlobalVarsBase* )*( PDWORD )*( PDWORD )( dwInitAddr + dwIter + 1 );
			break;
		}
	}
	if( !g_pGlobals ) printf("CGlobalVarsBase not found\n");

	dwInitAddr = ( DWORD )( pdwClient[18] );
	for ( DWORD dwIter = 0; dwIter <= 0xFF; dwIter++ )
	{
		if ( *( PBYTE )( dwInitAddr + dwIter ) == 0x0D )
		{
			g_pInput = (Valve::IInput*)*(PDWORD)*(PDWORD)( dwInitAddr + dwIter + 1 );
			break;
		}
	}
	if( !g_pInput ) printf("IInput not found\n");

	printf("Init done\n");

	m_ready = true;
	return true;
}
