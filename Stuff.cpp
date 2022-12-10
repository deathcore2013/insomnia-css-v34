#include "Main.h"
#include "SDK/checksum_md5.cpp"

CVars g_CVars;
Stuff g_Stuff;

void CVars::Init( )
{
	Menu.w = 420;
	Menu.h = 198;

	Accuracy.NoSpreadMode = 1;

	Menu.x = screen_x / 2 - ( Menu.h / 2 );
	Menu.y = screen_y / 2 - ( Menu.w / 2 );

	Radar.x = 20;
	Radar.y = 20;
	Radar.w = 249;
	Radar.h = 249;

	Visuals.ASUS = 1.f;

	ColorSelector.ESP.TT = Color::Red( );
	ColorSelector.ESP.CT = Color::LightBlue( );
	ColorSelector.ESP.Wpn = Color::White( );

	ColorSelector.Chams.CTInvis = Color( 100, 150, 255, 255 );
	ColorSelector.Chams.CTVis = Color( 65, 65, 255, 255 );
	ColorSelector.Chams.CTOutline = Color( 100, 150, 255, 255 );

	ColorSelector.Chams.TTInvis = Color( 255, 200, 200, 255 );
	ColorSelector.Chams.TTVis = Color::Red( );
	ColorSelector.Chams.TTOutline = Color( 255, 200, 200, 255 );

	ColorSelector.Chams.WpnInvis = Color::White( );
	ColorSelector.Chams.WpnVis = Color::White( );
	ColorSelector.Chams.WpnOutline = Color::Black( );

	g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 0 ] = g_CVars.ColorSelector.ESP.CT.r( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 1 ] = g_CVars.ColorSelector.ESP.CT.g( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 0 ][ 0 ][ 2 ] = g_CVars.ColorSelector.ESP.CT.b( );

	g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 0 ] = g_CVars.ColorSelector.ESP.TT.r( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 1 ] = g_CVars.ColorSelector.ESP.TT.g( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 1 ][ 0 ][ 2 ] = g_CVars.ColorSelector.ESP.TT.b( );

	g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 0 ] = g_CVars.ColorSelector.ESP.Wpn.r( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 1 ] = g_CVars.ColorSelector.ESP.Wpn.g( );
	g_CVars.ColorSelector.CurrentColor[ 0 ][ 2 ][ 0 ][ 2 ] = g_CVars.ColorSelector.ESP.Wpn.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 0 ] = g_CVars.ColorSelector.Chams.CTVis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 1 ] = g_CVars.ColorSelector.Chams.CTVis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 0 ][ 2 ] = g_CVars.ColorSelector.Chams.CTVis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 0 ] = g_CVars.ColorSelector.Chams.CTInvis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 1 ] = g_CVars.ColorSelector.Chams.CTInvis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 1 ][ 2 ] = g_CVars.ColorSelector.Chams.CTInvis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 0 ] = g_CVars.ColorSelector.Chams.CTOutline.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 1 ] = g_CVars.ColorSelector.Chams.CTOutline.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 0 ][ 2 ][ 2 ] = g_CVars.ColorSelector.Chams.CTOutline.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 0 ] = g_CVars.ColorSelector.Chams.TTVis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 1 ] = g_CVars.ColorSelector.Chams.TTVis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 0 ][ 2 ] = g_CVars.ColorSelector.Chams.TTVis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 0 ] = g_CVars.ColorSelector.Chams.TTInvis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 1 ] = g_CVars.ColorSelector.Chams.TTInvis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 1 ][ 2 ] = g_CVars.ColorSelector.Chams.TTInvis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 0 ] = g_CVars.ColorSelector.Chams.TTOutline.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 1 ] = g_CVars.ColorSelector.Chams.TTOutline.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 1 ][ 2 ][ 2 ] = g_CVars.ColorSelector.Chams.TTOutline.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 0 ] = g_CVars.ColorSelector.Chams.WpnVis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 1 ] = g_CVars.ColorSelector.Chams.WpnVis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 0 ][ 2 ] = g_CVars.ColorSelector.Chams.WpnVis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 0 ] = g_CVars.ColorSelector.Chams.WpnInvis.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 1 ] = g_CVars.ColorSelector.Chams.WpnInvis.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 1 ][ 2 ] = g_CVars.ColorSelector.Chams.WpnInvis.b( );

	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 0 ] = g_CVars.ColorSelector.Chams.WpnOutline.r( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 1 ] = g_CVars.ColorSelector.Chams.WpnOutline.g( );
	g_CVars.ColorSelector.CurrentColor[ 1 ][ 2 ][ 2 ][ 2 ] = g_CVars.ColorSelector.Chams.WpnOutline.b( );

	Colors.Scheme = 1;
}

//===============================================================================================

void Stuff::Mouse::Draw( Color mouse, Color outline )
{	
	int x = mouse_x;
	int y = mouse_y;

	g_Drawing.FilledRect( x, y, 1, 12, outline );
	g_Drawing.FilledRect( x + 1, y, 1, 11, outline );
	g_Drawing.FilledRect( x + 1, y + 11, 1, 1, outline );
	g_Drawing.FilledRect( x + 2, y + 1, 1, 1, outline );
	g_Drawing.FilledRect( x + 2, y + 10, 1, 1, outline );
	g_Drawing.FilledRect( x + 3, y + 2, 1, 1, outline );
	g_Drawing.FilledRect( x + 3, y + 9, 1, 1, outline );
	g_Drawing.FilledRect( x + 4, y + 3, 1, 1, outline );
	g_Drawing.FilledRect( x + 5, y + 4, 1, 1, outline );
	g_Drawing.FilledRect( x + 6, y + 5, 1, 1, outline );
	g_Drawing.FilledRect( x + 7, y + 6, 1, 1, outline );
	g_Drawing.FilledRect( x + 8, y + 7, 1, 1, outline );
	g_Drawing.FilledRect( x + 4, y + 8, 4, 1, outline );

	g_Drawing.FilledRect( x + 1, y + 1, 1, 10, mouse );
	g_Drawing.FilledRect( x + 2, y + 2, 1, 8, mouse );
	g_Drawing.FilledRect( x + 3, y + 3, 1, 6, mouse );
	g_Drawing.FilledRect( x + 4, y + 4, 1, 4, mouse );
	g_Drawing.FilledRect( x + 5, y + 5, 1, 3, mouse );
	g_Drawing.FilledRect( x + 6, y + 6, 1, 2, mouse );
	g_Drawing.FilledRect( x + 7, y + 7, 1, 1, mouse );
}

bool Stuff::Mouse::IsInBox( int x, int y, int w, int h )
{
	if( mouse_x >= x && mouse_x <= x + w && mouse_y >= y && mouse_y <= y + h ) return true;
	else return false;
}

bool mouse1pressed = false;
bool mouse1released = false;
bool mouse2pressed = false;
bool mouse2released = false;

bool mouse1holdpressed = false;
bool mouse1holdreleased = false;
bool mouse2holdpressed = false;
bool mouse2holdreleased = false;

void Stuff::Mouse::Wrapper( )
{
	if( GetAsyncKeyState( VK_LBUTTON ) & 1 ) mouse1pressed = true;
	else if( !( GetAsyncKeyState( VK_LBUTTON ) & 1 ) )
	{
		if( mouse1pressed ) mouse1released = true;
		else mouse1released = false;
		mouse1pressed = false;
	}

	if( ( GetAsyncKeyState( VK_RBUTTON ) & 1 ) ) mouse2pressed = true;
	else if( !( GetAsyncKeyState( VK_RBUTTON ) & 1 ) )
	{
		if( mouse2pressed ) mouse2released = true;
		else mouse2released = false;
		mouse2pressed = false;
	}

	if( GetAsyncKeyState( VK_LBUTTON ) ) mouse1holdpressed = true;
	else if( !( GetAsyncKeyState( VK_LBUTTON ) ) )
	{
		if( mouse1holdpressed ) mouse1holdreleased = true;
		else  mouse1holdreleased = false;
		mouse1holdpressed = false;
	}

	if( ( GetAsyncKeyState( VK_RBUTTON ) ) ) mouse2holdpressed = true;
	else if( !( GetAsyncKeyState( VK_RBUTTON ) ) )
	{
		if( mouse2holdpressed ) mouse2holdreleased = true;
		else mouse2holdreleased = false;
		mouse2holdpressed = false;
	}
}

bool Stuff::Mouse::Click( int x, int y, int w, int h )
{
	if( mouse1pressed && mouse_x > x && w + x > mouse_x && mouse_y > y && h + y > mouse_y ) return true;
	else return false;
}

bool Stuff::Mouse::RightClick( int x, int y, int w, int h )
{
	if( mouse2pressed && mouse_x > x && w + x > mouse_x && mouse_y > y && h + y > mouse_y ) return true;
	else return false;
}

