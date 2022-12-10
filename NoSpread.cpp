#include "Main.h"

NoSpread g_NoSpread;

uintptr_t NoSpread::GetWeaponData( CSWeapon* Weapon )
{
	typedef uintptr_t ( __thiscall * GetCSWpnData_t )( void* thisptr );
	return ( ( GetCSWpnData_t )( ( uintptr_t ) BASE_CLIENT + 0x1E0D80 ) )( Weapon );
}

WeaponInfo NoSpread::GetWeaponInfo( CSWeapon* Weapon )
{
	WeaponInfo TempWeaponInfo;
	uintptr_t WeaponData = GetWeaponData( Weapon );

	if( WeaponData )
	{
		TempWeaponInfo.BulletType = *( int* )( WeaponData + 0x620 );
		TempWeaponInfo.ArmorRatio = *( float* )( WeaponData + 0x664 );		
		TempWeaponInfo.Penetration = *( int* )( WeaponData + 0x7DC );
		TempWeaponInfo.Damage = *( int* )( WeaponData + 0x7E0 );
		TempWeaponInfo.MaxRange = *( float* )( WeaponData + 0x7E4 );
		TempWeaponInfo.RangeModifier = *( float* )( WeaponData + 0x7E8 );
		TempWeaponInfo.BulletsPerShots = *( int* )( WeaponData + 0x7EC );
		TempWeaponInfo.CycleTime = *( float* )( WeaponData + 0x7D8 );
		TempWeaponInfo.AccuracyQuadratic = *( bool* )( WeaponData + 0x7F4 );
		TempWeaponInfo.AccuracyDivisor = *( float* )( WeaponData + 0x7F8 );
		TempWeaponInfo.AccuracyOffset = *( float* )( WeaponData + 0x7FC );
		TempWeaponInfo.MaxInaccuracy = *( float* )( WeaponData + 0x800 );
	}

	TempWeaponInfo.ID = Weapon->GetWeaponID( );
	TempWeaponInfo.Alias = Weapon->GetWeaponAlias( );

	if( TempWeaponInfo.ID == WEAPON_M4A1 )
	{
		if( Weapon->SpecialMode( ) ) TempWeaponInfo.RangeModifier = .95f;
	}

	if( TempWeaponInfo.ID == WEAPON_GLOCK )
	{
		if( Weapon->SpecialMode( ) )
		{
			if( Weapon->m_flGlock18Shoot( ) > 0.f )
			{
				TempWeaponInfo.Damage = 18;
				TempWeaponInfo.RangeModifier = .9f;
			}
		}
	}

	if( TempWeaponInfo.ID == WEAPON_USP )
	{
		if( Weapon->SpecialMode( ) ) TempWeaponInfo.Damage = 30;
	}

	DWORD dwGetBulletTypeParameters = 0x241CE4B0;

	__asm
	{
		LEA ECX, TempWeaponInfo.PenetrationRange;
	    PUSH ECX;
	    LEA EDX, TempWeaponInfo.PenetrationPower;
	    PUSH EDX;
	    PUSH TempWeaponInfo.BulletType;
	    CALL dwGetBulletTypeParameters;
	}

	return TempWeaponInfo;
}

