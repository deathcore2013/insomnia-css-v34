#include "Main.h"

static DWORD ConvertToDWORD( float const number )
{
	return *reinterpret_cast< DWORD const* >( &number );
}
static float ConvertToFloat( DWORD const number )
{
	return *reinterpret_cast< float const* >( &number );
}

enum
{ 
	INTERFACE_CLIENT, 
	INTERFACE_ENGINE, 
	INTERFACE_PHYSICS, 
	INTERFACE_FILESYSTEM, 
	INTERFACE_STUDIO, 
	INTERFACE_MATERIAL,
	INTERFACE_VGUI,
	INTERFACE_VGUI2,
};

typedef struct
{
	int idx;
	std::string name;
}interface_t;

interface_t InterfacesArray[ ] = 
{
	{ INTERFACE_CLIENT, /*client*/XorStr<0x83,7,0x1826BC91>("\xE0\xE8\xEC\xE3\xE9\xFC"+0x1826BC91).s },
	{ INTERFACE_ENGINE, /*engine*/XorStr<0x32,7,0x4B392EEF>("\x57\x5D\x53\x5C\x58\x52"+0x4B392EEF).s },
	{ INTERFACE_PHYSICS, /*vphysics*/XorStr<0xF3,9,0xED4FD4DB>("\x85\x84\x9D\x8F\x84\x91\x9A\x89"+0xED4FD4DB).s },
	{ INTERFACE_FILESYSTEM, /*FileSystem_Steam*/XorStr<0x0B,17,0xB75F259B>("\x4D\x65\x61\x6B\x5C\x69\x62\x66\x76\x79\x4A\x45\x63\x7D\x78\x77"+0xB75F259B).s },
	{ INTERFACE_STUDIO, /*StudioRender*/XorStr<0x9D,13,0xE0D58ED8>("\xCE\xEA\xEA\xC4\xC8\xCD\xF1\xC1\xCB\xC2\xC2\xDA"+0xE0D58ED8).s },
	{ INTERFACE_MATERIAL, /*MaterialSystem*/XorStr<0xFA,15,0x8F32F14C>("\xB7\x9A\x88\x98\x8C\x96\x61\x6D\x51\x7A\x77\x71\x63\x6A"+0x8F32F14C).s },
	{ INTERFACE_VGUI, /*vguimatsurface*/XorStr<0xD4,15,0x3841273C>("\xA2\xB2\xA3\xBE\xB5\xB8\xAE\xA8\xA9\xAF\xB8\xBE\x83\x84"+0x3841273C).s },
	{ INTERFACE_VGUI2, /*vgui2*/XorStr<0xDB,6,0xBA268CE3>("\xAD\xBB\xA8\xB7\xED"+0xBA268CE3).s }
};

CreateInterface_t Interfaces[ 8 ];

void* FindInterface( int interface_s, char* interfaceversion )
{
	char buffer[ 0xFF ];
	int index = 0xFF;
	do
	{
		if( index <= 10 ) sprintf_s( buffer, /*%s00%i*/XorStr<0x2F,7,0xF36659C9>("\x0A\x43\x01\x02\x16\x5D"+0xF36659C9).s, interfaceversion, index );
		if( index >= 10 ) sprintf_s( buffer, /*%s0%i*/XorStr<0x37,6,0x377C3525>("\x12\x4B\x09\x1F\x52"+0x377C3525).s, interfaceversion, index );
		if( index >= 100 ) sprintf_s( buffer, /*%s%i*/XorStr<0x9D,5,0x8C23DD66>("\xB8\xED\xBA\xC9"+0x8C23DD66).s, interfaceversion, index );

		if( Interfaces[ interface_s ]( buffer, 0 ) ) break;
		index--;

	} while ( index >= 0 );

	//printf( "%s", buffer );
	void* ret = Interfaces[ interface_s ]( buffer, 0 );
	return ret;
}

// auto interface version
#define GrabInterface( type, interface_s, version ) ( type )FindInterface( interface_s, version )

