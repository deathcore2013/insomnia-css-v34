#include "Main.h"

CConfig g_Config;

float GetPrivateProfileFloat( LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flDefault, LPCSTR lpFileName )
{
	char szData[ 32 ];
	GetPrivateProfileStringA( lpAppName, lpKeyName, std::to_string( flDefault ).c_str( ), szData, 32, lpFileName );
	return ( float )atof( szData );
}

void WritePrivateProfileFloat( LPCSTR lpAppName, LPCSTR lpKeyName, FLOAT flValue, LPCSTR lpFileName )
{
	WritePrivateProfileStringA( lpAppName, lpKeyName, std::to_string( ( float )flValue ).c_str( ), lpFileName );
}

// =======================================================================================================================

int GetPrivateProfileInteger( LPCSTR lpAppName, LPCSTR lpKeyName, INT flDefault, LPCSTR lpFileName )
{
	char szData[ 32 ];
	GetPrivateProfileStringA( lpAppName, lpKeyName, std::to_string( flDefault ).c_str( ), szData, 32, lpFileName );
	return atoi( szData );
}

void WritePrivateProfileInteger( LPCSTR lpAppName, LPCSTR lpKeyName, INT flValue, LPCSTR lpFileName )
{
	WritePrivateProfileStringA( lpAppName, lpKeyName, std::to_string( ( int )flValue ).c_str( ), lpFileName );
}

// =======================================================================================================================

void GetPrivateProfileColor( LPCSTR lpAppName, LPCSTR lpKeyName, Color &cvar, LPCSTR lpFileName )
{
	char szData[ 32 ];
	char *red, *green, *blue;
	GetPrivateProfileStringA( lpAppName, lpKeyName, "r0,g0,b0", szData, 32, lpFileName );

	int len = strlen( szData );
	for( int i = 0; i < len; i++ )
	{
		if( szData[ i ] == 'r' && szData[ i + 2 ] == ',' ) red = &szData[ i + 1 ];
		else if( szData[ i ] == 'r' && szData[ i + 3 ] == ',' ) red = &szData[ i + 1 ];
		else if( szData[ i ] == 'r' && szData[ i + 4 ] == ',' ) red = &szData[ i + 1 ];

		if( szData[ i ] == 'g' && szData[ i + 2 ] == ',' ) green = &szData[ i + 1 ];
		else if( szData[ i ] == 'g' && szData[ i + 3 ] == ',' ) green = &szData[ i + 1 ];
		else if( szData[ i ] == 'g' && szData[ i + 4 ] == ',' ) green = &szData[ i + 1 ];

		if( szData[ i ] == 'b' ) blue = &szData[ i + 1 ];
	}

	len = strlen( red );
	
	for( int i = 0; i < len; i++ )
	{
		if( red[ i ] == ',' && red[ i + 1 ] == 'g' ) red[ i ] = 0;
	}

	len = strlen( green );

	for( int i = 0; i < len; i++ )
	{
		if( green[ i ] == ',' && green[ i + 1 ] == 'b' ) green[ i ] = 0;
	}

	std::string r, g, b;
	r = red;
	g = green;
	b = blue;

	cvar = Color( atoi( r.c_str( ) ), atoi( g.c_str( ) ), atoi( b.c_str( ) ), 255 );
}

void WritePrivateProfileColor( LPCSTR lpAppName, LPCSTR lpKeyName, Color flValue, LPCSTR lpFileName )
{
	std::string colorstring;
	colorstring += "r";
	colorstring += std::to_string( flValue.r( ) );
	colorstring += ",g";
	colorstring += std::to_string( flValue.g( ) );
	colorstring += ",b";
	colorstring += std::to_string( flValue.b( ) );
	WritePrivateProfileStringA( lpAppName, lpKeyName, colorstring.c_str( ), lpFileName );
}

// =======================================================================================================================

void CConfig::SetModule( HMODULE hModule )
{
	m_hModule = hModule;
}