bool Stuff::Mouse::Hold( int x, int y, int w, int h )
{
	if( mouse1holdpressed && mouse_x > x && w + x > mouse_x && mouse_y > y && h + y > mouse_y ) return true;
	else return false;
}

bool Stuff::Mouse::RightHold( int x, int y, int w, int h )
{
	if( mouse2holdpressed && mouse_x > x && w + x > mouse_x && mouse_y > y && h + y > mouse_y ) return true;
	else return false;
}

int savedx, savedy;
bool savepos;
void Stuff::Mouse::DragMenu( int &x, int &y, int w, int h )
{
	if( Hold( x, y, w, h ) )
	{
		if( !savepos )
		{
			savedx = mouse_x - g_CVars.Menu.x;
			savedy = mouse_y - g_CVars.Menu.y;
			savepos = true;
		}

		g_CVars.Menu.x = mouse_x;
		g_CVars.Menu.y = mouse_y;
		g_CVars.Menu.x -= savedx;
		g_CVars.Menu.y -= savedy;
	}
	else savepos = false;
}

int dx, dy;
bool pos;
void Stuff::Mouse::DragRadar( int &x, int &y, int w, int h )
{
	if( Hold( x, y, w, h ) )
	{
		if( !pos )
		{
			dx = mouse_x - g_CVars.Menu.x;
			dy = mouse_y - g_CVars.Menu.y;
			pos = true;
		}

		g_CVars.Menu.x = mouse_x;
		g_CVars.Menu.y = mouse_y;
		g_CVars.Menu.x -= dx;
		g_CVars.Menu.y -= dy;
	}
	else pos = false;
}

//===============================================================================================

double round( double fValue )
{
    return fValue < 0 ? ceil( fValue - 0.5 ) : floor( fValue + 0.5 );
}

float Stuff::GuwopNormalize( float flAngle )
{
	float flNormalizedAngle = 0;	
	float flRevolutions = flAngle / 360;
	
	if( flAngle > 180 || flAngle < -180 )
	{
		if( flRevolutions < 0 ) flRevolutions = -flRevolutions;
 
		flRevolutions = round( flRevolutions );
											
		if( flAngle < 0 ) flNormalizedAngle = ( flAngle + 360 * flRevolutions );
		else flNormalizedAngle = ( flAngle - 360 * flRevolutions );
	}
	else flNormalizedAngle = flAngle;
	return flNormalizedAngle;
}

//===============================================================================================

void Stuff::MovementFix::FixMove( BasePlayer* LocalPlayer, CUserCmd* pCmd, bool angelfix )
{
	int MoveType = LocalPlayer->m_MoveType( );

	QAngle viewangles = pCmd->viewangles, norm;
	vMove = Vector( pCmd->forwardmove, pCmd->sidemove, 0.0f );
	flSpeed = vMove.Length( );
	VectorAngles( vMove, qMove );

	norm.x = g_Stuff.GuwopNormalize( viewangles.x );
	norm.y = g_Stuff.GuwopNormalize( viewangles.y );
	norm.z = g_Stuff.GuwopNormalize( viewangles.z );

	float delta = g_Stuff.GuwopNormalize( ( norm.y - g_Stuff.GuwopNormalize( g_Stuff.viewangles_old.y ) ) );

	flYaw = DEG2RAD( delta + qMove.y );
	if( angelfix ) pCmd->forwardmove = cos( flYaw ) * flSpeed;
	else
	{
		if( norm.x >= 90.0f || norm.x <= -90.0f ) pCmd->forwardmove = -cos( flYaw ) * flSpeed;
		else pCmd->forwardmove = cos( flYaw ) * flSpeed;
	}

	pCmd->sidemove = sin( flYaw ) * flSpeed;
}

//===============================================================================================

void Stuff::AntiAim::AtTargets( BasePlayer* LocalPlayer, CUserCmd* pCmd )
{
	float TmpDistance = 999999.f;

	for( int i = g_pGlobals->maxClients; i >= 1; i-- )
	{
		if( i == g_pEngineClient->GetLocalPlayer( ) ) continue;			
		BasePlayer* Ent = ( BasePlayer* )g_pClientEntityList->GetClientEntity( i );
		if( !Ent ) continue;
		if( !( *( int* )( ( DWORD ) Ent + 0x87 ) == 0 ) ) continue;
		if( Ent->m_iTeamNum( ) == LocalPlayer->m_iTeamNum( ) ) continue;

		Vector dst = Ent->EyePosition( );

		float Distance = ( dst - EyePosition ).Length( );
		if( Distance < TmpDistance )
		{
			TmpDistance = Distance;
			g_Stuff.CalculateAngles( EyePosition, dst, tmp );
			Normalize( tmp );
			pCmd->viewangles = tmp;
		}
	}
}

bool Stuff::AntiAim::WallDetection( BasePlayer* LocalPlayer, CUserCmd* pCmd, float angle )
{
	bool ret = false;

	for( int y = 0; y < 360; y++ )
	{
		QAngle tmp( 10.f, pCmd->viewangles.y, 0.f );
		tmp.y += y;

		Vector forward;
		AngleVectors( tmp, &forward, NULL, NULL );
		float length = ( ( 16 + 3 ) + ( ( 16 + 3 ) * sin( DEG2RAD( 10.f ) ) ) ) + 5;
		forward *= length;

		Ray_t ray;
		trace_t traceData;

		TraceFilterSkipTwoEntities TraceFilter( LocalPlayer, 0 );

		ray.Init( LocalPlayer->EyePosition( ), ( LocalPlayer->EyePosition( ) + forward ) );
		g_pEngineTrace->TraceRay( ray, 0x200400B, NULL, &traceData );

		if( traceData.fraction != 1.f )
		{
			QAngle angles;
			Vector Negate = traceData.plane.normal;
			Negate *= -1;
			VectorAngles( Negate, angles );

			tmp.y = angles.y;
			trace_t leftTrace, rightTrace;

			Vector left, right;
			AngleVectors( tmp + QAngle( 0.f, 30.f, 0.f ), &left, NULL, NULL );
			AngleVectors( tmp - QAngle( 0.f, 30.f, 0.f ), &right, NULL, NULL );

			left *= ( length + ( length * sin( DEG2RAD( 30.f ) ) ) );
			right *= ( length + ( length * sin( DEG2RAD( 30.f ) ) ) );

			ray.Init( LocalPlayer->EyePosition( ), ( LocalPlayer->EyePosition( ) + left ) );
			g_pEngineTrace->TraceRay( ray, 0x200400B, NULL, &leftTrace );

			ray.Init( LocalPlayer->EyePosition( ), ( LocalPlayer->EyePosition( ) + right ) );
			g_pEngineTrace->TraceRay( ray, 0x200400B, NULL, &rightTrace );

			if ( ( leftTrace.fraction == 1.f ) && ( rightTrace.fraction != 1.f ) ) tmp.y -= 90.f;
			else if ( ( leftTrace.fraction != 1.f )	&& ( rightTrace.fraction == 1.f ) ) tmp.y += 90.f;

			pCmd->viewangles.y = tmp.y;
			pCmd->viewangles.y -= angle;
			ret = true;
		}
	}
	return ret;
}

//===============================================================================================

const ConCommandBase *ConCommandBase::GetNext( ) const
{
	return m_pNext;
}

