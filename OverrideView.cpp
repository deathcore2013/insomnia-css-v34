#include "Main.h"

typedef void( __thiscall* OverrideView_t )( void*, CViewSetup* );
void __fastcall Hooked_OverrideView( void* ecx, void* edx, CViewSetup* setup )
{
	BasePlayer* LocalPlayer = ( BasePlayer* )g_pClientEntityList->GetClientEntity( g_pEngineClient->GetLocalPlayer( ) );
	if( LocalPlayer )
	{
		printconsole( "fov: %f, viewmodel: %f", setup->fov, setup->fovViewmodel );
		setup->fov = 120.f;
		setup->fovViewmodel = 120.f;
		printconsole( "fov: %f, viewmodel: %f", setup->fov, setup->fovViewmodel );
	}

	g_pClientMode->OverrideView( setup );
	//g_pBaseClientDll->RenderView( view, nFlags, drawViewmodel );
}