void CConfig::Load( void )
{
	char szPath[ MAX_PATH ];

	GetModuleFileNameA( m_hModule, szPath, MAX_PATH );

	std::string path( szPath );
	path = path.substr( 0, path.find_last_of( /*\\*/XorStr<0x20,2,0xC7B7F129>("\x7C"+0xC7B7F129).s ) + 1 );
	path.append( /*config.cfg*/XorStr<0x53,11,0x13CC1293>("\x30\x3B\x3B\x30\x3E\x3F\x77\x39\x3D\x3B"+0x13CC1293).s );

	g_CVars.Aimbot.Active = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, 0, path.c_str( ) );
	g_CVars.Aimbot.AutoShoot = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AutoShoot*/XorStr<0x11,10,0xA8DBBE49>("\x50\x67\x67\x7B\x46\x7E\x78\x77\x6D"+0xA8DBBE49).s, 0, path.c_str( ) );
	g_CVars.Aimbot.AutoWall = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AutoWall*/XorStr<0xEF,9,0x87A95EA9>("\xAE\x85\x85\x9D\xA4\x95\x99\x9A"+0x87A95EA9).s, 0, path.c_str( ) );
	g_CVars.Aimbot.MultiSpot = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*MultiSpot*/XorStr<0xD1,10,0x86EC0E0A>("\x9C\xA7\xBF\xA0\xBC\x85\xA7\xB7\xAD"+0x86EC0E0A).s, 0, path.c_str( ) );
	g_CVars.Aimbot.HitScan = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*HitScan*/XorStr<0xCB,8,0xFC340577>("\x83\xA5\xB9\x9D\xAC\xB1\xBF"+0xFC340577).s, 0, path.c_str( ) );
	g_CVars.Aimbot.FriendlyFire = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*FriendlyFire*/XorStr<0xFC,13,0x954C6400>("\xBA\x8F\x97\x9A\x6E\x65\x6E\x7A\x42\x6C\x74\x62"+0x954C6400).s, 0, path.c_str( ) );
	g_CVars.Aimbot.TargetSelection = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*TargetSelection*/XorStr<0xC3,16,0x9E78006D>("\x97\xA5\xB7\xA1\xA2\xBC\x9A\xAF\xA7\xA9\xAE\xBA\xA6\xBF\xBF"+0x9E78006D).s, 0, path.c_str( ) );
	g_CVars.Aimbot.Hitbox = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*Hitbox*/XorStr<0x61,7,0xE7859F64>("\x29\x0B\x17\x06\x0A\x1E"+0xE7859F64).s, 0, path.c_str( ) );
	g_CVars.Aimbot.HitboxMode = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*HitboxMode*/XorStr<0xDB,11,0xBA9B04D1>("\x93\xB5\xA9\xBC\xB0\x98\xAC\x8D\x87\x81"+0xBA9B04D1).s, 0, path.c_str( ) );
	g_CVars.Aimbot.Silent = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*Silent*/XorStr<0xE1,7,0xA335B50B>("\xB2\x8B\x8F\x81\x8B\x92"+0xA335B50B).s, 0, path.c_str( ) );
	g_CVars.Aimbot.PerfectSilent = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*PerfectSilent*/XorStr<0xEC,14,0xBB750D0C>("\xBC\x88\x9C\x89\x95\x92\x86\xA0\x9D\x99\x93\x99\x8C"+0xBB750D0C).s, 0, path.c_str( ) );
	g_CVars.Aimbot.AntiSMAC = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AntiSMAC*/XorStr<0x07,9,0xDB906D0E>("\x46\x66\x7D\x63\x58\x41\x4C\x4D"+0xDB906D0E).s, 0, path.c_str( ) );
	g_CVars.Aimbot.BodyAWP = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*BodyAWP*/XorStr<0xCA,8,0x15077618>("\x88\xA4\xA8\xB4\x8F\x98\x80"+0x15077618).s, 0, path.c_str( ) );
	g_CVars.Aimbot.PointScale = GetPrivateProfileFloat( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*PointScale*/XorStr<0xBE,11,0x1EFB65EC>("\xEE\xD0\xA9\xAF\xB6\x90\xA7\xA4\xAA\xA2"+0x1EFB65EC).s, 0, path.c_str( ) );
	g_CVars.Aimbot.SnapLimiter = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*SnapLimiter*/XorStr<0xCD,12,0xE92FD079>("\x9E\xA0\xAE\xA0\x9D\xBB\xBE\xBD\xA1\xB3\xA5"+0xE92FD079).s, 0, path.c_str( ) );
	g_CVars.Aimbot.AngleLimit = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AngleLimit*/XorStr<0x55,11,0x2BCB8202>("\x14\x38\x30\x34\x3C\x16\x32\x31\x34\x2A"+0x2BCB8202).s, 0, path.c_str( ) );
	g_CVars.Aimbot.AngleLimitTens = GetPrivateProfileFloat( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AngleLimitTens*/XorStr<0x4F,15,0x42DB868E>("\x0E\x3E\x36\x3E\x36\x18\x3C\x3B\x3E\x2C\x0D\x3F\x35\x2F"+0x42DB868E).s, 0, path.c_str( ) );
	g_CVars.Aimbot.MinDamage = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*MinDamage*/XorStr<0x43,10,0xD1CF37C2>("\x0E\x2D\x2B\x02\x26\x25\x28\x2D\x2E"+0xD1CF37C2).s, 0, path.c_str( ) );
	g_CVars.Aimbot.Key = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*Key*/XorStr<0x19,4,0xBAF51996>("\x52\x7F\x62"+0xBAF51996).s, 0, path.c_str( ) );

	g_CVars.Aimbot.Interpolation.LagPrediction = GetPrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*LagPrediction*/XorStr<0x0C,14,0x8FC405E0>("\x40\x6C\x69\x5F\x62\x74\x76\x7A\x77\x61\x7F\x78\x76"+0x8FC405E0).s, 0, path.c_str( ) );

	g_CVars.Aimbot.Resolver.Active = GetPrivateProfileInteger( /*Resolver*/XorStr<0xC1,9,0xE5DCA663>("\x93\xA7\xB0\xAB\xA9\xB0\xA2\xBA"+0xE5DCA663).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, 0, path.c_str( ) );
	g_CVars.Aimbot.Resolver.Smart = GetPrivateProfileInteger( /*Resolver*/XorStr<0xC1,9,0xE5DCA663>("\x93\xA7\xB0\xAB\xA9\xB0\xA2\xBA"+0xE5DCA663).s, /*Smart*/XorStr<0x1B,6,0x3199AD52>("\x48\x71\x7C\x6C\x6B"+0x3199AD52).s, 0, path.c_str( ) );
	g_CVars.Aimbot.Resolver.Mode = GetPrivateProfileInteger( /*Resolver*/XorStr<0xC1,9,0xE5DCA663>("\x93\xA7\xB0\xAB\xA9\xB0\xA2\xBA"+0xE5DCA663).s, /*Mode*/XorStr<0xA1,5,0x038D62E9>("\xEC\xCD\xC7\xC1"+0x038D62E9).s, 0, path.c_str( ) );
	g_CVars.Aimbot.Resolver.Type = GetPrivateProfileInteger( /*Resolver*/XorStr<0xC1,9,0xE5DCA663>("\x93\xA7\xB0\xAB\xA9\xB0\xA2\xBA"+0xE5DCA663).s, /*Type*/XorStr<0x33,5,0x7A74F612>("\x67\x4D\x45\x53"+0x7A74F612).s, 0, path.c_str( ) );

	g_CVars.Triggerbot.Active = GetPrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, 0, path.c_str( ) );
	g_CVars.Triggerbot.Seed = GetPrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Seed*/XorStr<0x50,5,0x5388F9B1>("\x03\x34\x37\x37"+0x5388F9B1).s, 0, path.c_str( ) );
	g_CVars.Triggerbot.Strength = GetPrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Strength*/XorStr<0x4A,9,0x26680ABC>("\x19\x3F\x3E\x28\x20\x28\x24\x39"+0x26680ABC).s, 0, path.c_str( ) );
	g_CVars.Triggerbot.Key = GetPrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Key*/XorStr<0x19,4,0xBAF51996>("\x52\x7F\x62"+0xBAF51996).s, 0, path.c_str( ) );
	g_CVars.Triggerbot.Hitbox = GetPrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Hitbox*/XorStr<0x61,7,0xE7859F64>("\x29\x0B\x17\x06\x0A\x1E"+0xE7859F64).s, 0, path.c_str( ) );
	g_CVars.Triggerbot.Spread = GetPrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Spread*/XorStr<0x0E,7,0x101D52DD>("\x5D\x7F\x62\x74\x73\x77"+0x101D52DD).s, 0, path.c_str( ) );
	g_CVars.Triggerbot.Recoil = GetPrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Recoil*/XorStr<0xB0,7,0x998D4C43>("\xE2\xD4\xD1\xDC\xDD\xD9"+0x998D4C43).s, 0, path.c_str( ) );

	g_CVars.Accuracy.ForceSeed = GetPrivateProfileInteger( /*Accuracy*/XorStr<0xAF,9,0x175251A2>("\xEE\xD3\xD2\xC7\xC1\xD5\xD6\xCF"+0x175251A2).s, /*ForceSeed*/XorStr<0x17,10,0xB103C520>("\x51\x77\x6B\x79\x7E\x4F\x78\x7B\x7B"+0xB103C520).s, 0, path.c_str( ) );
	g_CVars.Accuracy.PerfectAccuracy = GetPrivateProfileInteger( /*Accuracy*/XorStr<0xAF,9,0x175251A2>("\xEE\xD3\xD2\xC7\xC1\xD5\xD6\xCF"+0x175251A2).s, /*PerfectAccuracy*/XorStr<0x62,16,0xCAB6BBCD>("\x32\x06\x16\x03\x03\x04\x1C\x28\x09\x08\x19\x1F\x0F\x0C\x09"+0xCAB6BBCD).s, 0, path.c_str( ) );
	g_CVars.Accuracy.NoSpreadMode = GetPrivateProfileInteger( /*Accuracy*/XorStr<0xAF,9,0x175251A2>("\xEE\xD3\xD2\xC7\xC1\xD5\xD6\xCF"+0x175251A2).s, /*NoSpreadMode*/XorStr<0x89,13,0xABE30353>("\xC7\xE5\xD8\xFC\xFF\xEB\xEE\xF4\xDC\xFD\xF7\xF1"+0xABE30353).s, 1, path.c_str( ) );

	g_CVars.Visuals.ESP.Box = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Box", 0, path.c_str( ) );
	g_CVars.Visuals.ESP.Name = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Name", 0, path.c_str( ) );
	g_CVars.Visuals.ESP.Health = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Health", 0, path.c_str( ) );
	g_CVars.Visuals.ESP.Weapon = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Weapon", 0, path.c_str( ) );
	g_CVars.Visuals.ESP.Bone = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Bone", 0, path.c_str( ) );
	g_CVars.Visuals.ESP.AimSpot = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "AimSpot", 0, path.c_str( ) );
	g_CVars.Visuals.ESP.Hit = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Hit", 0, path.c_str( ) );
	g_CVars.Visuals.ESP.Ground = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Ground", 0, path.c_str( ) );
	g_CVars.Visuals.ESP.EnemyOnly = GetPrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "EnemyOnly", 0, path.c_str( ) );

	g_CVars.Visuals.Chams.Active = GetPrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, 0, path.c_str( ) );
	g_CVars.Visuals.Chams.Weapons = GetPrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "Weapons", 0, path.c_str( ) );
	g_CVars.Visuals.Chams.Shadows = GetPrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "Shadows", 0, path.c_str( ) );
	g_CVars.Visuals.Chams.Outline = GetPrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "Outline", 0, path.c_str( ) );
	g_CVars.Visuals.Chams.HandsOutline = GetPrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "HandsOutline", 0, path.c_str( ) );
	g_CVars.Visuals.Chams.EnemyOnly = GetPrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "EnemyOnly", 0, path.c_str( ) );

	g_CVars.Visuals.Crosshair.Type = GetPrivateProfileInteger( /*Crosshair*/XorStr<0x43,10,0x4B4B568D>("\x00\x36\x2A\x35\x34\x20\x28\x23\x39"+0x4B4B568D).s, /*Type*/XorStr<0x33,5,0x7A74F612>("\x67\x4D\x45\x53"+0x7A74F612).s, 0, path.c_str( ) );
	g_CVars.Visuals.Crosshair.Dynamic = GetPrivateProfileInteger( /*Crosshair*/XorStr<0x43,10,0x4B4B568D>("\x00\x36\x2A\x35\x34\x20\x28\x23\x39"+0x4B4B568D).s, "Dynamic", 0, path.c_str( ) );

	g_CVars.Visuals.ASUS = GetPrivateProfileFloat( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "ASUS", 0, path.c_str( ) );
	g_CVars.Visuals.Radar = GetPrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "Radar", 0, path.c_str( ) );
	g_CVars.Visuals.NoSky = GetPrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoSky", 0, path.c_str( ) );
	g_CVars.Visuals.NoHands = GetPrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoHands", 0, path.c_str( ) );
	g_CVars.Visuals.NoSmoke = GetPrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoSmoke", 0, path.c_str( ) );
	g_CVars.Visuals.NoFlash = GetPrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoFlash", 0, path.c_str( ) );
	g_CVars.Visuals.NoVisualRecoil = GetPrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoVisualRecoil", 0, path.c_str( ) );

	g_CVars.Miscellaneous.AntiAim.Active = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.Pitch = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "Pitch", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.Yaw = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "Yaw", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.Variation = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "Variation", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.WallDetectionMode = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "WallDetectionMode", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.Static = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "Static", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.WallDetection = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "WallDetection", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.AtTargets = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "AtTargets", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.DuckInAir = GetPrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "DuckInAir", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.RealValue = GetPrivateProfileFloat( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "RealValue", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.FakeValue = GetPrivateProfileFloat( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "FakeValue", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AntiAim.TurnOff = GetPrivateProfileFloat( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "EnemyCheck", 0, path.c_str( ) );

	g_CVars.Miscellaneous.Fakelag.Active = GetPrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, 0, path.c_str( ) );
	g_CVars.Miscellaneous.Fakelag.Mode = GetPrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, /*Mode*/XorStr<0xA1,5,0x038D62E9>("\xEC\xCD\xC7\xC1"+0x038D62E9).s, 0, path.c_str( ) );
	g_CVars.Miscellaneous.Fakelag.Value = GetPrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, "Value", 0, path.c_str( ) );
	g_CVars.Miscellaneous.Fakelag.InAttack = GetPrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, "InAttack", 0, path.c_str( ) );
	g_CVars.Miscellaneous.Fakelag.AirOnly = GetPrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, "AirOnly", 0, path.c_str( ) );

	g_CVars.Miscellaneous.BunnyHop = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "BunnyHop", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AutoStrafe = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "AutoStrafe", 0, path.c_str( ) );
	g_CVars.Miscellaneous.CircleStrafe = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "CircleStrafe", 0, path.c_str( ) );
	g_CVars.Miscellaneous.EdgeJump = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "EdgeJump", 0, path.c_str( ) );
	g_CVars.Miscellaneous.Speedhack = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Speedhack", 0, path.c_str( ) );
	g_CVars.Miscellaneous.SpeedhackValue = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "SpeedhackValue", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AutoKnife = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "AutoKnife", 0, path.c_str( ) );
	g_CVars.Miscellaneous.RoundSay = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "RoundSay", 0, path.c_str( ) );
	g_CVars.Miscellaneous.CheatsBypass = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "CheatsBypass", 0, path.c_str( ) );
	g_CVars.Miscellaneous.AirStuck = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "AirStuck", 0, path.c_str( ) );

	g_CVars.Menu.x = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Menu.x", 0, path.c_str( ) );
	g_CVars.Menu.y = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Menu.y", 0, path.c_str( ) );

	g_CVars.Radar.x = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Radar.x", 0, path.c_str( ) );
	g_CVars.Radar.y = GetPrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Radar.y", 0, path.c_str( ) );

	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "ESP.TT", g_CVars.ColorSelector.ESP.TT, path.c_str( ) );
	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "ESP.CT", g_CVars.ColorSelector.ESP.CT, path.c_str( ) );
	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "ESP.Wpn", g_CVars.ColorSelector.ESP.Wpn, path.c_str( ) );

	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.CTInvis", g_CVars.ColorSelector.Chams.CTInvis, path.c_str( ) );
	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.CTVis", g_CVars.ColorSelector.Chams.CTVis, path.c_str( ) );
	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.CTOutline", g_CVars.ColorSelector.Chams.CTOutline, path.c_str( ) );

	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.TTInvis", g_CVars.ColorSelector.Chams.TTInvis, path.c_str( ) );
	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.TTVis", g_CVars.ColorSelector.Chams.TTVis, path.c_str( ) );
	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.TTOutline", g_CVars.ColorSelector.Chams.TTOutline, path.c_str( ) );

	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.WpnInvis", g_CVars.ColorSelector.Chams.WpnInvis, path.c_str( ) );
	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.WpnVis", g_CVars.ColorSelector.Chams.WpnVis, path.c_str( ) );
	GetPrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.WpnOutline", g_CVars.ColorSelector.Chams.WpnOutline, path.c_str( ) );
}