void Stuff::ForceCVars( )
{
	static ConVar* sv_cheats = g_pCvar->FindVar( /*sv_cheats*/XorStr<0x57,10,0xA5D43405>("\x24\x2E\x06\x39\x33\x39\x3C\x2A\x2C"+0xA5D43405).s );
	static ConVar* r_lightaverage = g_pCvar->FindVar( /*r_lightaverage*/XorStr<0xF3,15,0xA900D21B>("\x81\xAB\x99\x9F\x90\x90\x8D\x9B\x8D\x99\x8F\x9F\x98\x65"+0xA900D21B).s );
	static ConVar* cl_pred_optimize = g_pCvar->FindVar( /*cl_pred_optimize*/XorStr<0x60,17,0x4D7607F4>("\x03\x0D\x3D\x13\x16\x00\x02\x38\x07\x19\x1E\x02\x01\x04\x14\x0A"+0x4D7607F4).s );

	static ConVar* cvar_fps_max = g_pCvar->FindVar( /*fps_max*/XorStr<0x41,8,0x6C9C7188>("\x27\x32\x30\x1B\x28\x27\x3F"+0x6C9C7188).s );
	static ConVar* cvar_cl_interp = g_pCvar->FindVar( /*cl_interp*/XorStr<0x72,10,0x8F44826E>("\x11\x1F\x2B\x1C\x18\x03\x1D\x0B\x0A"+0x8F44826E).s );
	static ConVar* cvar_cl_cmdrate= g_pCvar->FindVar( /*cl_cmdrate*/XorStr<0x76,11,0xD36C7CF1>("\x15\x1B\x27\x1A\x17\x1F\x0E\x1C\x0A\x1A"+0xD36C7CF1).s );
	static ConVar* cvar_cl_updaterate = g_pCvar->FindVar( /*cl_updaterate*/XorStr<0x98,14,0x467A5F54>("\xFB\xF5\xC5\xEE\xEC\xF9\xFF\xEB\xC5\xD3\xC3\xD7\xC1"+0x467A5F54).s );
	static ConVar* cvar_sv_mincmdrate = g_pCvar->FindVar( /*sv_mincmdrate*/XorStr<0x14,14,0x203CB2FC>("\x67\x63\x49\x7A\x71\x77\x79\x76\x78\x6F\x7F\x6B\x45"+0x203CB2FC).s );
	static ConVar* cvar_sv_maxcmdrate = g_pCvar->FindVar( /*sv_maxcmdrate*/XorStr<0xED,14,0x9624D396>("\x9E\x98\xB0\x9D\x90\x8A\x90\x99\x91\x84\x96\x8C\x9C"+0x9624D396).s );
	static ConVar* cvar_cl_interp_ratio = g_pCvar->FindVar( /*cl_interp_ratio*/XorStr<0xD5,16,0xA3E6B2C6>("\xB6\xBA\x88\xB1\xB7\xAE\xBE\xAE\xAD\x81\xAD\x81\x95\x8B\x8C"+0xA3E6B2C6).s );
	static ConVar* cvar_sv_minupdaterate = g_pCvar->FindVar( /*sv_minupdaterate*/XorStr<0xA4,17,0xA861A08D>("\xD7\xD3\xF9\xCA\xC1\xC7\xDF\xDB\xC8\xCC\xDA\xCA\xC2\xD0\xC6\xD6"+0xA861A08D).s );
	static ConVar* cvar_sv_maxupdaterate = g_pCvar->FindVar( /*sv_maxupdaterate*/XorStr<0x59,17,0x8813350D>("\x2A\x2C\x04\x31\x3C\x26\x2A\x10\x05\x03\x17\x01\x17\x07\x13\x0D"+0x8813350D).s );
	static ConVar* cvar_sv_client_min_interp_ratio = g_pCvar->FindVar( /*sv_client_min_interp_ratio*/XorStr<0x81,27,0x45846C2E>("\xF2\xF4\xDC\xE7\xE9\xEF\xE2\xE6\xFD\xD5\xE6\xE5\xE3\xD1\xE6\xFE\xE5\xF7\xE1\xE4\xCA\xE4\xF6\xEC\xF0\xF5"+0x45846C2E).s );
	static ConVar* cvar_sv_client_max_interp_ratio = g_pCvar->FindVar( /*sv_client_max_interp_ratio*/XorStr<0xAC,27,0x4AC3C6D1>("\xDF\xDB\xF1\xCC\xDC\xD8\xD7\xDD\xC0\xEA\xDB\xD6\xC0\xE6\xD3\xD5\xC8\xD8\xCC\xCF\x9F\xB3\xA3\xB7\xAD\xAA"+0x4AC3C6D1).s );

	if( cvar_cl_interp_ratio->GetInt( ) == 2 ) cvar_cl_interp_ratio->SetValue( 1 );
	float cl_interp = cvar_cl_interp->GetFloat( );
	int cl_updaterate = cvar_cl_updaterate->GetInt( );
	int sv_maxupdaterate = cvar_sv_maxupdaterate->GetInt( );
	int sv_minupdaterate = cvar_sv_minupdaterate->GetInt( );
	int cl_interp_ratio = cvar_cl_interp_ratio->GetInt( );

	if( sv_minupdaterate > cl_updaterate ) cl_updaterate = sv_minupdaterate;
	if( sv_maxupdaterate <= cl_updaterate ) cl_updaterate = sv_maxupdaterate;

	float new_interp = ( float )cl_interp_ratio / cl_updaterate;
	if( new_interp > cl_interp ) cl_interp = new_interp;

	static bool SetCVars = true;
	if( bMouse )
	{
		if( SetCVars )
		{
			//g_pEngineClient->ExecuteClientCmd( "net_blockmsg svc_GetCvarValue" );

			cvar_fps_max->SetValue( 0 );
			cvar_cl_interp->SetValue( new_interp );
			cvar_cl_cmdrate->SetValue( cvar_sv_maxcmdrate->GetInt( ) );
			cvar_cl_updaterate->SetValue( cl_updaterate );
			cvar_cl_interp_ratio->SetValue( cl_interp_ratio );

			SetCVars = false;
		}
	}
	else
	{
		if( !SetCVars ) SetCVars = true;
	}

	r_lightaverage->SetValue( 1 );

	static bool cheats = true;
	if( g_CVars.Miscellaneous.CheatsBypass )
	{
		sv_cheats->SetValue( 1 );
		cheats = true;
	}
	else
	{
		if( cheats )
		{
			sv_cheats->SetValue( 0 );
			cheats = false;
		}
	}
}

bool Stuff::NextShotPredict( BasePlayer* LocalPlayer, CSWeapon* Weapon )
{
	return ( Weapon->m_flNextPrimaryAttack( ) <= ( ( LocalPlayer->m_nTickBase( ) + 1 ) * g_pGlobals->interval_per_tick ) && Weapon->m_iClip1( ) > 0 );
}

int Stuff::GetFontIndexByDistance( int len )
{
	// todo: do this
	return 0;
}

void Stuff::GetWorldSpaceCenter( BasePlayer* Ent, Vector& vWorldSpaceCenter )
{
	if( Ent )
	{
		Vector mins, maxs;
		Ent->GetRenderBounds( mins, maxs );

		Vector vMin, vMax;
		vMin = mins;
		vMax = maxs;
		vWorldSpaceCenter = Ent->m_vecOrigin( );
		vWorldSpaceCenter.z += ( vMin.z + vMax.z ) / 2.0f;
	}
}

bool Stuff::WorldToScreen( const Vector &vOrigin, Vector &vScreen )
{
	const VMatrix& worldToScreen = g_pEngineClient->WorldToScreenMatrix( );

	float w = worldToScreen[ 3 ][ 0 ] * vOrigin[ 0 ] + worldToScreen[ 3 ][ 1 ] * vOrigin[ 1 ] + worldToScreen[ 3 ][ 2 ] * vOrigin[ 2 ] + worldToScreen[ 3 ][ 3 ];
	vScreen.z = 0;

	if( w > 0.001 )
	{
		float fl1DBw = 1 / w;

		vScreen.x = ( screen_x / 2 ) + ( 0.5 * ( ( worldToScreen[ 0 ][ 0 ] * vOrigin[ 0 ] + worldToScreen[ 0 ][ 1 ] * vOrigin[ 1 ] + worldToScreen[ 0 ][ 2 ] * vOrigin[ 2 ] + worldToScreen[ 0 ][ 3 ] ) * fl1DBw ) * screen_x + 0.5 );
		vScreen.y = ( screen_y / 2 ) - ( 0.5 * ( ( worldToScreen[ 1 ][ 0 ] * vOrigin[ 0 ] + worldToScreen[ 1 ][ 1 ] * vOrigin[ 1 ] + worldToScreen[ 1 ][ 2 ] * vOrigin[ 2 ] + worldToScreen[ 1 ][ 3 ] ) * fl1DBw ) * screen_y + 0.5 );
		return true;
	}

	return false;
}

void Stuff::ForceMaterial( float Red, float Green, float Blue, float Alpha, IMaterial *Material, bool bColor, bool bForceMat )
{
	if( bColor )
	{
		float Temp[ 3 ] = { Red, Green, Blue };
		g_pRender->SetBlend( Alpha );
		g_pRender->SetColorModulation( Temp );
	}
	
	if( bForceMat ) g_pModelRender->ForcedMaterialOverride( Material );
}