// manual interface version
#define GrabInterface2( type, interface_s, version ) ( type )Interfaces[ interface_s ]( version, 0 )

IBaseClientDLL*			g_pBaseClientDll;
IClientEntityList*		g_pClientEntityList;
IPrediction*			g_pPrediction;
IGameMovement*			g_pGameMovement;
IVEngineClient*			g_pEngineClient;
ICvar*					g_pCvar;
IVModelInfo*			g_pModelInfo;
IEngineTrace*			g_pEngineTrace;
IPhysicsSurfaceProps*	g_pPhysicsSurfaceProps;
vgui::IPanel*			g_pPanel;
vgui::ISurface*			g_pSurface;
IVDebugOverlay*			g_pDebugOverlay;
IVRenderView*			g_pRender;
IVModelRender*			g_pModelRender;
IMaterialSystem*		g_pMaterialSystem;
IInput*					g_pInput;
CGlobalVarsBase*		g_pGlobals;
IGameEventManager2*		g_pGameEventManager;
IClientMode*			g_pClientMode;

vgui::HFont				g_Font;
vgui::HFont				g_MenuFontNormal;
float					g_flMenuFontNormalSize;
vgui::HFont				g_MenuFontBold;
float					g_flMenuFontBoldSize;
vgui::HFont				g_OldFont;
vgui::HFont				g_ESPFont;
vgui::HFont				g_WelcomeFont;

CVMTHook*				CreateMoveVMT;
CVMTHook*				GetUserCmdVMT;
CVMTHook*				PredictionVMT;
CVMTHook*				DrawPortalsVMT;
CVMTHook*				ModelRenderVMT;
CVMTHook*				EngineClientVMT;
CVMTHook*				PaintTraverseVMT;
CVMTHook*				MaterialSystemVMT;
CVMTHook*				GameEventManagerVMT;

RandomSeedFn			RandomSeed;
RandomFloatFn			RandomFloat;
RandomIntFn				RandomInt;

QAngle					g_qThirdPerson;
QAngle					g_qThirdPerson_last;
bool					g_bAirStuck;
bool					cmdnumticks;
int						g_ticks;
float					g_velocity;
bool					g_bRunCommand;
Vector					g_vecVelocity[ MULTIPLAYER_BACKUP ];
Vector					g_vecViewOffset[ MULTIPLAYER_BACKUP ];
QAngle					g_vecPunchAngle[ MULTIPLAYER_BACKUP ];
Vector					g_vecLocalOrigin[ MULTIPLAYER_BACKUP ];
float					g_flFallVelocity[ MULTIPLAYER_BACKUP ];
Vector					g_vecOrigin[ 64 ][ MULTIPLAYER_BACKUP ];
Vector					g_vecBaseVelocity[ MULTIPLAYER_BACKUP ];
float					g_flAccuracy[ MULTIPLAYER_BACKUP ];
float					g_flFireBulletsSpread;
Vector					EyePosition;
int						screen_x;
int						screen_y;
bool					g_bCL_Move;

int						g_Tick;
int						g_iGameTicks;
int						g_iBulletsFired[ 64 ];
float					g_flSimulationTime[ 64 ];
float					g_flAnimTime[ 64 ];
int						g_TickCount;

void InitInterfaces( int num, const char* module )
{
	Interfaces[ num ] = GetFuncModule< CreateInterface_t >( ( char* )module, /*CreateInterface*/XorStr<0xD2,16,0x0907B19C>("\x91\xA1\xB1\xB4\xA2\xB2\x91\xB7\xAE\xBE\xAE\xBB\xBF\xBC\x85"+0x0907B19C).s );
}

void FlashProxy( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	float flOut;
	if( g_CVars.Visuals.NoFlash ) flOut = 0.f;
	else flOut = pData->m_Value.m_Float;
		
	*( float* )pOut = flOut;
}

void SmokeProxy( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	float flOut;
	if( g_CVars.Visuals.NoSmoke ) flOut = 0.f;
	else flOut = pData->m_Value.m_Float;
		
	*( float* )pOut = flOut;
}