void CConfig::Save( void )
{
	char szPath[MAX_PATH];

	GetModuleFileNameA( m_hModule, szPath, MAX_PATH );

	std::string path( szPath );
	path = path.substr( 0, path.find_last_of( /*\\*/XorStr<0xCF,2,0x269221ED>("\x93"+0x269221ED).s ) + 1 );
	path.append( /*config.cfg*/XorStr<0xB0,11,0x15CDA4C2>("\xD3\xDE\xDC\xD5\xDD\xD2\x98\xD4\xDE\xDE"+0x15CDA4C2).s );

	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, g_CVars.Aimbot.Active, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AutoShoot*/XorStr<0x11,10,0xA8DBBE49>("\x50\x67\x67\x7B\x46\x7E\x78\x77\x6D"+0xA8DBBE49).s, g_CVars.Aimbot.AutoShoot, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AutoWall*/XorStr<0xEF,9,0x87A95EA9>("\xAE\x85\x85\x9D\xA4\x95\x99\x9A"+0x87A95EA9).s, g_CVars.Aimbot.AutoWall, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*MultiSpot*/XorStr<0xD1,10,0x86EC0E0A>("\x9C\xA7\xBF\xA0\xBC\x85\xA7\xB7\xAD"+0x86EC0E0A).s, g_CVars.Aimbot.MultiSpot, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*HitScan*/XorStr<0xCB,8,0xFC340577>("\x83\xA5\xB9\x9D\xAC\xB1\xBF"+0xFC340577).s, g_CVars.Aimbot.HitScan, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*FriendlyFire*/XorStr<0xFC,13,0x954C6400>("\xBA\x8F\x97\x9A\x6E\x65\x6E\x7A\x42\x6C\x74\x62"+0x954C6400).s, g_CVars.Aimbot.FriendlyFire, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*TargetSelection*/XorStr<0xC3,16,0x9E78006D>("\x97\xA5\xB7\xA1\xA2\xBC\x9A\xAF\xA7\xA9\xAE\xBA\xA6\xBF\xBF"+0x9E78006D).s, g_CVars.Aimbot.TargetSelection, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*Hitbox*/XorStr<0x61,7,0xE7859F64>("\x29\x0B\x17\x06\x0A\x1E"+0xE7859F64).s, g_CVars.Aimbot.Hitbox, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*HitboxMode*/XorStr<0xDB,11,0xBA9B04D1>("\x93\xB5\xA9\xBC\xB0\x98\xAC\x8D\x87\x81"+0xBA9B04D1).s, g_CVars.Aimbot.HitboxMode, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*Silent*/XorStr<0xE1,7,0xA335B50B>("\xB2\x8B\x8F\x81\x8B\x92"+0xA335B50B).s, g_CVars.Aimbot.Silent, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*PerfectSilent*/XorStr<0xEC,14,0xBB750D0C>("\xBC\x88\x9C\x89\x95\x92\x86\xA0\x9D\x99\x93\x99\x8C"+0xBB750D0C).s, g_CVars.Aimbot.PerfectSilent, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AntiSMAC*/XorStr<0x07,9,0xDB906D0E>("\x46\x66\x7D\x63\x58\x41\x4C\x4D"+0xDB906D0E).s, g_CVars.Aimbot.AntiSMAC, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*BodyAWP*/XorStr<0xCA,8,0x15077618>("\x88\xA4\xA8\xB4\x8F\x98\x80"+0x15077618).s, g_CVars.Aimbot.BodyAWP, path.c_str( ) );
	WritePrivateProfileFloat( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*PointScale*/XorStr<0xBE,11,0x1EFB65EC>("\xEE\xD0\xA9\xAF\xB6\x90\xA7\xA4\xAA\xA2"+0x1EFB65EC).s, g_CVars.Aimbot.PointScale, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*SnapLimiter*/XorStr<0xCD,12,0xE92FD079>("\x9E\xA0\xAE\xA0\x9D\xBB\xBE\xBD\xA1\xB3\xA5"+0xE92FD079).s, g_CVars.Aimbot.SnapLimiter, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AngleLimit*/XorStr<0x55,11,0x2BCB8202>("\x14\x38\x30\x34\x3C\x16\x32\x31\x34\x2A"+0x2BCB8202).s, g_CVars.Aimbot.AngleLimit, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*AngleLimitTens*/XorStr<0x4F,15,0x42DB868E>("\x0E\x3E\x36\x3E\x36\x18\x3C\x3B\x3E\x2C\x0D\x3F\x35\x2F"+0x42DB868E).s, g_CVars.Aimbot.AngleLimitTens, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*MinDamage*/XorStr<0x43,10,0xD1CF37C2>("\x0E\x2D\x2B\x02\x26\x25\x28\x2D\x2E"+0xD1CF37C2).s, g_CVars.Aimbot.MinDamage, path.c_str( ) );
	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*Key*/XorStr<0x19,4,0xBAF51996>("\x52\x7F\x62"+0xBAF51996).s, g_CVars.Aimbot.Key, path.c_str( ) );

	WritePrivateProfileInteger( /*Aimbot*/XorStr<0x06,7,0x1D2CE0D1>("\x47\x6E\x65\x6B\x65\x7F"+0x1D2CE0D1).s, /*LagPrediction*/XorStr<0x0C,14,0x8FC405E0>("\x40\x6C\x69\x5F\x62\x74\x76\x7A\x77\x61\x7F\x78\x76"+0x8FC405E0).s, g_CVars.Aimbot.Interpolation.LagPrediction, path.c_str( ) );

	WritePrivateProfileInteger( /*Resolver*/XorStr<0xC1,9,0xE5DCA663>("\x93\xA7\xB0\xAB\xA9\xB0\xA2\xBA"+0xE5DCA663).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, g_CVars.Aimbot.Resolver.Active, path.c_str( ) );
	WritePrivateProfileInteger( /*Resolver*/XorStr<0xC1,9,0xE5DCA663>("\x93\xA7\xB0\xAB\xA9\xB0\xA2\xBA"+0xE5DCA663).s, /*Smart*/XorStr<0x1B,6,0x3199AD52>("\x48\x71\x7C\x6C\x6B"+0x3199AD52).s, g_CVars.Aimbot.Resolver.Smart, path.c_str( ) );
	WritePrivateProfileInteger( /*Resolver*/XorStr<0xC1,9,0xE5DCA663>("\x93\xA7\xB0\xAB\xA9\xB0\xA2\xBA"+0xE5DCA663).s, /*Mode*/XorStr<0xA1,5,0x038D62E9>("\xEC\xCD\xC7\xC1"+0x038D62E9).s, g_CVars.Aimbot.Resolver.Mode, path.c_str( ) );
	WritePrivateProfileInteger( /*Resolver*/XorStr<0xC1,9,0xE5DCA663>("\x93\xA7\xB0\xAB\xA9\xB0\xA2\xBA"+0xE5DCA663).s, /*Type*/XorStr<0x33,5,0x7A74F612>("\x67\x4D\x45\x53"+0x7A74F612).s, g_CVars.Aimbot.Resolver.Type, path.c_str( ) );

	WritePrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, g_CVars.Triggerbot.Active, path.c_str( ) );
	WritePrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Seed*/XorStr<0x50,5,0x5388F9B1>("\x03\x34\x37\x37"+0x5388F9B1).s, g_CVars.Triggerbot.Seed, path.c_str( ) );
	WritePrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Strength*/XorStr<0x4A,9,0x26680ABC>("\x19\x3F\x3E\x28\x20\x28\x24\x39"+0x26680ABC).s, g_CVars.Triggerbot.Strength, path.c_str( ) );
	WritePrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Key*/XorStr<0x19,4,0xBAF51996>("\x52\x7F\x62"+0xBAF51996).s, g_CVars.Triggerbot.Key, path.c_str( ) );
	WritePrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Hitbox*/XorStr<0x61,7,0xE7859F64>("\x29\x0B\x17\x06\x0A\x1E"+0xE7859F64).s, g_CVars.Triggerbot.Hitbox, path.c_str( ) );
	WritePrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Recoil*/XorStr<0xB0,7,0x998D4C43>("\xE2\xD4\xD1\xDC\xDD\xD9"+0x998D4C43).s, g_CVars.Triggerbot.Recoil, path.c_str( ) );
	WritePrivateProfileInteger( /*Triggerbot*/XorStr<0x57,11,0x2DB2B1FA>("\x03\x2A\x30\x3D\x3C\x39\x2F\x3C\x30\x14"+0x2DB2B1FA).s, /*Spread*/XorStr<0x0E,7,0x101D52DD>("\x5D\x7F\x62\x74\x73\x77"+0x101D52DD).s, g_CVars.Triggerbot.Spread, path.c_str( ) );

	WritePrivateProfileInteger( /*Accuracy*/XorStr<0xAF,9,0x175251A2>("\xEE\xD3\xD2\xC7\xC1\xD5\xD6\xCF"+0x175251A2).s, /*ForceSeed*/XorStr<0x17,10,0xB103C520>("\x51\x77\x6B\x79\x7E\x4F\x78\x7B\x7B"+0xB103C520).s, g_CVars.Accuracy.ForceSeed, path.c_str( ) );
	WritePrivateProfileInteger( /*Accuracy*/XorStr<0xAF,9,0x175251A2>("\xEE\xD3\xD2\xC7\xC1\xD5\xD6\xCF"+0x175251A2).s, /*PerfectAccuracy*/XorStr<0x62,16,0xCAB6BBCD>("\x32\x06\x16\x03\x03\x04\x1C\x28\x09\x08\x19\x1F\x0F\x0C\x09"+0xCAB6BBCD).s, g_CVars.Accuracy.PerfectAccuracy, path.c_str( ) );
	WritePrivateProfileInteger( /*Accuracy*/XorStr<0xAF,9,0x175251A2>("\xEE\xD3\xD2\xC7\xC1\xD5\xD6\xCF"+0x175251A2).s, /*NoSpreadMode*/XorStr<0x89,13,0xABE30353>("\xC7\xE5\xD8\xFC\xFF\xEB\xEE\xF4\xDC\xFD\xF7\xF1"+0xABE30353).s, g_CVars.Accuracy.NoSpreadMode, path.c_str( ) );

	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Box", g_CVars.Visuals.ESP.Box, path.c_str( ) );
	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Name", g_CVars.Visuals.ESP.Name, path.c_str( ) );
	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Health", g_CVars.Visuals.ESP.Health, path.c_str( ) );
	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Weapon", g_CVars.Visuals.ESP.Weapon, path.c_str( ) );
	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Bone", g_CVars.Visuals.ESP.Bone, path.c_str( ) );
	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "AimSpot", g_CVars.Visuals.ESP.AimSpot, path.c_str( ) );
	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Hit", g_CVars.Visuals.ESP.Hit, path.c_str( ) );
	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "Ground", g_CVars.Visuals.ESP.Ground, path.c_str( ) );
	WritePrivateProfileInteger( /*ESP*/XorStr<0x4F,4,0x16AF489D>("\x0A\x03\x01"+0x16AF489D).s, "EnemyOnly", g_CVars.Visuals.ESP.EnemyOnly, path.c_str( ) );

	WritePrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, g_CVars.Visuals.Chams.Active, path.c_str( ) );
	WritePrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "Weapons", g_CVars.Visuals.Chams.Weapons, path.c_str( ) );
	WritePrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "Shadows", g_CVars.Visuals.Chams.Shadows, path.c_str( ) );
	WritePrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "Outline", g_CVars.Visuals.Chams.Outline, path.c_str( ) );
	WritePrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "HandsOutline", g_CVars.Visuals.Chams.HandsOutline, path.c_str( ) );
	WritePrivateProfileInteger( /*Chams*/XorStr<0xEC,6,0xBE77CCE8>("\xAF\x85\x8F\x82\x83"+0xBE77CCE8).s, "EnemyOnly", g_CVars.Visuals.Chams.EnemyOnly, path.c_str( ) );

	WritePrivateProfileInteger( /*Crosshair*/XorStr<0x43,10,0x4B4B568D>("\x00\x36\x2A\x35\x34\x20\x28\x23\x39"+0x4B4B568D).s, /*Type*/XorStr<0x33,5,0x7A74F612>("\x67\x4D\x45\x53"+0x7A74F612).s, g_CVars.Visuals.Crosshair.Type, path.c_str( ) );
	WritePrivateProfileInteger( /*Crosshair*/XorStr<0x43,10,0x4B4B568D>("\x00\x36\x2A\x35\x34\x20\x28\x23\x39"+0x4B4B568D).s, "Dynamic", g_CVars.Visuals.Crosshair.Dynamic, path.c_str( ) );

	WritePrivateProfileFloat( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "ASUS", g_CVars.Visuals.ASUS, path.c_str( ) );
	WritePrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "Radar", g_CVars.Visuals.Radar, path.c_str( ) );
	WritePrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoSky", g_CVars.Visuals.NoSky, path.c_str( ) );
	WritePrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoHands", g_CVars.Visuals.NoHands, path.c_str( ) );
	WritePrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoSmoke", g_CVars.Visuals.NoSmoke, path.c_str( ) );
	WritePrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoFlash", g_CVars.Visuals.NoFlash, path.c_str( ) );
	WritePrivateProfileInteger( /*Visuals*/XorStr<0xE2,8,0xAB24030E>("\xB4\x8A\x97\x90\x87\x8B\x9B"+0xAB24030E).s, "NoVisualRecoil", g_CVars.Visuals.NoVisualRecoil, path.c_str( ) );

	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, g_CVars.Miscellaneous.AntiAim.Active, path.c_str( ) );
	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "Pitch", g_CVars.Miscellaneous.AntiAim.Pitch, path.c_str( ) );
	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "Yaw", g_CVars.Miscellaneous.AntiAim.Yaw, path.c_str( ) );
	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "Variation", g_CVars.Miscellaneous.AntiAim.Variation, path.c_str( ) );
	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "Static", g_CVars.Miscellaneous.AntiAim.Static, path.c_str( ) );
	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "WallDetection", g_CVars.Miscellaneous.AntiAim.WallDetection, path.c_str( ) );
	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "WallDetectionMode", g_CVars.Miscellaneous.AntiAim.WallDetectionMode, path.c_str( ) );
	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "AtTargets", g_CVars.Miscellaneous.AntiAim.AtTargets, path.c_str( ) );
	WritePrivateProfileInteger( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "DuckInAir", g_CVars.Miscellaneous.AntiAim.DuckInAir, path.c_str( ) );
	WritePrivateProfileFloat( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "RealValue", g_CVars.Miscellaneous.AntiAim.RealValue, path.c_str( ) );
	WritePrivateProfileFloat( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "FakeValue", g_CVars.Miscellaneous.AntiAim.FakeValue, path.c_str( ) );
	WritePrivateProfileFloat( /*AntiAim*/XorStr<0x67,8,0x84564416>("\x26\x06\x1D\x03\x2A\x05\x00"+0x84564416).s, "EnemyCheck", g_CVars.Miscellaneous.AntiAim.TurnOff, path.c_str( ) );

	WritePrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, /*Active*/XorStr<0x05,7,0x27ACD844>("\x44\x65\x73\x61\x7F\x6F"+0x27ACD844).s, g_CVars.Miscellaneous.Fakelag.Active, path.c_str( ) );
	WritePrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, /*Mode*/XorStr<0xA1,5,0x038D62E9>("\xEC\xCD\xC7\xC1"+0x038D62E9).s, g_CVars.Miscellaneous.Fakelag.Mode, path.c_str( ) );
	WritePrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, "Value", g_CVars.Miscellaneous.Fakelag.Value, path.c_str( ) );
	WritePrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, "InAttack", g_CVars.Miscellaneous.Fakelag.InAttack, path.c_str( ) );
	WritePrivateProfileInteger( /*Fakelag*/XorStr<0x0D,8,0xB5531447>("\x4B\x6F\x64\x75\x7D\x73\x74"+0xB5531447).s, "AirOnly", g_CVars.Miscellaneous.Fakelag.AirOnly, path.c_str( ) );

	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "BunnyHop", g_CVars.Miscellaneous.BunnyHop, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "AutoStrafe", g_CVars.Miscellaneous.AutoStrafe, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "CircleStrafe", g_CVars.Miscellaneous.CircleStrafe, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "EdgeJump", g_CVars.Miscellaneous.EdgeJump, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Speedhack", g_CVars.Miscellaneous.Speedhack, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "SpeedhackValue", g_CVars.Miscellaneous.SpeedhackValue, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "AutoKnife", g_CVars.Miscellaneous.AutoKnife, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "RoundSay", g_CVars.Miscellaneous.RoundSay, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "CheatsBypass", g_CVars.Miscellaneous.CheatsBypass, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "AirStuck", g_CVars.Miscellaneous.AirStuck, path.c_str( ) );

	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Menu.x", g_CVars.Menu.x, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Menu.y", g_CVars.Menu.y, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Radar.x", g_CVars.Radar.x, path.c_str( ) );
	WritePrivateProfileInteger( /*Miscellaneous*/XorStr<0x45,14,0x11CF7276>("\x08\x2F\x34\x2B\x2C\x26\x27\x2D\x23\x2B\x20\x25\x22"+0x11CF7276).s, "Radar.y", g_CVars.Radar.y, path.c_str( ) );

	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "ESP.TT", g_CVars.ColorSelector.ESP.TT, path.c_str( ) );
	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "ESP.CT", g_CVars.ColorSelector.ESP.CT, path.c_str( ) );
	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "ESP.Wpn", g_CVars.ColorSelector.ESP.Wpn, path.c_str( ) );

	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.CTInvis", g_CVars.ColorSelector.Chams.CTInvis, path.c_str( ) );
	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.CTVis", g_CVars.ColorSelector.Chams.CTVis, path.c_str( ) );
	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.CTOutline", g_CVars.ColorSelector.Chams.CTOutline, path.c_str( ) );

	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.TTInvis", g_CVars.ColorSelector.Chams.TTInvis, path.c_str( ) );
	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.TTVis", g_CVars.ColorSelector.Chams.TTVis, path.c_str( ) );
	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.TTOutline", g_CVars.ColorSelector.Chams.TTOutline, path.c_str( ) );

	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.WpnInvis", g_CVars.ColorSelector.Chams.WpnInvis, path.c_str( ) );
	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.WpnVis", g_CVars.ColorSelector.Chams.WpnVis, path.c_str( ) );
	WritePrivateProfileColor( /*Colors*/XorStr<0x02,7,0x76D4C00A>("\x41\x6C\x68\x6A\x74\x74"+0x76D4C00A).s, "Chams.WpnOutline", g_CVars.ColorSelector.Chams.WpnOutline, path.c_str( ) );
}