IMaterial* Stuff::CreateMaterial( bool VertexLit, bool shouldIgnoreZ, bool isWireframe )
{
	static int created = 0;

	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$receiveflashlight\" \"1\"\
		\n\t\"$singlepassflashlight\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
		\n}\n"
	};
	
	char material[ 512 ];
	sprintf_s( material, sizeof( material ), tmp, ( VertexLit ) ? /*VertexLitGeneric*/XorStr<0xDE,17,0xCA01542A>("\x88\xBA\x92\x95\x87\x9B\xA8\x8C\x92\xA0\x8D\x87\x8F\x99\x85\x8E"+0xCA01542A).s : /*UnlitGeneric*/XorStr<0x4D,13,0x1EAD4D43>("\x18\x20\x23\x39\x25\x15\x36\x3A\x30\x24\x3E\x3B"+0x1EAD4D43).s, ( shouldIgnoreZ ) ? 1 : 0, ( isWireframe ) ? 1 : 0 );
	
	char name[ 512 ];
	sprintf_s( name, sizeof( name ), /*mat_%i.vmt*/XorStr<0x6A,11,0xAE11C1A6>("\x07\x0A\x18\x32\x4B\x06\x5E\x07\x1F\x07"+0xAE11C1A6).s, created ); 
	++created;
	
	KeyValues *keyValues = new KeyValues( ( VertexLit ) ? /*VertexLitGeneric*/XorStr<0x5E,17,0xC83B3F48>("\x08\x3A\x12\x15\x07\x1B\x28\x0C\x12\x20\x0D\x07\x0F\x19\x05\x0E"+0xC83B3F48).s : /*UnlitGeneric*/XorStr<0x95,13,0x1617D1F0>("\xC0\xF8\xFB\xF1\xED\xDD\xFE\xF2\xF8\xEC\xF6\xC3"+0x1617D1F0).s );

	keyValues->LoadFromBuffer( name, material );
	
	IMaterial *createdMaterial = g_pMaterialSystem->CreateMaterial( name, keyValues );
	createdMaterial->IncrementReferenceCount( );
	return createdMaterial;
}

QAngle Stuff::Clamp( QAngle &angle )
{
	if( angle.x >= 180.f ) angle.x -= 360.f;
	else if ( angle.x <= -180.f ) angle.x += 360.f;

	if( angle.y >= 180.f ) angle.y -= 360.f;
	else if ( angle.y <= -180.f ) angle.y += 360.f;

	if( angle.z >= 180.f ) angle.z -= 360.f;
	else if( angle.z <= 180.f ) angle.z += 360.f;

	return angle;
}

float Stuff::Clamp( float &angle )
{
	while ( angle >= 180 ) angle -= 360;
	while ( angle <= -180 ) angle += 360;
	return angle;
}

void Stuff::ForceSeed( CUserCmd* pCmd )
{
	int seed = 141;

	if( seed != -1 )
	{
		for( ;; ++pCmd->command_number )
		{
			pCmd->random_seed = MD5_PseudoRandom( pCmd->command_number ) & 0x7FFFFFFF;
			if( ( pCmd->random_seed & 0xFF ) == seed ) break;
		}
	}

	// todo: find m3 seed
}

void vectorangleshehe( const Vector& forward, QAngle &angles )
{
	float tmp, yaw, pitch;
	if (forward[1] == 0 && forward[0] == 0)
	{
		yaw = 0;
		pitch = 0;
	}
	else
	{
		yaw = atan2(forward[1], forward[0]) * 180 / M_PI;
		if (yaw < 0)
			yaw += 360;
		tmp = g_Stuff.fastSqrt(forward[0] * forward[0] + forward[1] * forward[1]);
		pitch = atan2(-forward[2], tmp) * 180 / M_PI;
	}
	angles[0] = pitch;
	angles[1] = yaw;
	angles[2] = 0;
}

float normalizehehe( float angle )
{
	if( angle < -180 ) angle += 360;
	if( angle > 180 ) angle -= 360;
	return angle;
}

bool Stuff::CanHit( Vector vSource, QAngle qCurAngle, Vector vForward, Vector vRight, Vector vUp, float fMaxDistance, int iLocalTeamNumber, CSWeapon* Weapon, BasePlayer* LocalPlayer, int iSeed )
{
	bool bRet = false;
	trace_t tr;
	Ray_t ray;

	if( g_CVars.Triggerbot.Spread )
	{
		float flSpread = Weapon->GetSpread( );

		RandomSeed( ( iSeed & 255 ) + 1 );
		Vector vSpread;

		vSpread.x = RandomFloat( -0.5f, 0.5f ) + RandomFloat( -0.5f, 0.5f );
		vSpread.y = RandomFloat( -0.5f, 0.5f ) + RandomFloat( -0.5f, 0.5f );

		vSpread.x *= flSpread;
		vSpread.y *= flSpread;

		vForward.x = vForward.x + vSpread.x * vRight.x + vSpread.y * vUp.x;
		vForward.y = vForward.y + vSpread.x * vRight.y + vSpread.y * vUp.y;
		vForward.z = vForward.z + vSpread.x * vRight.z + vSpread.y * vUp.z;

		vForward.NormalizeInPlace( );

		vectorangleshehe( vForward, qCurAngle );

		qCurAngle.x = GuwopNormalize( qCurAngle.x );
		qCurAngle.y = GuwopNormalize( qCurAngle.y );
	}

	if( g_CVars.Triggerbot.Recoil ) qCurAngle += LocalPlayer->GetPunchAngle( ) * 2;

	Vector vEnd;
	AngleVectors( qCurAngle, &vEnd );

	vEnd = vSource + ( vEnd * fMaxDistance );

	DWORD TraceFilter[ 5 ];
	g_Stuff.TraceFilterSkip2Entities( TraceFilter, LocalPlayer, 0, 0 );
	ray.Init( vSource, vEnd );
	g_pEngineTrace->TraceRay( ray, 0x46004003, ( ITraceFilter* )&TraceFilter, &tr );

	if( tr.m_pEnt && tr.m_pEnt->m_iTeamNum( ) != iLocalTeamNumber )
	{
		if( g_CVars.Triggerbot.Hitbox == 0 )
		{
			if( tr.hitgroup == 1 ) bRet = true;
		}
		else if( g_CVars.Triggerbot.Hitbox == 1 )
		{
			if( tr.hitgroup == 2 ) bRet = true;
		}
		else if( g_CVars.Triggerbot.Hitbox == 2 )
		{
			if( tr.hitgroup == 3 ) bRet = true;
		}
		else if( g_CVars.Triggerbot.Hitbox == 3 )
		{
			if( tr.hitgroup == 1 
				|| tr.hitgroup == 2 
				|| tr.hitgroup == 3
				|| tr.hitgroup == 4
				|| tr.hitgroup == 5
				|| tr.hitgroup == 6
				|| tr.hitgroup == 7 ) bRet = true;
		}
	}

	return bRet;
}

bool checkkey( )
{
	// completely not ghett0
	switch( g_CVars.Triggerbot.Key )
	{
		case 0: return true; break;
		case 1:
		{
			if( GetAsyncKeyState( VK_LBUTTON ) ) return true;
			break;
		}
		case 2:
		{
			if( GetAsyncKeyState( VK_RBUTTON ) ) return true;
			break;
		}
		case 3:
		{
			if( GetAsyncKeyState( VK_MBUTTON ) ) return true;
			break;
		}
		case 4:
		{
			if( GetAsyncKeyState( VK_XBUTTON1 ) ) return true;
			break;
		}
		case 5:
		{
			if( GetAsyncKeyState( VK_XBUTTON2 ) ) return true;
			break;
		}
	}
	
	return false;
}

void Stuff::SeedTrigger( CUserCmd* pCmd, BasePlayer* LocalPlayer, CSWeapon* Weapon )
{
	if( !Weapon || !Weapon->IsWeapon( ) ) return;
	g_CVars.Triggerbot.IsShooting = false;

    Vector vEyePosition = LocalPlayer->EyePosition( );
	QAngle qCurAngle = pCmd->viewangles;

	Vector vForward,vRight,vUp;
	AngleVectors( qCurAngle, &vForward, &vRight, &vUp );

	int iMyTeam = LocalPlayer->m_iTeamNum( );

	for( auto i = g_pGlobals->maxClients; i >= 1; --i )
	{
		if( i == g_pEngineClient->GetLocalPlayer( ) ) continue;
		BasePlayer* Ent = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( i );
		if( Ent == 0 ) continue;
		if( Ent->IsDormant( ) ) continue;
		if( Ent->m_iTeamNum( ) == LocalPlayer->m_iTeamNum( ) ) continue;
		if( !( *( int* )( ( DWORD ) Ent + 0x87 ) == 0 ) ) continue;
		if( g_CVars.PlayerList.Friend[ i ] ) continue;

		PVOID pCollisionProperty = Ent->CollisionProperty( );

		PFLOAT pfvecMaxsZ = ( PFLOAT )( ( DWORD ) pCollisionProperty + 0x1C );
		PFLOAT vecSpecifiedSurroundingMaxsZ = ( PFLOAT )( ( DWORD ) pCollisionProperty + 0x40 );

		Vector vMins, vMaxs;
		Ent->GetRenderBounds( vMins, vMaxs );

		if( *pfvecMaxsZ == vMaxs.z && *vecSpecifiedSurroundingMaxsZ == vMaxs.z ) return;

		*pfvecMaxsZ = vMaxs.z;
		*vecSpecifiedSurroundingMaxsZ = vMaxs.z;

		Vector vecSize;
		VectorSubtract( vMaxs, vMins, vecSize );
		float fNewRadius = vecSize.Length( ) * 0.5f;

		*( PFLOAT )( ( DWORD ) pCollisionProperty + 0x42 ) = fNewRadius;

		Ent->AddEFlags( 0x4000 );
	}

	if( checkkey( ) )
	{
		if( !g_CVars.Triggerbot.Seed )
		{
			if( CanHit( vEyePosition, qCurAngle, vForward, vRight, vUp, 8192.0f, iMyTeam, Weapon, LocalPlayer, pCmd->random_seed ) )
			{
				g_CVars.Triggerbot.IsShooting = true;
				pCmd->buttons |= IN_ATTACK;
			}			
		}
		else
		{
			int iHitSeed = 1337;
			int iStrength = 256;

			if( g_CVars.Triggerbot.Strength == 0 ) iStrength = 32;
			else if( g_CVars.Triggerbot.Strength == 1 ) iStrength = 64;
			else if( g_CVars.Triggerbot.Strength == 2 ) iStrength = 128;
			else if( g_CVars.Triggerbot.Strength == 3 ) iStrength = 256;		

			for( int iSeed = 0; iSeed < iStrength; iSeed++ )
			{
				if( CanHit( vEyePosition, qCurAngle, vForward, vRight, vUp, 8192.0f, iMyTeam, Weapon, LocalPlayer, iSeed ) )
				{
					iHitSeed = iSeed;
					break;
				}
			}

			if( iHitSeed != 1337 )
			{
				int iCurrentCommand = pCmd->command_number;
				for( ; ; iCurrentCommand++ )
				{
					int iRandomSeed = ( MD5_PseudoRandom( iCurrentCommand ) & 0x7fffffff ) & 255;
					if( iRandomSeed == iHitSeed )
					{
						pCmd->command_number = iCurrentCommand;
						g_CVars.Triggerbot.IsShooting = true;
						pCmd->buttons |= IN_ATTACK;
						break;
					}
				}
			}
		}
	}
}