#define clamp(val, min, max) (((val) > (max)) ? (max) : (((val) < (min)) ? (min) : (val)))

void PlayerList_EyeAngles_Pitch( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	if( ( ( BaseEntity* )( pStruct ) )->GetClientNetworkable( )->entindex( ) == g_pEngineClient->GetLocalPlayer( ) )
	{
		*( float* )pOut = pData->m_Value.m_Float;
	}
	else
	{
		float flTmp = pData->m_Value.m_Float;
		float flPitch = pData->m_Value.m_Float;

		g_CVars.PlayerList.Index = ( ( BaseEntity* )( pStruct ) )->GetClientNetworkable( )->entindex( );

		if( g_CVars.PlayerList.Pitch[ g_CVars.PlayerList.Index ] == 0 ) // auto
		{
			float pfPitch = flPitch;
			if( pfPitch < 0 ) pfPitch += 360.f;

			if( ( pfPitch > 180.f ) && ( pfPitch < 290.0f ) ) flPitch = -89.f;
			else if( ( pfPitch >= 60.f ) && ( pfPitch <= 180.f ) ) flPitch = 89.f;
		}
		else if( g_CVars.PlayerList.Pitch[ g_CVars.PlayerList.Index ] == 1 ) // down
		{
			flPitch = 89.f;
		}
		else if( g_CVars.PlayerList.Pitch[ g_CVars.PlayerList.Index ] == 2 ) // up
		{
			flPitch = -89.f;
		}
		else if( g_CVars.PlayerList.Pitch[ g_CVars.PlayerList.Index ] == 3 ) // off
		{
			flPitch = pData->m_Value.m_Float;
		}

		g_CVars.PlayerList.ViewAngles[ g_CVars.PlayerList.Index ].x = flPitch;
		*( float* )pOut = flPitch;
	}
}

void PlayerList_EyeAngles_Yaw( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	if( ( ( BaseEntity* )( pStruct ) )->GetClientNetworkable( )->entindex( ) == g_pEngineClient->GetLocalPlayer( ) )
	{
		*( float* )pOut = pData->m_Value.m_Float;
	}
	else
	{
		static float Temp[ 64 ];
		static float flOldYaw[ 64 ];
		float flYaw = pData->m_Value.m_Float, TempYaw = pData->m_Value.m_Float;

		g_CVars.PlayerList.Index = ( ( BaseEntity* )( pStruct ) )->GetClientNetworkable( )->entindex( );

		float flPitch = *( float* )( ( DWORD )pOut - 4 );
		bool bPitch = ( ( flPitch == 89.f ) || ( flPitch == -89.f ) );

		if( !( g_CVars.Aimbot.Resolver.Active && g_CVars.Aimbot.Resolver.Mode == 0 ) )
		{
			switch( g_CVars.PlayerList.Yaw[ g_CVars.PlayerList.Index ] )
			{
				case 0:
				{
					static bool bTemp[ 64 ];
					bool twitch = bTemp[ g_CVars.PlayerList.Index ];
					bTemp[ g_CVars.PlayerList.Index ] = ( flYaw >= 180 && flYaw <= 360 );

					if( twitch && ( flYaw >= 0 && flYaw <= 180 ) ) flYaw += 359;
					break;
				}
				case 1: flYaw = TempYaw; break;
				case 2: flYaw -= 270.f; break;
				case 3: flYaw -= 90.f; break;
				case 4: flYaw -= 180.f; break;
				case 5: flYaw = TempYaw; break;
			}
		}

		g_CVars.PlayerList.ViewAngles[ g_CVars.PlayerList.Index ].y = flYaw;
		*( float* )pOut = flYaw;
	}
}

void BasePlayer_ViewOffsetZ( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	float ViewOffsetZ = pData->m_Value.m_Float;
	DWORD DViewOffsetZ = ConvertToDWORD( ViewOffsetZ );

	if( DViewOffsetZ == 0x42802008 ) DViewOffsetZ = 0x42800000;
	else if( DViewOffsetZ == 0x423C2F0C ) DViewOffsetZ = 0x423C0000;

	ViewOffsetZ = ConvertToFloat( DViewOffsetZ );

	*( float* )pOut = ViewOffsetZ;
}