float NoSpread::GetSpread( BasePlayer* LocalPlayer, int iGlock18ShotsFired )
{
	CSWeapon* Weapon = ( CSWeapon* ) LocalPlayer->GetActiveBaseCombatWeapon( );

	if ( !Weapon ) return 0.0f;
	
	float m_flSpread = 0;
	int m_fFlags = *( int* )( ( DWORD ) LocalPlayer + 0x2B4 ); // LocalPlayer->m_fFlags( );
	int m_iWeaponID = Weapon->GetWeaponID( );
	float m_flAccuracy = Weapon->m_flAccuracy( );
	float m_flGlock18Shoot = Weapon->m_flGlock18Shoot( );
	bool m_bSilencer_USP = *( bool* )( ( DWORD ) Weapon + 0x780 ); // Weapon->m_bSilencerOnUSP( );
	bool m_bSilencer_M4A1 = *( bool* )( ( DWORD ) Weapon + 0x780 ); // Weapon->m_bSilencerOnM4A1( );
	bool m_bBurstModeGlock = *( bool* )( ( DWORD ) Weapon + 0x778 ); // Weapon->m_bBurstModeGlock( );
	bool m_bBurstModeFamas = *( bool* )( ( DWORD ) Weapon + 0x778 ); // Weapon->m_bBurstModeFamas( );
	int m_iFOV = *( int* )( ( DWORD ) LocalPlayer + 0xD1C );
	vec_t m_iSpeed = LocalPlayer->GetAbsVelocity( ).Length2D( );

	switch ( m_iWeaponID )
	{
	case 27:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 140.0 )
				m_flSpread = m_flAccuracy * 0.02749999985098839;
			else
				m_flSpread = m_flAccuracy * 0.07000000029802322 + 0.03999999910593033;
		}
		else
		{
			m_flSpread = m_flAccuracy * 0.4000000059604645 + 0.03999999910593033;
		}
		break;

	case 8:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 140.0 )
				m_flSpread = m_flAccuracy * 0.02;
			else
				m_flSpread = m_flAccuracy * 0.07000000000000001 + 0.035;
		}
		else
		{
			m_flSpread = m_flAccuracy * 0.4 + 0.035;
		}
		break;

	case 17:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 140.0 )
			{
				if( m_iSpeed <= 10.0 )
				{
					if( m_fFlags & FL_DUCKING )
						m_flSpread = 0.0;
					else
						m_flSpread = 0.001000000047497451;
				}
				else
				{
					m_flSpread = 0.1000000014901161;
				}
			}
			else
			{
				m_flSpread = 0.25;
			}
		}
		else
		{
			m_flSpread = 0.8500000238418579;
		}
		if( m_iFOV == 90.0 )
			m_flSpread += 0.08;
		break;

	case 25:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 5.0 )
			{
				if( m_fFlags & FL_DUCKING )
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.115;
				else
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.13;
			}
			else
			{
				m_flSpread = ( 1.0 - m_flAccuracy ) * 0.25;
			}
		}
		else
		{
			m_flSpread = ( 1.0 - m_flAccuracy ) * 1.5;
		}
		break;

	case 10:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 5.0 )
			{
				if( m_fFlags & FL_DUCKING )
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.08;
				else
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.1;
			}
			else
			{
				m_flSpread = ( 1.0 - m_flAccuracy ) * 0.175;
			}
		}
		else
		{
			m_flSpread = ( 1.0 - m_flAccuracy ) * 1.3;
		}
		break;

	case 15:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 140.0 )
				m_flSpread = m_flAccuracy * 0.02;
			else
				m_flSpread = m_flAccuracy * 0.07000000000000001 + 0.03;
		}
		else
		{
			m_flSpread = m_flAccuracy * 0.3 + 0.03;
		}
		break;

	case 11:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 5.0 )
			{
				if( m_fFlags & FL_DUCKING )
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.075;
				else
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.15;
			}
			else
			{
				m_flSpread = ( 1.0 - m_flAccuracy ) * 0.255;
			}
		}
		else
		{
			m_flSpread = ( 1.0 - m_flAccuracy ) * 1.5;
		}
		break;

	case 23:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 5.0 )
			{
				if( m_fFlags & FL_DUCKING )
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.035;
				else
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.055;
			}
			else
			{
			  m_flSpread = 0.1500000059604645;
			}
		}
		else
		{
			m_flSpread = ( 1.0 - m_flAccuracy ) * 0.45;
		}
		if( m_iFOV == 90.0 )
			m_flSpread += 0.025;
		break;

	case 14:
		if ( m_fFlags & FL_ONGROUND )
		{
			if ( m_iSpeed <= 140.0 )
				m_flSpread = m_flAccuracy * 0.0375;
			else
				m_flSpread = m_flAccuracy * 0.07000000000000001 + 0.04;
		}
		else
		{
			m_flSpread = m_flAccuracy * 0.3 + 0.04;
		}
		break;

	case 2:
		if( m_bBurstModeGlock )
		{
			if( iGlock18ShotsFired )
				m_flSpread = 0.05000000074505806;
			if( 0.0 == m_flGlock18Shoot )
			{
				if( m_fFlags & FL_ONGROUND )
				{
					if( m_iSpeed <= 5.0 )
					{
						if( m_fFlags & FL_DUCKING )
							m_flSpread = ( 1.0 - m_flAccuracy ) * 0.0949999988079071;
						else
							m_flSpread = ( 1.0 - m_flAccuracy ) * 0.1850000023841858;
					}
					else
					{
						m_flSpread = ( 1.0 - m_flAccuracy ) * 0.300000011920929;
					}
				}
				else
				{
					m_flSpread = ( 1.0 - m_flAccuracy ) * 1.200000047683716;
				}
			}
		}
		else
		{
			if( m_fFlags & FL_ONGROUND )
			{
				if( m_iSpeed <= 5.0 )
				{
					if( m_fFlags & FL_DUCKING )
						m_flSpread = ( 1.0 - m_flAccuracy ) * 0.07500000298023224;
					else
						m_flSpread = ( 1.0 - m_flAccuracy ) * 0.1000000014901161;
				}
				else
				{
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.1650000065565109;
				}
			}
			else
			{
				m_flSpread = 1.0 - m_flAccuracy;
			}
		}
		break;

	case 19:
		if( m_fFlags & FL_ONGROUND )
		{
			if ( m_iSpeed <= 140.0 )
				m_flSpread = m_flAccuracy * 0.03;
			else
				m_flSpread = m_flAccuracy * 0.095 + 0.045;
		}
		else
		{
			m_flSpread = m_flAccuracy * 0.5 + 0.045;
		}
		break;

	case 21:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 140.0 )
			{
				if( m_bSilencer_M4A1 )
					m_flSpread = m_flAccuracy * 0.02500000037252903;
				else
					m_flSpread = m_flAccuracy * 0.01999999955296516;
			}
			else
			{
				m_flSpread = m_flAccuracy * 0.07000000029802322 + 0.03500000014901161;
			}
		}
		else
		{
			m_flSpread = m_flAccuracy * 0.4000000059604645 + 0.03500000014901161;
		}
		break;

	case 7:
		if( m_fFlags & FL_ONGROUND )
			m_flSpread = m_flAccuracy * 0.03;
		else
			m_flSpread = m_flAccuracy * 0.375;
		break;

	case 18:
		if( m_fFlags & FL_ONGROUND )
			m_flSpread = m_flAccuracy * 0.04;
		else
			m_flSpread = m_flAccuracy * 0.2;
		break;

	case 1:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 5.0 )
			{
				if( m_fFlags & FL_DUCKING )
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.075;
				else
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.15;
			}
			else
			{
				m_flSpread = ( 1.0 - m_flAccuracy ) * 0.255;
			}
		}
		else
		{
			m_flSpread = ( 1.0 - m_flAccuracy ) * 1.5;
		}
		break;

	case 29:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 170.0 )
				m_flSpread = m_flAccuracy * 0.045;
			else
				m_flSpread = m_flAccuracy * 0.115;
		}
		else
		{
			m_flSpread = m_flAccuracy * 0.3;
		}
	  break;

	case 3:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 170.0 )
			{
				if( m_fFlags & FL_DUCKING )
					m_flSpread = 0.0;
				else
					m_flSpread = 0.007000000216066837;
			}
			else
			{
				m_flSpread = 0.07500000298023224;
			}
		}
		else
		{
			m_flSpread = 0.2000000029802322;
		}
		if( m_iFOV == 90.0 )
			m_flSpread += 0.025;
		break;

	case 13:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 5.0 )
			{
				if( m_fFlags & FL_DUCKING )
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.04;
				else
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.05;
			}
			else
			{
				m_flSpread = 0.1500000059604645;
			}
		}
		else
		{
			m_flSpread = ( 1.0 - m_flAccuracy ) * 0.45;
		}
		if( m_iFOV == 90.0 )
			m_flSpread += 0.025;
		break;

	case 26:
		if( m_fFlags & FL_ONGROUND )
		{
			if( m_iSpeed <= 140.0 )
				m_flSpread = m_flAccuracy * 0.02;
			else
				m_flSpread = m_flAccuracy * 0.075 + 0.035;
		}
		else
		{
			m_flSpread = m_flAccuracy * 0.45 + 0.035;
		}
		break;

	case 22:
		if( m_fFlags & FL_ONGROUND )
			m_flSpread = m_flAccuracy * 0.03;
		else
			m_flSpread = m_flAccuracy * 0.25;
		break;

	case 12:
		if( m_fFlags & FL_ONGROUND )
			m_flSpread = m_flAccuracy * 0.04;
		else
			m_flSpread = m_flAccuracy * 0.24;
		break;

	case 16:
		if( m_bSilencer_USP )
		{
			if( m_fFlags & FL_ONGROUND )
			{
				if( m_iSpeed <= 5.0 )
				{
					if( m_fFlags & FL_DUCKING )
						m_flSpread = ( 1.0 - m_flAccuracy ) * 0.125;
					else
						m_flSpread = ( 1.0 - m_flAccuracy ) * 0.15;
				}
				else
				{
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.25;
				}
			}
			else
			{
				m_flSpread = ( 1.0 - m_flAccuracy ) * 1.3;
			}
		}
		else
		{
			if( m_fFlags & FL_ONGROUND )
			{
				if( m_iSpeed <= 5.0 )
				{
					if( m_fFlags & FL_DUCKING )
						m_flSpread = ( 1.0 - m_flAccuracy ) * 0.08;
					else
						m_flSpread = ( 1.0 - m_flAccuracy ) * 0.1;
				}
				else
				{
					m_flSpread = ( 1.0 - m_flAccuracy ) * 0.225;
				}
			}
			else
			{
				m_flSpread = ( 1.0 - m_flAccuracy ) * 1.2;
			}
		}
		break;

	default:
		m_flSpread = 0.0;
		break;

	}
	return m_flSpread;
}