void Stuff::NoRecoil( CUserCmd* pCmd, BasePlayer* LocalPlayer, bool isAA )
{
	g_pGameMovement->DecayPunchAngle( );

	if( g_CVars.Miscellaneous.AntiAim.Active )
	{
		if( isAA )
		{
			pCmd->viewangles.x = ( 180 - pCmd->viewangles.x ) - ( LocalPlayer->GetPunchAngle( ).x * 2 );
			pCmd->viewangles.y = -( ( 180 - pCmd->viewangles.y ) + ( LocalPlayer->GetPunchAngle( ).y * 2 ) );
		}
		else pCmd->viewangles -= LocalPlayer->GetPunchAngle( ) * 2;
	}
	else pCmd->viewangles -= LocalPlayer->GetPunchAngle( ) * 2;
}

static bool MustActiveBhop = false;
static bool bLastJumped = false; 
static bool bShouldFake = false;

int lasttick = 0;

float get_delta( float hspeed, float maxspeed, float airaccelerate )
{
	float tickrate = 1 / g_pGlobals->interval_per_tick;
	auto term = ( 30.0 - ( airaccelerate * maxspeed / tickrate ) ) / hspeed; 
	if( term < 1.0f && term > -1.0f ) return acos( term );
 
	return 0.f;
}

inline unsigned long& FloatBits( vec_t& f )
{
	return *reinterpret_cast< unsigned long* >( &f );
}


inline bool IsFinite( vec_t f )
{
	return ( ( FloatBits( f ) & 0x7F800000) != 0x7F800000 );
}


bool CheckIfNonValidNumber( float num )
{
	return !IsFinite( num );
}

float GetDegreeFromVelocity( float VelocityLength2D )
{
    auto tmp = RAD2DEG( atan( 30.0 / VelocityLength2D ) );

    if( CheckIfNonValidNumber( tmp ) || tmp > 90.f ) return 90.f;
    else if( tmp < 0.f ) return 0.f;
    else return tmp;
};

float GetVelocityYawStep( Vector Velocity, float NewCircleYaw )
{
	if( !g_pEngineClient->GetLocalPlayer( ) ) return 0.f;
	BasePlayer* LocalPlayer = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( g_pEngineClient->GetLocalPlayer( ) );	
	float degVelocity = RAD2DEG( atan2( Velocity.x, Velocity.y ) ), retn = 1.5f;

	Vector start = LocalPlayer->EyePosition( ), end = LocalPlayer->EyePosition( );
	//Ray_t ray;
	trace_t trace;
	//CTraceFilterWorldOnly filter;

	while( true )
	{
		end.x = end.x + ( ( cos( DEG2RAD( degVelocity + NewCircleYaw ) ) * Velocity.Length2D( ) ) * g_pGlobals->interval_per_tick );
		end.y = end.y + ( ( sin( DEG2RAD( degVelocity + NewCircleYaw ) ) * Velocity.Length2D( ) ) * g_pGlobals->interval_per_tick );
																  
		Vector mins = LocalPlayer->m_vecMins( ); //Vector( -16.f, -16.f, 0.f );
		Vector maxs = LocalPlayer->m_vecMaxs( ); //Vector( 16.f, 16.f, 45.f );
		
		// todo: check what fks up here

		//ray.Init( start, end, mins, maxs );
		//g_pEngineTrace->TraceRay( ray, CONTENTS_SOLID, &filter, &trace ); 
		g_Stuff.UTIL_TraceHull( start, end, mins, maxs, CONTENTS_SOLID, LocalPlayer, 1, &trace );
		
		if( trace.fraction < 1.0 || trace.allsolid || trace.startsolid ) break;
		
		retn -= g_pGlobals->interval_per_tick;
		
		if( retn == 0.f ) break;
		
		start = end;
		degVelocity += ( degVelocity + NewCircleYaw );
	}
	
	return retn;
};

static float CircleYaw = 0.f, OldYaw = 0.f;
void BigPolishAutostrafer( CUserCmd* pCmd, BasePlayer* LocalPlayer ) 
{
	if( LocalPlayer->m_MoveType( ) != MOVETYPE_WALK ) return;
	
	auto Velocity = LocalPlayer->m_vecVelocity( );
	Velocity.z = 0;
	
	static bool Switch = false;
	float SwitchFloat = ( Switch ) ? 1.f : -1.f;
	Switch = !Switch;
	
	static bool in_strafing = false;
	
	if( ( GetAsyncKeyState( 'V' ) & 0x8000 ) && g_CVars.Miscellaneous.CircleStrafe )
	{
		float tmp = GetDegreeFromVelocity( Velocity.Length2D( ) );
		CircleYaw = g_Stuff.GuwopNormalize( CircleYaw + tmp );
		
		float v14 = GetVelocityYawStep( Velocity, tmp );
		float tickrate = 1 / g_pGlobals->interval_per_tick;

		if( v14 != 0.f ) CircleYaw += ( ( g_pGlobals->interval_per_tick * tickrate ) * v14 ) * v14;
		
		g_Stuff.viewangles_old.y = g_Stuff.GuwopNormalize( CircleYaw );
		pCmd->sidemove = -450.f;
		return;
	}
	
	if( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) return;
	
	if( pCmd->forwardmove > 0.f ) pCmd->forwardmove = 0.f;
	
	auto StrafeAngle = RAD2DEG( atan( 15.f / Velocity.Length2D( ) ) );
	
	if( StrafeAngle > 90.f ) StrafeAngle = 90.f;
	else if( StrafeAngle < 0.f ) StrafeAngle = 0.f;
	
	auto YawDelta = g_Stuff.GuwopNormalize( g_Stuff.viewangles_old.y - OldYaw );
	OldYaw = g_Stuff.viewangles_old.y;
	
	if( YawDelta > 0.f ) pCmd->sidemove = -450.f;
	else if( YawDelta < 0.f ) pCmd->sidemove = 450.f;
	
	auto AbsYawDelta = abs( YawDelta );
	
	if( AbsYawDelta <= StrafeAngle || AbsYawDelta >= 30.f )
	{
		QAngle VelocityAngles;
		VectorAngles( Velocity, VelocityAngles );
		
		auto VelocityAngleYawDelta = g_Stuff.GuwopNormalize( g_Stuff.viewangles_old.y - VelocityAngles.y );
		auto VelocityDegree = 15.f;
		
		if( VelocityAngleYawDelta <= VelocityDegree || Velocity.Length2D( ) <= 15.f )
		{
			if( -( VelocityDegree ) <= VelocityAngleYawDelta || Velocity.Length2D( ) <= 15.f )
			{
				g_Stuff.viewangles_old.y += ( StrafeAngle * SwitchFloat );
				pCmd->sidemove = 450.f * SwitchFloat;
			}
			else
			{
				g_Stuff.viewangles_old.y = VelocityAngles.y - VelocityDegree;
				pCmd->sidemove = 450.f;
			}
		}
		else
		{
			g_Stuff.viewangles_old.y = VelocityAngles.y + VelocityDegree;
			pCmd->sidemove = -450.f;
		}
	}
	
	pCmd->buttons &= ~( IN_MOVELEFT | IN_MOVERIGHT | IN_FORWARD | IN_BACK );
	
	if( pCmd->sidemove <= 0.f ) pCmd->buttons |= IN_MOVELEFT;
	else pCmd->buttons |= IN_MOVERIGHT;
	
	if( pCmd->forwardmove <= 0.f ) pCmd->buttons |= IN_BACK;
	else pCmd->buttons |= IN_FORWARD;
}