void BaseEntity_SimulationTime( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	int t;
	int tickbase;
	int addt;

	addt = pData->m_Value.m_Int;

	tickbase = 100 * ( int )( g_pGlobals->tickcount / 100 );
	t = tickbase;
	t += addt;

	while( t < g_pGlobals->tickcount - 127 ) t += 256;
	while( t > g_pGlobals->tickcount + 127 ) t -= 256;
	
	BasePlayer* Entity = ( BasePlayer* )pStruct;
	Entity->m_flSimulationTime( ) = ( t * g_pGlobals->interval_per_tick );

	*( float* )pOut = Entity->m_flSimulationTime( );
}

void BasePlayer_BaseVelocity( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	for( int i = 0; i <= 2; ++i )
	{
		float axis = pData->m_Value.m_Vector[ i ];
		DWORD Daxis = ConvertToDWORD( axis );
		if( Daxis == 0xBA7A0010 ) axis = 0.f;
		*( float* )pOut = axis;
	}
}

void BasePlayer_FallVelocity( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	float FallVelocity = pData->m_Value.m_Float;
	DWORD DFallVelocity = ConvertToDWORD( FallVelocity );
	if( DFallVelocity == 0x3D000040 ) FallVelocity = 0.f;
	*( float* )pOut = FallVelocity;
}

void BasePlayer_TickBase( const CRecvProxyData *pData, void *pStruct, void *pOut )
{
	BasePlayer* pEntity = ( BasePlayer* )pStruct;
	if( pEntity->entindex( ) == g_pEngineClient->GetLocalPlayer( ) )
	{
		static int stuck = 0;
		int update = pData->m_Value.m_Int;

		*( int* ) pOut = ( update == stuck ) ? pEntity->m_nTickBase( ) + 1 : update;
		stuck = update;
	}
	else *( int* ) pOut = pData->m_Value.m_Int;
}

char RandomChar( void )
{
	char result;

	if( rand( ) % 3 == 0 ) result = rand( ) % 10 + 48;
	else result = rand( ) % 26 + 65;

	return result;
}

/*
void SteamID( void )
{
	while( 1 )
	{
		Sleep( 0x64 );

		DWORD_PTR dwSteam = ( DWORD ) GetModuleBase( "Steam.dll" );
		if( !dwSteam ) continue;
		srand( GetTickCount( ) );
		for( int i = 0; i < 4; i++ )
		{
			*( BYTE* )( dwSteam + 0x12C5C + i ) = RandomChar( );
		}
	}
}
*/

IMaterial* mat_vertex_in;
IMaterial* mat_vertex_out;
IMaterial* mat_unlit_in;
IMaterial* mat_unlit_out;
IMaterial* mat_outline;

