#include "Main.h"

Color visible, invisible, outlinecolour;
IMaterial* materials[ 2 ];

int __stdcall Hooked_DrawModelEx( ModelRenderInfo_t &pInfo ) 
{
	ModelRenderVMT->SetHookEnabled( false );

	bool players = false;
	bool weapons = false;
	bool hands = false;

	IMaterial* in = ( g_CVars.Visuals.Chams.Shadows ) ? mat_vertex_in : mat_unlit_in;
	IMaterial* out = ( g_CVars.Visuals.Chams.Shadows ) ? mat_vertex_out : mat_unlit_out;
	IMaterial* outline = mat_outline;

	std::string pszModelName = g_pModelInfo->GetModelName( ( model_t* )pInfo.pModel );

	BasePlayer* LocalPlayer = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( g_pEngineClient->GetLocalPlayer( ) );
	BasePlayer* pModelEntity = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( pInfo.entity_index );

	if( pModelEntity )
	{
		if( pszModelName.find( /*models/player*/XorStr<0x62,14,0xE7AF524E>("\x0F\x0C\x00\x00\x0A\x14\x47\x19\x06\x0A\x15\x08\x1C"+0xE7AF524E).s ) != std::string::npos )
		{
			if( g_CVars.Visuals.Chams.Active )
			{
				if( g_CVars.PlayerList.Friend[ pInfo.entity_index ] )
				{
					visible = Color::White( );
					invisible = Color::White( );
					outlinecolour = Color::White( );
				}
				else
				{
					bool IsTerrorist = ( pModelEntity->m_iTeamNum( ) == 2 );

					visible = ( IsTerrorist ) ? g_CVars.ColorSelector.Chams.TTVis : g_CVars.ColorSelector.Chams.CTVis;
					invisible = ( IsTerrorist ) ? g_CVars.ColorSelector.Chams.TTInvis : g_CVars.ColorSelector.Chams.CTInvis;
					outlinecolour = ( IsTerrorist ) ? g_CVars.ColorSelector.Chams.TTOutline : g_CVars.ColorSelector.Chams.CTOutline;
				}

				bool enemyonly = ( pModelEntity->m_iTeamNum( ) != LocalPlayer->m_iTeamNum( ) );

				if( g_CVars.Visuals.Chams.EnemyOnly )
				{
					if( enemyonly )
					{
						if( g_CVars.Visuals.Chams.Outline )
						{
							outline->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, true );
							//g_Stuff.ForceMaterial( 1, 1, 1, 1.0f, outline, true, true );
							g_Stuff.ForceMaterial( ( float )outlinecolour.r( ) / 255, ( float )outlinecolour.g( ) / 255, ( float )outlinecolour.b( ) / 255, 1.f, outline, true, true );
							g_pModelRender->DrawModelEx( pInfo );
							outline->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, false );
						}

						g_Stuff.ForceMaterial( ( float )invisible.r( ) / 255, ( float )invisible.g( ) / 255, ( float )invisible.b( ) / 255, 1.f, in, true, true );
						g_pModelRender->DrawModelEx( pInfo );
	
						g_Stuff.ForceMaterial( ( float )visible.r( ) / 255, ( float )visible.g( ) / 255, ( float )visible.b( ) / 255, 1.f, out, true, true );
						g_pModelRender->DrawModelEx( pInfo );
					}
					else
					{
						IMaterial* mat; 
						g_pModelInfo->GetModelMaterials( ( model_t* )pInfo.pModel, 1, &mat );
						g_Stuff.ForceMaterial( 1.f, 1.f, 1.f, 1.f, mat, true, true );
						g_pModelRender->DrawModelEx( pInfo );
					}
				}
				else
				{
					if( g_CVars.Visuals.Chams.Outline )
					{
						outline->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, true );
						//g_Stuff.ForceMaterial( 1, 1, 1, 1.0f, outline, true, true );
						g_Stuff.ForceMaterial( ( float )outlinecolour.r( ) / 255, ( float )outlinecolour.g( ) / 255, ( float )outlinecolour.b( ) / 255, 1.f, outline, true, true );
						g_pModelRender->DrawModelEx( pInfo );
						outline->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, false );
					}

					g_Stuff.ForceMaterial( ( float )invisible.r( ) / 255, ( float )invisible.g( ) / 255, ( float )invisible.b( ) / 255, 1.f, in, true, true );
					g_pModelRender->DrawModelEx( pInfo );
	
					g_Stuff.ForceMaterial( ( float )visible.r( ) / 255, ( float )visible.g( ) / 255, ( float )visible.b( ) / 255, 1.f, out, true, true );
					g_pModelRender->DrawModelEx( pInfo );
				}
				players = true;
			}	
			else if( g_CVars.Visuals.ASUS < 1.f )
			{
				IMaterial* mat; 
				g_pModelInfo->GetModelMaterials( ( model_t* )pInfo.pModel, 1, &mat );
				g_Stuff.ForceMaterial( 1.f, 1.f, 1.f, 1.f, mat, true, true );
				g_pModelRender->DrawModelEx( pInfo );
				players = true;
			}
			else g_pModelRender->DrawModelEx( pInfo );
		}
	}

	if( pszModelName.find( /*models/weapons/w_*/XorStr<0xF0,18,0x6594C4FA>("\x9D\x9E\x96\x96\x98\x86\xD9\x80\x9D\x98\x8A\x94\x92\x8E\xD1\x88\x5F"+0x6594C4FA).s ) != std::string::npos )
	{
		if( g_CVars.Visuals.Chams.Weapons )
		{
			visible = g_CVars.ColorSelector.Chams.WpnVis;
			invisible = g_CVars.ColorSelector.Chams.WpnInvis;
			outlinecolour = g_CVars.ColorSelector.Chams.WpnOutline;

			if( g_CVars.Visuals.Chams.Outline )
			{
				outline->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, true );
				g_Stuff.ForceMaterial( ( float )outlinecolour.r( ) / 255, ( float )outlinecolour.g( ) / 255, ( float )outlinecolour.b( ) / 255, 1.f, outline, true, true );
				g_pModelRender->DrawModelEx( pInfo );
				outline->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, false );
			}

			g_Stuff.ForceMaterial( ( float )invisible.r( ) / 255, ( float )invisible.g( ) / 255, ( float )invisible.b( ) / 255, 1.f, in, true, true );
			g_pModelRender->DrawModelEx( pInfo );
			g_Stuff.ForceMaterial( ( float )visible.r( ) / 255, ( float )visible.g( ) / 255, ( float )visible.b( ), 1.f, out, true, true );
			weapons = true;
		}
		else if( g_CVars.Visuals.ASUS < 1.f )
		{
			IMaterial* mat; 
			g_pModelInfo->GetModelMaterials( ( model_t* )pInfo.pModel, 1, &mat );
			g_Stuff.ForceMaterial( 1.f, 1.f, 1.f, 1.f, mat, true, true );
			g_pModelRender->DrawModelEx( pInfo );
			weapons = true;
		}
		else g_pModelRender->DrawModelEx( pInfo );
	}

	if( g_CVars.Visuals.Chams.HandsOutline )
	{
		if( pszModelName.find( /*models/weapons/v_*/XorStr<0x07,18,0x231BE69E>("\x6A\x67\x6D\x6F\x67\x7F\x22\x79\x6A\x71\x61\x7D\x7D\x67\x3A\x60\x48"+0x231BE69E).s ) != std::string::npos )
		{
			invisible = ( LocalPlayer->m_iTeamNum( ) == 2 ) ? g_CVars.ColorSelector.Chams.TTInvis : g_CVars.ColorSelector.Chams.CTInvis;

			if( g_CVars.Visuals.Chams.Outline )
			{
				outline->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, true );
				g_Stuff.ForceMaterial( ( float )invisible.r( ) / 255, ( float )invisible.g( ) / 255, ( float )invisible.b( ) / 255, 1.f, outline, true, true );
				g_pModelRender->DrawModelEx( pInfo );
				outline->SetMaterialVarFlag( MATERIAL_VAR_WIREFRAME, false );
			}

			g_Stuff.ForceMaterial( 1.0f, 1.f, 1.f, 1.f, 0, true, true );
			g_pModelRender->DrawModelEx( pInfo );
			hands = true;
		}
	}

	int bRet = g_pModelRender->DrawModelEx( pInfo );

	if( players || weapons || hands ) g_Stuff.ForceMaterial( 1.f, 1.f, 1.f, 1.f, 0, true, true );

	ModelRenderVMT->SetHookEnabled( true );
	return bRet;
}