void Stuff::AutoStrafe( CUserCmd* pCmd, BasePlayer* LocalPlayer )
{
	// removed my old astrafer
	// good but the code was ugly asf
	if( GetAsyncKeyState( VK_SPACE ) ) BigPolishAutostrafer( pCmd, LocalPlayer );
}

void Stuff::BunnyHop( CUserCmd* pCmd, BasePlayer* LocalPlayer )
{
	Flags = LocalPlayer->m_fFlags( );

	if( !( Flags & FL_ONGROUND ) ) MustActiveBhop = true;
	else MustActiveBhop = false;

	if( !bLastJumped && bShouldFake ) 
	{ 
		bShouldFake = false; 
		pCmd->buttons |= IN_JUMP;  
	} 
	else if( pCmd->buttons & IN_JUMP ) 
	{ 
		if( !MustActiveBhop ) 
		{ 
			bLastJumped = true; 
			bShouldFake = true; 
		} 
		else 
		{ 
			pCmd->buttons &= ~IN_JUMP; 
			pCmd->buttons |= IN_JUMP;
			pCmd->buttons &= ~IN_JUMP;
			bLastJumped = false; 
		} 
	} 
	else 
	{ 
		bLastJumped = false; 
		bShouldFake = false; 
	}
}

void Stuff::EdgeJump( CUserCmd* pCmd, BasePlayer* LocalPlayer )
{
	if( GetAsyncKeyState( 'V' ) )
	{
		int MoveType = *( int* )( ( DWORD ) LocalPlayer + 0x134 );

		if( MoveType == 9 ) return;

		Vector start, end;
		VectorCopy( LocalPlayer->m_vecOrigin( ), start );
		VectorCopy( start, end );
	
		end.z -= 16;
	
		Vector vecMins = *( Vector* )( LocalPlayer + 0x168 );
		Vector vecMaxs = *( Vector* )( LocalPlayer + 0x174 );
	
		Ray_t ray;
		ray.Init( start, end, vecMins, vecMaxs );
	
		TraceFilterSkipTwoEntities TraceFilter( ( IHandleEntity* )LocalPlayer, NULL );
	
		trace_t trace;
		g_pEngineTrace->TraceRay( ray, MASK_PLAYERSOLID_BRUSHONLY, ( ITraceFilter* )&TraceFilter, &trace );
	
		if( trace.fraction == 1.0f ) pCmd->buttons |= IN_JUMP;
	}
}

float __fastcall Stuff::fastSqrt( float ehi )
{
	float tmp = ehi;
	float half = 0.5f * ehi;
	int i = *reinterpret_cast< int* >( &ehi );

	i = 0x5f3759df - ( i >> 1 );
	ehi = *reinterpret_cast<float*>( &i );
  
	ehi = ehi * ( 1.5f - half * ehi * ehi ); 
	ehi = ehi * ( 1.5f - half * ehi * ehi );

	return tmp * ehi;
}

void Stuff::VectorAngles_( const Vector &forward, const Vector &pseudoup, QAngle &angles )
{
	Vector left;

	CrossProduct( pseudoup, forward, left );
	VectorNormalizeFast( left );		
	
	float xyDist = sqrtf( forward[ 0 ] * forward[ 0 ] + forward[ 1 ] * forward[ 1 ] );

	if ( xyDist > 0.001f )
	{
		angles[ 1 ] = RAD2DEG( atan2f( forward[ 1 ], forward[0 ] ) );
		angles[ 0 ] = RAD2DEG( atan2f( -forward[ 2 ], xyDist ) );
		float up_z = ( left[ 1 ] * forward[ 0 ] ) - ( left[ 0 ] * forward[ 1 ] );
		angles[ 2 ] = RAD2DEG( atan2f( left[ 2 ], up_z ) );
	}
	else
	{
		angles[ 1 ] = RAD2DEG( atan2f( -left[ 0 ], left[ 1 ] ) );
		angles[ 0 ] = RAD2DEG( atan2f( -forward[ 2 ], xyDist ) );
		angles[ 2 ] = 0;
	}	
}

void inline Stuff::SinCos( float radians, float *sine, float *cosine )
{
	_asm
	{
		fld DWORD PTR [ radians ]
		fsincos
		mov edx, DWORD PTR [ cosine ]
		mov eax, DWORD PTR [ sine ]
		fstp DWORD PTR [ edx ]
		fstp DWORD PTR [ eax ]
	}
}

void Stuff::AngleVectors_( const float *angles, float *forward, float *right, float *up )
{
	float sr, sp, sy, cr, cp, cy;

	SinCos( DEG2RAD( angles[ 1 ] ), &sy, &cy );
	SinCos( DEG2RAD( angles[ 0 ] ), &sp, &cp );
	SinCos( DEG2RAD( angles[ 2 ] ), &sr, &cr );

	if( forward )
	{
		forward[ 0 ] = cp*cy;
		forward[ 1 ] = cp*sy;
		forward[ 2 ] = -sp;
	}

	if( right )
	{
		right[ 0 ] = ( -1 * sr * sp * cy + -1 * cr * -sy );
		right[ 1 ] = ( -1 * sr * sp * sy + -1 * cr * cy );
		right[ 2 ] = -1 * sr * cp;
	}

	if( up )
	{
		up[ 0 ] = ( cr * sp * cy + -sr *-sy);
		up[ 1 ] = ( cr * sp * sy + -sr * cy );
		up[ 2 ] = cr * cp;
	}
}

void Stuff::CalculateAngles( Vector src, Vector dst, QAngle &angles )
{
	double delta[3] = { ( src[ 0 ] - dst[ 0 ] ), ( src[ 1 ] - dst[ 1 ] ), ( src[ 2 ] - dst[ 2 ] ) };
	double hyp = sqrt( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );
	angles[ 0 ] = ( float )( atan( delta[ 2 ] / hyp ) * 57.2957914 );
	angles[ 1 ] = ( float )( atan( delta[ 1 ] / delta[ 0 ] ) * 57.2957914 );
	angles[ 2 ] = 0.f;
	if( delta[ 0 ] >= 0.0 ) angles[ 1 ] += 180.f;
}

int Stuff::lerp( int t, int a, int b )
{
	return ( 1 - t ) * a + t * b;
}

bool Stuff::IsReadyToShoot( BasePlayer* LocalPlayer, CSWeapon* Weapon )
{
	if( !LocalPlayer ) return false;
	if( !Weapon ) return false;

	int WeaponID = Weapon->GetWeaponID( );
	float curtime = g_pGlobals->interval_per_tick * LocalPlayer->m_nTickBase( );

	if( WeaponID == WEAPON_GLOCK )
	{
		if( Weapon->SpecialMode( ) )
		{
			if( Weapon->m_flGlock18Shoot( ) > 0.f ) return true;
		}
	}
	else if( WeaponID == WEAPON_FAMAS )
	{
		if( Weapon->SpecialMode( ) )
		{
			if( Weapon->m_flFamasShoot( ) > 0.f && Weapon->m_flFamasShoot( ) < curtime ) return true;
		}
	}

	return Weapon->m_flNextPrimaryAttack( ) <= curtime && LocalPlayer->m_flNextAttack( ) <= curtime && Weapon->m_iClip1( ) > 0;
}

void Stuff::TraceFilterSkip2Entities( void* thisptr, const BaseEntity* PassEntity, const BaseEntity* PassEntity2, int CollisionGroup )
{
	typedef void( __thiscall *TraceFilterSkipTwoEntities_t )( void* thisptr, const BaseEntity* PassEntity, const BaseEntity* PassEntity2, int CollisionGroup );
	( ( TraceFilterSkipTwoEntities_t )( ( DWORD ) BASE_CLIENT + 0x160A80 ) )( thisptr, PassEntity, PassEntity2, CollisionGroup );
}

void Stuff::UTIL_TraceLine( const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, const IHandleEntity* ignore, int collisionGroup, trace_t* ptr )
{
	typedef void( __cdecl *UTIL_TraceLine_t )( const Vector&, const Vector&, unsigned int, const IHandleEntity*, int, trace_t* );
	( ( UTIL_TraceLine_t )( ( DWORD ) BASE_CLIENT + 0x13E90 ) )( vecAbsStart, vecAbsEnd, mask, ignore, collisionGroup, ptr );
}