void Hook( void )
{

	while( GetModuleHandleA( /*engine*/XorStr<0xFF,7,0x5467D774>("\x9A\x6E\x66\x6B\x6D\x61"+0x5467D774).s ) == NULL || GetModuleHandleA( /*client*/XorStr<0x9A,7,0x861DD552>("\xF9\xF7\xF5\xF8\xF0\xEB"+0x861DD552).s ) == NULL ) Sleep( 100 );

	for( int i = 0; i <= 7; i++ ) InitInterfaces( InterfacesArray[ i ].idx, InterfacesArray[ i ].name.c_str( ) );
	printconsole( /* Interfaces initialized...*/XorStr<0x0C,27,0x060618EC>("\x2C\x44\x60\x7B\x75\x63\x74\x72\x77\x70\x65\x37\x71\x77\x73\x6F\x75\x7C\x72\x76\x5A\x44\x46\x0D\x0A\x0B"+0x060618EC).s );

	g_pBaseClientDll = GrabInterface( IBaseClientDLL*, INTERFACE_CLIENT, "VClient" );
	g_pClientEntityList = GrabInterface( IClientEntityList*, INTERFACE_CLIENT, "VClientEntityList" );
	g_pPrediction = GrabInterface( IPrediction*, INTERFACE_CLIENT, "VClientPrediction" );
	g_pGameMovement = GrabInterface( IGameMovement*, INTERFACE_CLIENT, "GameMovement" );
	g_pEngineClient = GrabInterface( IVEngineClient*, INTERFACE_ENGINE, "VEngineClient" );
	g_pCvar = GrabInterface( ICvar*, INTERFACE_ENGINE, "VEngineCvar" );
	g_pModelInfo = GrabInterface( IVModelInfo*, INTERFACE_ENGINE, "VModelInfoClient" );
	g_pEngineTrace = GrabInterface( IEngineTrace*, INTERFACE_ENGINE, "EngineTraceClient" );
	g_pPhysicsSurfaceProps = GrabInterface( IPhysicsSurfaceProps*, INTERFACE_PHYSICS, "VPhysicsSurfaceProps" );
	g_pPanel = GrabInterface( vgui::IPanel*, INTERFACE_VGUI2, "VGUI_Panel" );
	g_pSurface = GrabInterface( vgui::ISurface*, INTERFACE_VGUI, "VGUI_Surface" );
	g_pRender = GrabInterface( IVRenderView*, INTERFACE_ENGINE, "VEngineRenderView" );
	g_pModelRender = GrabInterface( IVModelRender*, INTERFACE_ENGINE, "VEngineModel" );
	g_pDebugOverlay = GrabInterface( IVDebugOverlay*, INTERFACE_ENGINE, "VDebugOverlay" );
	g_pMaterialSystem = GrabInterface( IMaterialSystem*, INTERFACE_MATERIAL, "VMaterialSystem" );	
	g_pGameEventManager = GrabInterface( IGameEventManager2*, INTERFACE_ENGINE, "GAMEEVENTSMANAGER" );

	g_pInput = **( IInput*** )( ( *( uintptr_t** ) g_pBaseClientDll )[ 11 ] + 0x2 );
	g_pGlobals = **( CGlobalVarsBase*** )( ( *( uintptr_t** ) g_pBaseClientDll )[ 0 ] + 0x2F );

	HMODULE vstdlib = GetModuleHandleA( /*vstdlib.dll*/XorStr<0x8B,12,0x922FC0BB>("\xFD\xFF\xF9\xEA\xE3\xF9\xF3\xBC\xF7\xF8\xF9"+0x922FC0BB).s );
    RandomSeed = ( RandomSeedFn )GetProcAddress( vstdlib, /*RandomSeed*/XorStr<0xA8,11,0x514D0126>("\xFA\xC8\xC4\xCF\xC3\xC0\xFD\xCA\xD5\xD5"+0x514D0126).s );
    RandomFloat = ( RandomFloatFn )GetProcAddress( vstdlib, /*RandomFloat*/XorStr<0xD5,12,0x17E3FE6D>("\x87\xB7\xB9\xBC\xB6\xB7\x9D\xB0\xB2\xBF\xAB"+0x17E3FE6D).s );
    RandomInt = ( RandomIntFn )GetProcAddress( vstdlib, /*RandomInt*/XorStr<0x82,10,0x05AB732A>("\xD0\xE2\xEA\xE1\xE9\xEA\xC1\xE7\xFE"+0x05AB732A).s );

	PDWORD* pdwPanelVMT = ( PDWORD* )g_pPanel; 
	PDWORD* pdwInputVMT = ( PDWORD* )g_pInput; 
	PDWORD* pdwEngineVMT = ( PDWORD* )g_pEngineClient;
	PDWORD* pdwClientVMT = ( PDWORD* )g_pBaseClientDll; 
	PDWORD* pdwPredictionVMT = ( PDWORD* )g_pPrediction;
	PDWORD* pdwModelRenderVMT = ( PDWORD* )g_pModelRender;
	PDWORD* pdwMaterialSystemVMT = ( PDWORD* )g_pMaterialSystem;
	PDWORD* pdwGameEventManagerVMT = ( PDWORD* )g_pGameEventManager;

	EngineClientVMT = new CVMTHook( pdwEngineVMT );
	//EngineClientVMT->HookFunction( 15, Hooked_GetLastTimeStamp );

	CreateMoveVMT = new CVMTHook( pdwClientVMT );
	CreateMoveVMT->HookFunction( 18, Hooked_CreateMove );
	//CreateMoveVMT->HookFunction( 17, Hooked_IN_KeyEvent );
	CreateMoveVMT->HookFunction( 32, Hooked_FrameStageNotify );	
	
	GetUserCmdVMT = new CVMTHook( pdwInputVMT );
	GetUserCmdVMT->HookFunction( 8, Hooked_GetUserCmd );
	
	PredictionVMT = new CVMTHook( pdwPredictionVMT );
	//PredictionVMT->HookFunction( 8, Hooked_InPrediction );
	PredictionVMT->HookFunction( 16, Hooked_SetViewAngles );
	PredictionVMT->HookFunction( 19, Hooked_RunCommand );
	PredictionVMT->HookFunction( 23, Hooked_Update );

	CL_Move( );
	FX_FireBullets( );
	CL_RunPrediction( );
	//ClientInterpolation( );

	ModelRenderVMT = new CVMTHook( pdwModelRenderVMT );
	ModelRenderVMT->HookFunction( 19, Hooked_DrawModelEx );

	MaterialSystemVMT = new CVMTHook( pdwMaterialSystemVMT );
	MaterialSystemVMT->HookFunction( 27, Hooked_FindMaterial );

	g_pEngineClient->GetScreenSize( screen_x, screen_y );

	PaintTraverseVMT = new CVMTHook( pdwPanelVMT );
	PaintTraverseVMT->HookFunction( 40, Hooked_PaintTraverse );

	g_CVars.Init( );

	g_pNetvarManager = new HackInterfaces::NetvarManager( );
	g_pNetvarManager->HookRecvProp( /*DT_CSPlayer*/XorStr<0xF1,12,0xB60E482B>("\xB5\xA6\xAC\xB7\xA6\xA6\x9B\x99\x80\x9F\x89"+0xB60E482B).s, /*m_angEyeAngles[0]*/XorStr<0x8A,18,0x3656D77C>("\xE7\xD4\xED\xE3\xE9\xCA\xE9\xF4\xD3\xFD\xF3\xF9\xF3\xE4\xC3\xA9\xC7"+0x3656D77C).s, PlayerList_EyeAngles_Pitch );
	g_pNetvarManager->HookRecvProp( /*DT_CSPlayer*/XorStr<0xCE,12,0x913CD0AA>("\x8A\x9B\x8F\x92\x81\x83\xB8\xB4\xAF\xB2\xAA"+0x913CD0AA).s, /*m_angEyeAngles[1]*/XorStr<0xE8,18,0x2FF7726E>("\x85\xB6\x8B\x85\x8B\xA8\x97\x8A\xB1\x9F\x95\x9F\x91\x86\xAD\xC6\xA5"+0x2FF7726E).s, PlayerList_EyeAngles_Yaw );
	g_pNetvarManager->HookRecvProp( /*DT_BasePlayer*/XorStr<0x69,14,0xD964BC30>("\x2D\x3E\x34\x2E\x0C\x1D\x0A\x20\x1D\x13\x0A\x11\x07"+0xD964BC30).s, /*m_vecViewOffset[2]*/XorStr<0xF0,19,0x3B8A201F>("\x9D\xAE\x84\x96\x97\xA3\x9F\x92\x8F\xB6\x9C\x9D\x8F\x98\x8A\xA4\x32\x5C"+0x3B8A201F).s, BasePlayer_ViewOffsetZ );
	g_pNetvarManager->HookRecvProp( /*DT_BasePlayer*/XorStr<0x6B,14,0x70A952E3>("\x2F\x38\x32\x2C\x0E\x03\x14\x22\x1F\x15\x0C\x13\x05"+0x70A952E3).s, /*m_vecBaseVelocity*/XorStr<0xF0,18,0x2EA12133>("\x9D\xAE\x84\x96\x97\xB7\x97\x84\x9D\xAF\x9F\x97\x93\x9E\x97\x8B\x79"+0x2EA12133).s, BasePlayer_BaseVelocity );
	//g_pNetvarManager->HookRecvProp( /*DT_BaseEntity*/XorStr<0x7E,14,0x34E50703>("\x3A\x2B\xDF\xC3\xE3\xF0\xE1\xC0\xE8\xF3\xE1\xFD\xF3"+0x34E50703).s, /*m_flSimulationTime*/XorStr<0x1D,19,0xCD57C537>("\x70\x41\x79\x4C\x72\x4B\x4E\x51\x49\x47\x53\x41\x46\x44\x7F\x45\x40\x4B"+0xCD57C537).s, BaseEntity_SimulationTime );
	g_pNetvarManager->HookRecvProp( /*DT_CSPlayer*/XorStr<0x96,12,0x69D79DA0>("\xD2\xC3\xC7\xDA\xC9\xCB\xF0\xFC\xE7\xFA\xD2"+0x69D79DA0).s, /*m_flFallVelocity*/XorStr<0x72,17,0x97E4AF69>("\x1F\x2C\x12\x19\x30\x16\x14\x15\x2C\x1E\x10\x12\x1D\x16\xF4\xF8"+0x97E4AF69).s, BasePlayer_FallVelocity );
	//g_pNetvarManager->HookRecvProp( /*DT_CSPlayer*/XorStr<0xBE,12,0xF8678CD8>("\xFA\xEB\x9F\x82\x91\x93\xA8\xA4\xBF\xA2\xBA"+0xF8678CD8).s, /*m_nTickBase*/XorStr<0x50,12,0x8EA8F7FC>("\x3D\x0E\x3C\x07\x3D\x36\x3D\x15\x39\x2A\x3F"+0x8EA8F7FC).s, BasePlayer_TickBase );
	g_pNetvarManager->HookRecvProp( /*DT_CSPlayer*/XorStr<0x17,12,0x4063FD44>("\x53\x4C\x46\x59\x48\x4C\x71\x7F\x66\x45\x53"+0x4063FD44).s, /*m_flFlashDuration*/XorStr<0x3C,18,0x4EA121B8>("\x51\x62\x58\x53\x06\x2D\x23\x30\x2C\x01\x33\x35\x29\x3D\x23\x24\x22"+0x4EA121B8).s, FlashProxy );
	g_pNetvarManager->HookRecvProp( /*DT_ParticleSmokeGrenade*/XorStr<0x96,24,0x1551A9A9>("\xD2\xC3\xC7\xC9\xFB\xE9\xE8\xF4\xFD\xF3\xC5\xF2\xCF\xCC\xCF\xC0\xE1\xD5\xCD\xC7\xCB\xCF\xC9"+0x1551A9A9).s, /*m_flSpawnTime*/XorStr<0x67,14,0x5D98EEC8>("\x0A\x37\x0F\x06\x38\x1C\x0C\x19\x01\x24\x18\x1F\x16"+0x5D98EEC8).s, SmokeProxy );

	printconsole( /* Hooks done...\n*/XorStr<0xEE,16,0x806644F3>("\xCE\xA7\x9F\x9E\x99\x80\xD4\x91\x99\x99\x9D\xD7\xD4\xD5\xF6"+0x806644F3).s );

	mat_vertex_in = g_Stuff.CreateMaterial( true, true, false );
	mat_vertex_out = g_Stuff.CreateMaterial( true, false, false );
	mat_unlit_in = g_Stuff.CreateMaterial( false, true, false );
	mat_unlit_out = g_Stuff.CreateMaterial( false, false, false );
	mat_outline = g_Stuff.CreateMaterial( false, true, false );
}

void UnHook( void )
{
	CreateMoveVMT->SetHookEnabled( false );
	PaintTraverseVMT->SetHookEnabled( false );
	GetUserCmdVMT->SetHookEnabled( false );
	PredictionVMT->SetHookEnabled( false );
}