void NoSpread::CoolNospreee( CUserCmd* pCmd, QAngle &In, BasePlayer* LocalPlayer, CSWeapon* Weapon, bool isAA )
{
	if( !Weapon || !Weapon->IsWeapon( ) ) return;

	auto Seed = pCmd->random_seed;
	auto FutureSeed = ( Seed & 255 ) + 1u;
	RandomSeed( FutureSeed );
	auto RandomX = RandomFloat( -0.5f , 0.5f ) + RandomFloat( -0.5f , 0.5f );
	auto RandomY = RandomFloat( -0.5f , 0.5f ) + RandomFloat( -0.5f , 0.5f );
	auto WeaponSpread = Weapon->GetSpread( );
	auto Spread = Vector( WeaponSpread * RandomX , WeaponSpread * RandomY , 0.0f );

	if( g_CVars.Miscellaneous.AntiAim.Active && isAA ) Spread = -Spread;

	auto Forward = Vector( 0.f, 0.f, 0.f ), Side = Vector( 0.f, 0.f, 0.f ), Up = Vector( 0.f, 0.f, 0.f );
	auto Angle = QAngle( 0.f, 0.f, 0.f );
	auto AngleLast = In;
	AngleVectors( Angle , &Forward , &Side , &Up );
	auto Direction = Forward + ( -Spread.x * Side ) + ( -Spread.y * Up );
	Direction.NormalizeInPlace();
	auto AngleCosineX = cosf( DEG2RAD( AngleLast.x ) );
	auto RotatedY = ( AngleCosineX / Direction.y );
	if( RotatedY > 1.0f || RotatedY < -1.0f ) RotatedY = 1.0f / RotatedY;
	
	auto SideInputRotated = Vector( 0.f, 0.f, 0.f );
	SideInputRotated.x = sqrtf( 1.0f - pow( RotatedY, 2 ) );
	SideInputRotated.y = RotatedY;
	SideInputRotated.z = 0.0f;
	
	auto AngleAdjust = QAngle();
	AngleAdjust.y = RAD2DEG( atan2f( SideInputRotated.y , SideInputRotated.x ) );
	if( AngleAdjust.y < 0.0f ) AngleAdjust.y += 360.0f;

	AngleAdjust.x = g_Stuff.GuwopNormalize( AngleAdjust.x );
	AngleAdjust.y = g_Stuff.GuwopNormalize( AngleAdjust.y );
	AngleAdjust.z = g_Stuff.GuwopNormalize( AngleAdjust.z );
	
	auto SideInputNormal = Vector( 0.f, 0.f, 0.f );
	SideInputNormal.x = sqrtf( 1.0f - pow( Direction.y, 2 ) );
	SideInputNormal.y = Direction.y;
	SideInputNormal.z = 0.0f;
	
	auto RecipRotated = SideInputRotated.y / SideInputRotated.x;
	auto RecipNormal = SideInputNormal.y / SideInputNormal.x;
	
	auto AngleInputRadX = RecipNormal / RecipRotated;
	if ( AngleInputRadX > 1.0f || AngleInputRadX < -1.0f ) AngleInputRadX = 1.0f / AngleInputRadX;
	
	auto AngleInput = QAngle( 0.f, 0.f, 0.f );
	AngleInput.x = RAD2DEG( std::asin( AngleInputRadX ) );
	if( AngleInput.x < 0.0f ) AngleInput.x += 360.0f;

	AngleInput.x = g_Stuff.GuwopNormalize( AngleInput.x );
	AngleInput.y = g_Stuff.GuwopNormalize( AngleInput.y );
	AngleInput.z = g_Stuff.GuwopNormalize( AngleInput.z );
	
	auto AngleTempX = AngleLast.x;
	if( AngleTempX < 0.0f ) AngleTempX = -AngleTempX;
	AngleInput.x -= ( 45.0f - AngleTempX ) * 2.0f;
	if( AngleLast.x < 0.0f ) AngleInput.x = -AngleInput.x;
	
	AngleInput.x = g_Stuff.GuwopNormalize( AngleInput.x );
	AngleInput.y = g_Stuff.GuwopNormalize( AngleInput.y );
	AngleInput.z = g_Stuff.GuwopNormalize( AngleInput.z );

	AngleVectors( AngleInput, &Forward , &Side , &Up );
	Direction = Forward + ( Spread.x * Side ) + ( Spread.y * Up );
	Direction.y = 0.0f;
	Direction.NormalizeInPlace( );
	AngleAdjust.x = RAD2DEG( atan2f( Direction.z , Direction.x ) );
	if( AngleAdjust.x < 0.0f ) AngleAdjust.x += 360.0f;

	AngleAdjust.x = g_Stuff.GuwopNormalize( AngleAdjust.x );
	AngleAdjust.y = g_Stuff.GuwopNormalize( AngleAdjust.y );
	AngleAdjust.z = g_Stuff.GuwopNormalize( AngleAdjust.z );

	auto AngleSpread = AngleLast;
	
	AngleSpread.x += AngleLast.x + AngleAdjust.x;
	AngleSpread.y += AngleAdjust.y;
	AngleSpread.z = 0.0f;
	
	AngleSpread.x = g_Stuff.GuwopNormalize( AngleSpread.x );
	AngleSpread.y = g_Stuff.GuwopNormalize( AngleSpread.y );
	AngleSpread.z = g_Stuff.GuwopNormalize( AngleSpread.z );

	In = AngleSpread;
}