void Stuff::UTIL_TraceHull( const Vector &vecAbsStart, const Vector& vecAbsEnd, const Vector& hullMin, const Vector& hullMax, unsigned int mask, const IHandleEntity* ignore, int collisionGroup, trace_t *ptr )
{
	typedef void( *UTIL_TraceHull_t )( const Vector&, const Vector&, const Vector&, const Vector&, unsigned int, const IHandleEntity*, int, trace_t* );
	( ( UTIL_TraceHull_t )( ( DWORD ) BASE_CLIENT + 0x18A60 ) )( vecAbsStart, vecAbsEnd, hullMin, hullMax, mask, ignore, collisionGroup, ptr );
}

void Stuff::UTIL_TraceHull2( const Vector &vecAbsStart, const Vector &vecAbsEnd, const Vector &hullMin, const Vector &hullMax, unsigned int mask, const IHandleEntity *ignore, int collisionGroup, trace_t *ptr )
{
	typedef void( *UTIL_TraceHull_t )( const Vector&, const Vector&, const Vector&, const Vector&, unsigned int, const IHandleEntity*, int, trace_t* );
	( ( UTIL_TraceHull_t )( ( DWORD ) BASE_CLIENT + 0xA3DC0 ) )( vecAbsStart, vecAbsEnd, hullMin, hullMax, mask, ignore, collisionGroup, ptr );
}

void Stuff::FindHullIntersection( const Vector& vecSrc, trace_t& tr, const Vector& mins, const Vector& maxs, BaseEntity* pEntity )
{
	typedef void( *FindHullIntersection_t )( const Vector&, trace_t&, const Vector&, const Vector&, BaseEntity* );
	( ( FindHullIntersection_t )( ( DWORD ) BASE_CLIENT + 0x1E66D0 ) )( vecSrc, tr, mins, maxs, pEntity );
}

bool Stuff::IsBSPModel( void* ptr )
{
	typedef bool( __thiscall* IsBSPModel_t )( void* );
	return ( ( IsBSPModel_t )( ( DWORD ) BASE_CLIENT + 0x124D0 ) )( ptr );
}

void Stuff::ClipTraceToPlayers( const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, void* filter, trace_t* tr )
{
	typedef void( *UTIL_ClipTraceToPlayers_t )( const Vector& vecAbsStart, const Vector& vecAbsEnd, unsigned int mask, void* filter, trace_t* tr );
	( ( UTIL_ClipTraceToPlayers_t )( ( DWORD ) BASE_CLIENT + 0x1613F0 ) )( vecAbsStart, vecAbsEnd, mask, filter, tr );
}

void Stuff::MoveToLastReceivedPosition( BasePlayer* Ent, bool force )
{
	*( float* )( ( DWORD ) Ent + 0x204 ) = Ent->m_vecOrigin( ).x;
	*( float* )( ( DWORD ) Ent + 0x208 ) = Ent->m_vecOrigin( ).y;
	*( float* )( ( DWORD ) Ent + 0x20C ) = Ent->m_vecOrigin( ).z;

	*( float* )( ( DWORD ) Ent + 0x238 ) = Ent->m_angRotation( ).x;
	*( float* )( ( DWORD ) Ent + 0x23C ) = Ent->m_angRotation( ).y;
    *( float* )( ( DWORD ) Ent + 0x240 ) = Ent->m_angRotation( ).z;
}

void Stuff::RemoveFromInterpolationList( BasePlayer* Ent )
{
	typedef void( __thiscall* RemoveFromInterpolationList_t )( void* );
	( ( RemoveFromInterpolationList_t )( ( DWORD ) BASE_CLIENT + 0x4BFA0 ) )( Ent );
}


void Stuff::AddToInterpolationList( BasePlayer* Ent )
{
	typedef void( __thiscall* RemoveFromInterpolationList_t )( void* );
	( ( RemoveFromInterpolationList_t )( ( DWORD ) BASE_CLIENT + 0x4C4C0 ) )( Ent );
}

void Stuff::SetAbsOrigin( BasePlayer* Ent, const Vector& absOrigin )
{
	typedef void( __thiscall* SetAbsOrigin_t )( void*, const Vector& );
	( ( SetAbsOrigin_t )( ( DWORD ) BASE_CLIENT + 0x45620 ) )( Ent, absOrigin );
}

void Stuff::SetAbsAngles( BasePlayer* Ent, const QAngle& absAngles )
{
	typedef void( __thiscall* SetAbsAngles_t )( void*, const QAngle& );
	( ( SetAbsAngles_t )( ( DWORD ) BASE_CLIENT + 0x45720 ) )( Ent, absAngles );
}

void Stuff::EstimateAbsVelocity( BasePlayer* Ent, Vector& vec )
{
	typedef void( __thiscall* EstimateAbsVelocity_t )( void*, Vector& );
	( ( EstimateAbsVelocity_t )( ( DWORD ) BASE_CLIENT + 0x4B3A0 ) )( Ent, vec );
}

bool Stuff::KnifeBot::CanKnife( bool bStab, CUserCmd* pCmd, BasePlayer* LocalPlayer, BasePlayer* Ent )
{
	float fRange = bStab ? 31 : 47;

	const Vector head_hull_mins = *( Vector* )( ( DWORD ) BASE_CLIENT + 0x39E194 );
	const Vector head_hull_maxs = *( Vector* )( ( DWORD ) BASE_CLIENT + 0x39E1A0 );
	const Vector mins = LocalPlayer->m_vecMins( );
	const Vector maxs = LocalPlayer->m_vecMaxs( );

	Vector forward;
	AngleVectors( pCmd->viewangles, &forward );
	Vector end = LocalPlayer->EyePosition( ) + forward * fRange;

	trace_t tr;
	g_Stuff.UTIL_TraceLine( LocalPlayer->EyePosition( ), end, MASK_SOLID, ( IHandleEntity* ) LocalPlayer, 0, &tr );

	if( tr.fraction >= 1.0 )
	{
		g_Stuff.UTIL_TraceHull( LocalPlayer->EyePosition( ), end, head_hull_mins, head_hull_maxs, MASK_SOLID, ( IHandleEntity* ) LocalPlayer, 0, &tr );
		if( tr.fraction < 1.0 )
		{
			if( !tr.m_pEnt || g_Stuff.IsBSPModel( tr.m_pEnt ) ) g_Stuff.FindHullIntersection( LocalPlayer->EyePosition( ), tr, mins, maxs, LocalPlayer );
			end = tr.endpos;
		}
	}

	if( ( tr.fraction < 1.0 ) && ( tr.m_pEnt->entindex( ) == Ent->entindex( ) ) )
	{
		TargetIndex = Ent->entindex( );
		return true;
	}
	else return false;
}

void Stuff::KnifeBot::Main( CUserCmd* pCmd, BasePlayer* LocalPlayer, CSWeapon* Weapon )
{
	if( !Weapon ) return;

	if( Weapon->GetWeaponID( ) == WEAPON_KNIFE )
	{
		for( auto i = g_pGlobals->maxClients; i >= 1; --i )
		{
			if( i == g_pEngineClient->GetLocalPlayer( ) ) continue;
			BasePlayer* Ent = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( i );
			if( Ent == 0 ) continue;
			if( Ent->IsDormant( ) ) continue;
			if( Ent->m_iTeamNum( ) == LocalPlayer->m_iTeamNum( ) ) continue;
			if( !( *( int* )( ( DWORD ) Ent + 0x87 ) == 0 ) ) continue;
			if( g_CVars.PlayerList.Friend[ i ] ) continue;

			bool bFirstSwing = ( Weapon->m_flNextPrimaryAttack( ) + 0.4 ) < g_pGlobals->curtime;

			if( ( Ent->m_iHealth( ) <= 20 ) && bFirstSwing )
			{
				if( CanKnife( false, pCmd, LocalPlayer, Ent ) ) pCmd->buttons |= IN_ATTACK;
			}
			else if ( ( Ent->m_iHealth( ) <= 15 ) && !bFirstSwing )
			{
				if( CanKnife( false, pCmd, LocalPlayer, Ent ) ) pCmd->buttons |= IN_ATTACK;
			}
			else
			{
				if( CanKnife( true, pCmd, LocalPlayer, Ent ) ) pCmd->buttons |= IN_ATTACK2;
			}
		}
	}
}

