#pragma once
#ifndef _HOOK_H_
#define _HOOK_H_

typedef void*( *CreateInterface_t )( const char*, int* );
typedef void( *RandomSeedFn )( unsigned int );
typedef float( *RandomFloatFn )( float, float );
typedef int( *RandomIntFn )( int, int );

extern IBaseClientDLL*			g_pBaseClientDll;
extern IClientEntityList*		g_pClientEntityList;
extern IPrediction*				g_pPrediction;
extern IGameMovement*			g_pGameMovement;
extern IVEngineClient*			g_pEngineClient;
extern ICvar*					g_pCvar;
extern IVModelInfo*				g_pModelInfo;
extern IEngineTrace*			g_pEngineTrace;
extern IPhysicsSurfaceProps*	g_pPhysicsSurfaceProps;
extern vgui::IPanel*			g_pPanel;
extern vgui::ISurface*			g_pSurface;
extern IVDebugOverlay*			g_pDebugOverlay;
extern IVRenderView*			g_pRender;
extern IVModelRender*			g_pModelRender;
extern IMaterialSystem*			g_pMaterialSystem;
extern IInput*					g_pInput;
extern CGlobalVarsBase*			g_pGlobals;
extern IGameEventManager2*		g_pGameEventManager;
extern IClientMode*				g_pClientMode;

extern vgui::HFont				g_Font;
extern vgui::HFont				g_MenuFontNormal;
extern float					g_flMenuFontNormalSize;
extern vgui::HFont				g_MenuFontBold;
extern float					g_flMenuFontBoldSize;
extern vgui::HFont				g_OldFont;
extern vgui::HFont				g_ESPFont;
extern vgui::HFont				g_WelcomeFont;

extern CVMTHook*				CreateMoveVMT;
extern CVMTHook*				PaintTraverseVMT;
extern CVMTHook*				GetUserCmdVMT;
extern CVMTHook*				PredictionVMT;
extern CVMTHook*				EngineClientVMT;
extern CVMTHook*				MaterialSystemVMT;
extern CVMTHook*				ModelRenderVMT;
extern CVMTHook*				GameEventManagerVMT;

extern RandomSeedFn				RandomSeed;
extern RandomFloatFn			RandomFloat;
extern RandomIntFn				RandomInt;

extern QAngle					g_qThirdPerson;
extern QAngle					g_qThirdPerson_last;
extern bool						g_bAirStuck;
extern bool						cmdnumticks;
extern int						g_ticks;
extern float					g_velocity;
extern bool						g_bRunCommand;
extern Vector					g_vecVelocity[ MULTIPLAYER_BACKUP ];
extern Vector					g_vecViewOffset[ MULTIPLAYER_BACKUP ];
extern QAngle					g_vecPunchAngle[ MULTIPLAYER_BACKUP ];
extern Vector					g_vecLocalOrigin[ MULTIPLAYER_BACKUP ];
extern float					g_flFallVelocity[ MULTIPLAYER_BACKUP ];
extern Vector					g_vecOrigin[ 64 ][ MULTIPLAYER_BACKUP ];
extern Vector					g_vecBaseVelocity[ MULTIPLAYER_BACKUP ];
extern float					g_flAccuracy[ MULTIPLAYER_BACKUP ];
extern float					g_flFireBulletsSpread;
extern Vector					EyePosition;
extern int						screen_x;
extern int						screen_y;

extern bool						g_bCL_Move;

extern int						g_Tick;
extern int						g_iGameTicks;
extern int						g_iBulletsFired[ 64 ];
extern float					g_flSimulationTime[ 64 ];
extern float					g_flAnimTime[ 64 ];
extern int						g_TickCount;

extern IMaterial* mat_vertex_in;
extern IMaterial* mat_vertex_out;
extern IMaterial* mat_unlit_in;
extern IMaterial* mat_unlit_out;
extern IMaterial* mat_outline;

extern void Hook( void );
extern void UnHook( void );
extern void SteamID( void );

#endif // _HOOK_H_