void NoSpread::Main( CUserCmd* pCmd, QAngle &In, BasePlayer* LocalPlayer, CSWeapon* Weapon, bool isAA )
{
	if( !Weapon || !Weapon->IsWeapon( ) ) return;
	float flSpread = Weapon->GetSpread( ); // g_spread;
	Vector forward, right, up, spread, dir;

	RandomSeed( ( pCmd->random_seed & 255 ) + 1 );
	spread.x = RandomFloat( -0.5f, 0.5f ) + RandomFloat( -0.5f, 0.5f );
	spread.y = RandomFloat( -0.5f, 0.5f ) + RandomFloat( -0.5f, 0.5f );
	spread.z = 0.0f;

	spread.x *= flSpread;
	spread.y *= flSpread;

	if( g_CVars.Miscellaneous.AntiAim.Active )
	{
		if( !isAA ) spread = -spread;
	}
	else
	{
		spread = -spread;
	}

	QAngle Temp = pCmd->viewangles;
	AngleVectors( pCmd->viewangles, &forward, &right, &up );
	dir = forward + spread.x * right + spread.y * up;
	VectorNormalize( dir );

	if( g_CVars.Accuracy.NoSpreadMode == 1 )
	{
		VectorAngles( dir, In );

		Vector fix[ 3 ];
 
		fix[ 2 ][ 0 ] = 1.0f;
		fix[ 2 ][ 1 ] = -spread.x;
		fix[ 2 ][ 2 ] = spread.y;
	
		VectorNormalize( fix[ 2 ] );
	
		fix[ 0 ][ 0 ] = 0.0f;
		fix[ 0 ][ 1 ] = -spread.x;
		fix[ 0 ][ 2 ] = ( 1.0f / spread.y ) + ( 1.0f / fix[ 2 ][ 2 ] ) + spread.y;
	
		if( spread.x > 0.0f && spread.y < 0.0f )
		{
			if( fix[ 0 ][ 1 ] < 0.0f ) fix[ 0 ][ 1 ] = -fix[ 0 ][ 1 ];
		}
		else if( spread.x < 0.0f && spread.y < 0.0f )
		{
			if( fix[ 0 ][ 1 ] > 0.0f ) fix[ 0 ][ 1 ] = -fix[ 0 ][ 1 ];
		}
	
		if( fix[ 0 ][ 2 ] < 0.0f ) fix[ 0 ][ 2 ] = -fix[ 0 ][ 2 ];
	
		VectorNormalize( fix[ 0 ] );
		CrossProduct( fix[ 0 ], fix[ 2 ], fix[ 1 ] );
		VectorNormalize( fix[ 1 ] );
	
		float cross = ( fix[ 1 ][ 1 ] * fix[ 2 ][ 0 ] ) - ( fix[ 1 ][ 0 ] * fix[ 2 ][ 1 ] );
		float roll = 0.0f;
	
		if( pCmd->viewangles.x > 84.0f || pCmd->viewangles.x < -84.0f ) roll = RAD2DEG( atan2f( fix[ 1 ][ 2 ], sqrtf ( cross ) ) );
		else roll = RAD2DEG( atan2f( fix[ 1 ][ 2 ], cross ) );
		if( roll < 0.0f ) roll += 360.0f;
		pCmd->viewangles.z += roll; // apply roll fix
	}
}