void Stuff::FixCollision( BasePlayer* LocalPlayer, BasePlayer* Ent )
{
	// thx kolo

	PVOID pCollisionProperty = Ent->CollisionProperty( );

	PFLOAT pfvecMaxsZ = ( PFLOAT )( ( DWORD ) pCollisionProperty + 0x1C );
	PFLOAT vecSpecifiedSurroundingMaxsZ = ( PFLOAT )( ( DWORD ) pCollisionProperty + 0x40 );

	Vector vMins, vMaxs;
	Ent->GetRenderBounds( vMins, vMaxs );

	if( *pfvecMaxsZ == vMaxs.z && *vecSpecifiedSurroundingMaxsZ == vMaxs.z ) return;

	*pfvecMaxsZ = vMaxs.z;
	*vecSpecifiedSurroundingMaxsZ = vMaxs.z;

	Vector vecSize;
	VectorSubtract( vMaxs, vMins, vecSize );
	float fNewRadius = vecSize.Length( ) * .5f;

	*( PFLOAT )( ( DWORD ) pCollisionProperty + 0x42 ) = fNewRadius;

	Ent->AddEFlags( 0x4000 );
}

CTickRecord pPlayerHistory[ 64 ][ 32 ];
CTickRecord pSimulationData[ 64 ];
CTickRecord pBackupData[ 64 ];

void Stuff::ApplyTickRecord( BasePlayer* Entity, CTickRecord* Record )
{
	typedef void( __thiscall* InvalidatePhysicsRecursive_t )( void*, int );
	( ( InvalidatePhysicsRecursive_t )( ( DWORD ) BASE_CLIENT + 0x143F0 ) )( Entity, InvalidatePhysicsBits_t::ANGLES_CHANGED | InvalidatePhysicsBits_t::ANIMATION_CHANGED | InvalidatePhysicsBits_t::POSITION_CHANGED | InvalidatePhysicsBits_t::VELOCITY_CHANGED );

	Entity->m_angNetworkAngles( ) = Record->m_EyeAngles;
	Entity->m_vecOrigin( ) = Record->m_Origin;
	Entity->m_flSimulationTime( ) = Record->m_SimulationTime;
	Entity->m_nSequence( ) = Record->m_Sequence;
	Entity->m_fFlags( ) = Record->m_Flags;
	Entity->m_flCycle( ) = Record->m_Cycle;
	Entity->m_vecVelocity( ) = Record->m_Velocity;
	Entity->m_vecMins( ) = Record->m_Mins;
	Entity->m_vecMaxs( ) = Record->m_Maxs;
	SetAbsOrigin( Entity, Record->m_Origin );
	SetAbsAngles( Entity, Record->m_EyeAngles );

	for( INT idx = 0; idx < 15; idx++ )
	{
		DWORD_PTR currentLayer = *( DWORD_PTR* )( ( DWORD_PTR ) Entity + 1712 ) + 32 * idx;
		if( currentLayer != 0x0 )
		{
			C_AnimationLayer& record = Record->m_AnimationLayer[ idx ];
			*( int* )( currentLayer ) = record.nSequence;
			*( float* )( currentLayer + 8 ) = record.flWeight;
			*( float* )( currentLayer + 20 ) = record.flCycle;
			*( int* )( currentLayer + 12 ) = record.nOrder;
		}
	}

	for( auto i = 0; i < 24; ++i ) *( float* )( ( DWORD ) Entity + 0x518 + ( 0x4 * i ) ) = Record->m_PoseParameter[ i ];
	for( auto i = 0; i < 4; ++i ) *( float* )( ( DWORD ) Entity + 0x5CC + ( 0x4 * i ) ) = Record->m_EncodedController[ i ];
	for( auto i = 0; i < 64; ++i ) *( float* )( ( DWORD ) Entity + 0x74C + ( 0x4 * i ) ) = Record->m_flexWeight[ i ];
}

void Stuff::StoreTickRecord( BasePlayer* Entity, CTickRecord* Record )
{
	static ConVar* cvar_cl_interp = g_pCvar->FindVar( XorStr<0xAD,10,0x4CBB6338>("\xCE\xC2\xF0\xD9\xDF\xC6\xD6\xC6\xC5"+0x4CBB6338).s );
	static ConVar* cvar_cl_updaterate = g_pCvar->FindVar( XorStr<0x11,14,0xBB703A35>("\x72\x7E\x4C\x61\x65\x72\x76\x6C\x7C\x68\x7A\x68\x78"+0xBB703A35).s );
	static ConVar* cvar_cl_interp_ratio = g_pCvar->FindVar( XorStr<0x9F,16,0x8A043D47>("\xFC\xCC\xFE\xCB\xCD\xD0\xC0\xD4\xD7\xF7\xDB\xCB\xDF\xC5\xC2"+0x8A043D47).s );
	static ConVar* cvar_sv_minupdaterate = g_pCvar->FindVar( XorStr<0x1E,17,0x79A19D68>("\x6D\x69\x7F\x4C\x4B\x4D\x51\x55\x42\x46\x5C\x4C\x58\x4A\x58\x48"+0x79A19D68).s );
	static ConVar* cvar_sv_maxupdaterate = g_pCvar->FindVar( XorStr<0x7C,17,0xA8DDFDC6>("\x0F\x0B\x21\x12\xE1\xF9\xF7\xF3\xE0\xE4\xF2\xE2\xFA\xE8\xFE\xEE"+0xA8DDFDC6).s );
	static ConVar* cvar_sv_client_min_interp_ratio = g_pCvar->FindVar( XorStr<0xB9,27,0x47A07A44>("\xCA\xCC\xE4\xDF\xD1\xD7\xDA\xAE\xB5\x9D\xAE\xAD\xAB\x99\xAE\xA6\xBD\xAF\xB9\xBC\x92\xBC\xAE\xA4\xB8\xBD"+0x47A07A44).s );
	static ConVar* cvar_sv_client_max_interp_ratio = g_pCvar->FindVar( XorStr<0x99,27,0xB4857844>("\xEA\xEC\xC4\xFF\xF1\xF7\xFA\xCE\xD5\xFD\xCE\xC5\xDD\xF9\xCE\xC6\xDD\xCF\xD9\xDC\xF2\xDC\xCE\xC4\xD8\xDD"+0xB4857844).s );

	float cl_interp = cvar_cl_interp->GetFloat( );
	int cl_updaterate = cvar_cl_updaterate->GetInt( );
	int sv_maxupdaterate = cvar_sv_maxupdaterate->GetInt( );
	int sv_minupdaterate = cvar_sv_minupdaterate->GetInt( );
	int cl_interp_ratio = cvar_cl_interp_ratio->GetInt( );
	int sv_client_min_interp_ratio = cvar_sv_client_min_interp_ratio->GetInt( );
	int sv_client_max_interp_ratio = cvar_sv_client_max_interp_ratio->GetInt( );

	if( sv_client_min_interp_ratio > cl_interp_ratio ) cl_interp_ratio = sv_client_min_interp_ratio;
	if( cl_interp_ratio > sv_client_max_interp_ratio ) cl_interp_ratio = sv_client_max_interp_ratio;
	if( sv_maxupdaterate <= cl_updaterate ) cl_updaterate = sv_maxupdaterate;
	if( sv_minupdaterate > cl_updaterate ) cl_updaterate = sv_minupdaterate;

	float interp = cl_interp_ratio / cl_updaterate;
	if( interp > cl_interp ) cl_interp = interp;

	Record->m_Origin = Entity->m_vecOrigin( );
	Record->m_SimulationTime = Entity->m_flSimulationTime( );
	Record->m_Sequence = Entity->m_nSequence( );
	Record->m_Flags = Entity->m_fFlags( );
	Record->m_Cycle = Entity->m_flCycle( );
	Record->m_EyeAngles = Entity->m_angEyeAngles( );
	Record->m_Velocity = Entity->m_vecVelocity( );
	Record->m_Mins = Entity->m_vecMins( );
	Record->m_Maxs = Entity->m_vecMaxs( );

	for( INT idx = 0; idx < 15; idx++ )
	{
		DWORD_PTR currentLayer = *( DWORD_PTR* )( ( DWORD_PTR ) Entity + 1712 ) + 32 * idx;
		if( currentLayer != 0x0 )
		{
			C_AnimationLayer& record = Record->m_AnimationLayer[ idx ];
			record.nSequence = *( int* )( currentLayer );
			record.flWeight = *( float* )( currentLayer + 8 );
			record.flCycle = *( float* )(currentLayer + 20 );
			record.nOrder = *( int* )( currentLayer + 12 );
		}
	}

	for( auto i = 0; i < 24; ++i ) Record->m_PoseParameter[ i ] = *( float* )( ( DWORD ) Entity + 0x518 + ( 0x4 * i ) );
	for( auto i = 0; i < 4; ++i ) Record->m_EncodedController[ i ] = *( float* )( ( DWORD ) Entity + 0x5CC + ( 0x4 * i ) );
	for( auto i = 0; i < 64; ++i ) Record->m_flexWeight[ i ] = *( float* )( ( DWORD ) Entity + 0x74C + ( 0x4 * i ) );
}