void NoSpread::Iterative( CUserCmd* pCmd, QAngle &In, BasePlayer* LocalPlayer, CSWeapon* Weapon, bool isAA )
{
	if( !Weapon || !Weapon->IsWeapon( ) ) return;

	float flSpread = Weapon->GetSpread( ); // g_spread;
	WeaponInfo WeaponInfo = GetWeaponInfo( Weapon );
	Vector forward, right, up, dir, viewforward, viewright, viewup, spread, serverspread;
	QAngle out, modifier;

	RandomSeed( ( pCmd->random_seed & 255 ) + 1 );
	spread.x = RandomFloat( -0.5f, 0.5f ) + RandomFloat( -0.5f, 0.5f );
	spread.y = RandomFloat( -0.5f, 0.5f ) + RandomFloat( -0.5f, 0.5f );
	spread.z = 0.0f;

	spread.x *= flSpread;
	spread.y *= flSpread;

	if( g_CVars.Miscellaneous.AntiAim.Active )
	{
		if( !isAA ) spread = -spread;
	}
	else
	{
		spread = -spread;
	}

	AngleVectors( pCmd->viewangles, &forward, &right, &up );
	dir = forward + spread.x * right + spread.y * up;

	VectorNormalize( dir );
	g_Stuff.VectorAngles_( dir, up, out );

	for( int i = 0; i <= 24; i++ )
	{
		AngleVectors( out, &viewforward, &viewright, &viewup );
		serverspread = viewforward + -spread.x * viewright + -spread.y * viewup;

		VectorNormalize( serverspread );

		VectorAngles( serverspread, modifier );
		modifier = In - modifier;

		if( sqrt( ( modifier.x * modifier.x ) + ( modifier.y * modifier.y ) ) == 0 ) break;

		out += modifier;
	}

	In = out;
}