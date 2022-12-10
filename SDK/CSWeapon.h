/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __CSWEAPON_H__
#define __CSWEAPON_H__

#include "GlobalVarsBase.h"
#include "BaseCombatWeapon.h"

enum WeaponType_t
{
        WEAPONTYPE_KNIFE = 0,
        WEAPONTYPE_PISTOL,
        WEAPONTYPE_SUBMACHINEGUN,
        WEAPONTYPE_RIFLE,
        WEAPONTYPE_SHOTGUN,
        WEAPONTYPE_SNIPER_RIFLE,
        WEAPONTYPE_MACHINEGUN,
        WEAPONTYPE_C4,
        WEAPONTYPE_GRENADE,
        WEAPONTYPE_UNKNOWN
};

struct WeaponInfo
{
	int	ID,
		Penetration,
		Damage,
		BulletsPerShots,
		BulletType;

	float MaxRange,
		RangeModifier,
		PenetrationRange,
		PenetrationPower,
		ArmorRatio,
		CycleTime,
		AccuracyDivisor,
		AccuracyOffset,
		MaxInaccuracy;
	
	bool AccuracyQuadratic;
	
	const char* Alias;
};

enum 
{
	BULLET_NONE = 0,
	BULLET_PLAYER_9MM, 
	BULLET_PLAYER_45ACP,
	BULLET_PLAYER_338MAG,
	BULLET_PLAYER_762MM,
	BULLET_PLAYER_556MM,
	BULLET_PLAYER_50AE,
	BULLET_PLAYER_57MM,
	BULLET_PLAYER_357SIG,
};

extern Valve::CGlobalVarsBase* g_pGlobals;
extern float g_fPredictedCurtime;
extern int g_numWeapons;
namespace Valve
{
#define CLASSNAME CSWeapon
	class CSWeapon:
		public BaseCombatWeapon
	{
	public:
		//OB functions:
		//VFUNCN0(UpdateAccuracyPenalty, 0x00);
		//VFUNCR0(GetWeaponSpread, 0x00, float);
		//VFUNCR0(GetWeaponInaccuracy, 0x00, float);
		//NETVAR(float, DT_WeaponCSBase, m_fAccuracyPenalty);

		VFUNCR0( vtGetWeaponId, 0x4A4, int );
		NETVARN( bool, DT_WeaponUSP, m_bSilencerOn, m_bSilencerOnUSP );
		NETVARN( bool, DT_WeaponM4A1, m_bSilencerOn, m_bSilencerOnM4A1 );
		NETVARN( bool, DT_WeaponGlock, m_bBurstMode, m_bBurstModeGlock );
		NETVARN( bool, DT_WeaponFamas, m_bBurstMode, m_bBurstModeFamas );

		inline float& m_flGlock18Shoot( )
		{ 
			return *( float* )( 0x780 + ( DWORD_PTR ) this ); 
		}

		inline float& m_flFamasShoot( )
		{
			return *( float* )( 0x784 + ( DWORD_PTR ) this ); 
		}
 
		inline float& m_flFamasBurstSpread( )
		{
			return *( float* )( 0x78C + ( DWORD_PTR ) this ); 
		}

		inline float& m_flAccuracy( )
		{ 
			return *( float* )( 0x760 + ( DWORD_PTR ) this ); 
		}

		inline float& m_zoomFullyActiveTime( )
		{ 
			return *( float* )( 0x778 + ( DWORD_PTR ) this ); 
		}

		inline int& m_iGlock18ShotsFired( )
		{ 
			return *( int* )( 0x77C + ( DWORD_PTR ) this ); 
		}

		inline CSPlayer* GetPlayerOwner( )
		{
			return ( ( CSPlayer* ( __thiscall* )( CSWeapon* ) ) 0x241E0D40 )( this );
		}

		inline int GetWeaponID( )
		{
			int id = vtGetWeaponId( );
			if( id < 0 ) id = 0;
			else if( id > 29 ) id = 0;
			return id;
		}

		inline void GetWeaponBulletType( int &iBulletType )
		{
			int id = GetWeaponID( );
			switch( id )
			{
				case 0: iBulletType = 0; break;
				case 1: iBulletType = BULLET_PLAYER_357SIG; break;
				case 2: iBulletType = BULLET_PLAYER_9MM; break;
				case 3: iBulletType = BULLET_PLAYER_762MM; break;
				case 7: iBulletType = BULLET_PLAYER_45ACP; break;
				case 8: iBulletType = BULLET_PLAYER_762MM; break;
				case 10: iBulletType = BULLET_PLAYER_9MM; break;
				case 11: iBulletType = BULLET_PLAYER_57MM; break;
				case 12: iBulletType = BULLET_PLAYER_45ACP; break;
				case 13: iBulletType = BULLET_PLAYER_556MM; break;
				case 14: iBulletType = BULLET_PLAYER_556MM; break;
				case 15: iBulletType = BULLET_PLAYER_556MM; break;
				case 16: iBulletType = BULLET_PLAYER_45ACP; break;
				case 17: iBulletType = BULLET_PLAYER_338MAG; break;
				case 18: iBulletType = BULLET_PLAYER_9MM; break;
				case 19: iBulletType = BULLET_PLAYER_556MM; break;
				case 21: iBulletType = BULLET_PLAYER_556MM; break;
				case 22: iBulletType = BULLET_PLAYER_9MM; break;
				case 23: iBulletType = BULLET_PLAYER_762MM; break;
				case 25: iBulletType = BULLET_PLAYER_50AE; break;
				case 26: iBulletType = BULLET_PLAYER_556MM; break;
				case 27: iBulletType = BULLET_PLAYER_762MM; break;
				case 29: iBulletType = BULLET_PLAYER_57MM; break;
				default: iBulletType = 0; break;
			}
		}

		inline void GetBulletTypeParameters( int iBulletType, float &fPenetrationPower,float &flPenetrationDistance )
		{
			switch( iBulletType )
			{
				case BULLET_PLAYER_9MM: fPenetrationPower = 21; flPenetrationDistance = 800.f; break;
				case BULLET_PLAYER_45ACP: fPenetrationPower = 15; flPenetrationDistance = 500.f; break;
				case BULLET_PLAYER_338MAG: fPenetrationPower = 45; flPenetrationDistance = 8000.f; break;
				case BULLET_PLAYER_762MM: fPenetrationPower = 39;  flPenetrationDistance = 5000.f; break;
				case BULLET_PLAYER_556MM: fPenetrationPower = 35; flPenetrationDistance = 4000.f; break;
				case BULLET_PLAYER_50AE: fPenetrationPower = 30; flPenetrationDistance = 1000.f; break;
				case BULLET_PLAYER_57MM: fPenetrationPower = 30; flPenetrationDistance = 2000.f; break;			
				case BULLET_PLAYER_357SIG: fPenetrationPower = 25; flPenetrationDistance = 800.f; break;
				default: fPenetrationPower = 0; flPenetrationDistance = 0.0; break;
			}
		}

		inline void GetMaterialParameters( int iMaterial, float &flPenetrationModifier, float &flDamageModifier )
		{
			switch( iMaterial )
			{
				case 'M': flPenetrationModifier = 0.5; flDamageModifier = 0.3; break;
				case 'D': flPenetrationModifier = 0.5; flDamageModifier = 0.3; break;
				case 'C': flPenetrationModifier = 0.4; flDamageModifier = 0.25; break;
				case 'G': flPenetrationModifier = 1.0; flDamageModifier = 0.99; break;
				case 'V': flPenetrationModifier = 0.5; flDamageModifier = 0.45; break;
				case 'T': flPenetrationModifier = 0.65; flDamageModifier = 0.3; break;
				case 'P': flPenetrationModifier = 0.4; flDamageModifier = 0.45; break;
				case 'W': flPenetrationModifier = 1.0; flDamageModifier = 0.6; break;
				default: flPenetrationModifier = 1.0; flDamageModifier = 0.5; break;
			}
		}

		inline const char* GetWeaponAlias( )
		{
			typedef const char* ( *WeaponIDToAlias_t )( int WeaponID );
			return ( ( WeaponIDToAlias_t )( ( DWORD ) GetModuleHandleA( "client.dll" ) + 0x1E0B00 ) )( GetWeaponID( ) );
		}

		inline bool IsWeapon( )
		{ 
			switch( GetWeaponID( ) )
			{ 
			case 0: 
			case 4: 
			case 6: 
			case 9: 
			case 24: 
			case 28: 
				return false; 
			default: 
				return true; 
			} 
		}

		inline bool IsPistol( )
		{ 
			switch( GetWeaponID( ) )
			{ 
			case 1: 
			case 2: 
			case 10: 
			case 11: 
			case 16: 
			case 25: 
				return false; 
			default: 
				return true; 
			} 
		}

		inline bool SpecialMode( )
		{	
			if( GetWeaponID( ) == 2 ) return m_bBurstModeGlock( );
			else if( GetWeaponID( ) == 15 ) return m_bBurstModeFamas( );
			else if( GetWeaponID( ) == 21 ) return m_bSilencerOnM4A1( );
			else if( GetWeaponID( ) == 16 ) return m_bSilencerOnUSP( );
			return false;
		}

		inline float GetSpread( )
		{
			CSPlayer* LocalPlayer = GetPlayerOwner( );
			
			//if( !LocalPlayer ) return 0.0f;			
			float flSpread = 0.0f;
			
			//float flAccuracy = m_flAccuracy( );
			int m_iFOV = *( int* )( ( DWORD ) LocalPlayer + 0xD1C );
			Vector vecVelocity = LocalPlayer->m_vecVelocity( );
			//vec_t iSpeed = LocalPlayer->GetAbsVelocity( ).Length2D( );
			int iSpeed;

			if( vecVelocity.IsLengthLessThan( 1 ) ) iSpeed = 0;
			else iSpeed = (int)vecVelocity.Length2D( );

			//if( LocalPlayer->GetAbsVelocity( ).IsLengthLessThan( 1 ) ) iSpeed = 0;
			
			switch( GetWeaponID( ) )
			{
				case 0:
				{
					flSpread = 0.0f;
					break;
				}
				case 27:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ( 0.04f + ( 0.4f ) * ( m_flAccuracy() ) );
					else if( iSpeed > 140 )
						flSpread = ( 0.04f + ( 0.07f ) * ( m_flAccuracy() ) );
					else
						flSpread = ( ( 0.0275f ) * ( m_flAccuracy() ) );
					break;
				}
				case 8:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ( 0.035f + ( 0.4f ) * ( m_flAccuracy() ) );
					else if (iSpeed > 140)
						flSpread = ( 0.035f + ( 0.07f ) * ( m_flAccuracy() ) );
					else
						flSpread = ( ( 0.02f ) * ( m_flAccuracy() ) );
					break;
				}
				case 17:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = 0.85f;
					else if( iSpeed > 140 )
						flSpread = 0.25f;
					else if( iSpeed > 10 )
						flSpread = 0.10f;
					else if( LocalPlayer->m_fFlags( ) & FL_DUCKING )
						flSpread = 0.0f;
					else
						flSpread = 0.001f;
					
					if( m_iFOV == 0 || m_iFOV == 90 ) flSpread += 0.08f;
					break;
				}
				case 6:
				{
					flSpread = 0.0f;
					break;
				}
				case 25: // 241E2E90
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ( ( 1.5f ) * ( 1 - m_flAccuracy() ) );
					else if( iSpeed > 5 )
						flSpread = ( ( 0.25f ) * ( 1 - m_flAccuracy() ) );
					else if( ( LocalPlayer->m_fFlags( ) & FL_DUCKING ) )
						flSpread = ( ( 0.115f ) * ( 1 - m_flAccuracy() ) );
					else
						flSpread = ( ( 0.13f ) * ( 1 - m_flAccuracy() ) );
					break;
				}
				case 10: // 241E3800
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ( ( 1.3f ) * ( 1 - m_flAccuracy() ) );
					else if( iSpeed > 5 )
						flSpread = ( ( 0.175f ) * ( 1 - m_flAccuracy() ) );
					else if( ( LocalPlayer->m_fFlags( ) & FL_DUCKING ) )
						flSpread = ( ( 0.08f ) * ( 1 - m_flAccuracy() ) );
					else
						flSpread = ( ( 0.1f ) * ( 1 - m_flAccuracy() ) );
					break;
				}
				case 15:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ( 0.03f + ( 0.3f ) * ( m_flAccuracy() ) );
					else if( iSpeed > 140 )
						flSpread = ( 0.03f + ( 0.07f ) * ( m_flAccuracy() ) );
					else
						flSpread = ( ( 0.02f ) * ( m_flAccuracy() ) );
					
					if( SpecialMode( ) )
					{
						if( m_flFamasShoot( ) != 0.0f && m_flFamasShoot( ) < g_pGlobals->curtime ) flSpread = m_flFamasBurstSpread( );
					}
					else
						flSpread += 0.01f;
					break;
				}
				case 11: // 241E91C0
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ( ( 1.5f ) * ( 1 - m_flAccuracy() ) );
					else if( iSpeed > 5 )
						flSpread = ( ( 0.255f ) * ( 1 - m_flAccuracy() ) );
					else if( LocalPlayer->m_fFlags( ) & FL_DUCKING )
						flSpread = ( ( 0.075f ) * ( 1 - m_flAccuracy() ) );
					else
						flSpread = ( ( 0.15f ) * ( 1 - m_flAccuracy() ) );
					break;
				}
				case 24:
				{
					flSpread = 0.0f;
					break;
				}
				case 23:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ((0.45f) * (1 - m_flAccuracy()));
					else if( iSpeed > 5 )
						flSpread = 0.15f;
					else if( LocalPlayer->m_fFlags( ) & FL_DUCKING )
						flSpread = ( ( 0.035f ) * ( 1 - m_flAccuracy() ) );
					else
						flSpread = ( ( 0.055f ) * ( 1 - m_flAccuracy() ) );
					
					if( m_iFOV == 0 || m_iFOV == 90 ) flSpread += 0.025f;
					break;
				}
				case 14:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ( 0.04f + ( 0.3f ) * ( m_flAccuracy() ) );
					else if( iSpeed > 140 )
						flSpread = ( 0.04f + ( 0.07f ) * ( m_flAccuracy() ) );
					else
						flSpread = ( ( 0.0375f ) * ( m_flAccuracy() ) );
					break;
				}
				case 2: // 241E5C30
				{
					if( SpecialMode( ) )
					{
						if( m_flGlock18Shoot( ) != 0.f )
						{
							flSpread = 0.05;
						}
						else
						{
							if( LocalPlayer->m_fFlags( ) & FL_ONGROUND )
							{
								if( iSpeed <= 5 )
								{
									if( LocalPlayer->m_fFlags( ) & FL_DUCKING ) flSpread = ( 1 - m_flAccuracy() ) * 0.095f;
									else flSpread = ( 1 - m_flAccuracy() ) * 0.185f;
								}
								else flSpread = ( 1 - m_flAccuracy() ) * 0.3f;
							}
							else flSpread = ( 1 - m_flAccuracy() ) * 1.2f;
						}
					}
					else
					{
						if( LocalPlayer->m_fFlags( ) & FL_ONGROUND )
						{
							if( iSpeed <= 5 )
							{
								if( LocalPlayer->m_fFlags( ) & FL_DUCKING ) flSpread = ( 1 - m_flAccuracy() ) * 0.075f;
								else flSpread = ( 1 - m_flAccuracy() ) * 0.1f;
							}
							else flSpread = ( 1 - m_flAccuracy() ) * 0.165f;
						}
						else flSpread = 1 - m_flAccuracy();
					}
					break;
				}
				case 4:
				{
					flSpread = 0.0f;
					break;
				}
				case 28:
				{
					flSpread = 0.0f;
					break;
				}
				case 19:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = (0.045f + (0.5f) * (m_flAccuracy()));
					else if (iSpeed > 140)
						flSpread = (0.045f + (0.095f) * (m_flAccuracy()));
					else
						flSpread = ((0.03f) * (m_flAccuracy()));
					break;
				}
				case 20:
				{
					flSpread = 0.0675f;
					break;
				}
				case 21:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = (0.035f + (0.4f) * (m_flAccuracy()));
					else if( iSpeed > 140 )
						flSpread = (0.035f + (0.07f) * (m_flAccuracy()));
					else
					{
						if( SpecialMode( ) )
							flSpread = ((0.025f) * (m_flAccuracy()));
						else
							flSpread = ((0.02f) * (m_flAccuracy()));
					}
					break;
				}
				case 7:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ((0.375f) * (m_flAccuracy()));
					else
						flSpread = ((0.03f) * (m_flAccuracy()));
					break;
				}
				case 18:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ((0.2f) * (m_flAccuracy()));
					else
						flSpread = ((0.04f) * (m_flAccuracy()));
					break;
				}
				case 1: // 241E4680
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ((1.5f) * (1 - m_flAccuracy()));
					else if( iSpeed > 5 )
						flSpread = ((0.255f) * (1 - m_flAccuracy()));
					else if( LocalPlayer->m_fFlags( ) & FL_DUCKING )
						flSpread = ((0.075f) * (1 - m_flAccuracy()));
					else
						flSpread = ((0.15f) * (1 - m_flAccuracy()));
					break;
				}
				case 29:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ((0.3f) * (m_flAccuracy()));
					else if (iSpeed > 170)
						flSpread = ((0.115f) * (m_flAccuracy()));
					else
						flSpread = ((0.045f) * (m_flAccuracy()));
					break;
				}
				case 3:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = 0.2f;
					else if (iSpeed > 170)
						flSpread = 0.075f;
					else if( LocalPlayer->m_fFlags( ) & FL_DUCKING )
						flSpread = 0.0f;
					else
						flSpread = 0.007f;
				
					if( m_iFOV == 0 || m_iFOV == 90 ) flSpread += 0.025f;
					break;
				}
				case 13:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ((0.45f) * (1 - m_flAccuracy()));
					else if( iSpeed > 5 )
						flSpread = 0.15f;
					else if( LocalPlayer->m_fFlags( ) & FL_DUCKING )
						flSpread = ((0.04f) * (1 - m_flAccuracy()));
					else
						flSpread = ((0.05f) * (1 - m_flAccuracy()));
				
					if( m_iFOV == 0 || m_iFOV == 90 ) flSpread += 0.025f;
					break;
				}
				case 26:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = (0.035f + (0.45f) * (m_flAccuracy()));
					else if (iSpeed > 140)
						flSpread = (0.035f + (0.075f) * (m_flAccuracy()));
					else
						flSpread = ((0.02f) * (m_flAccuracy()));
					break;
				}
				case 9:
				{
					flSpread = 0.0f;
					break;
				}
				case 22:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ((0.25f) * (m_flAccuracy()));
					else
						flSpread = ((0.03f) * (m_flAccuracy()));
					break;
				}
				case 12:
				{
					if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
						flSpread = ((0.24f) * (m_flAccuracy()));
					else
						flSpread = ((0.04f) * (m_flAccuracy()));
					break;
				}
				case 16: // 241EB810
				{
					if( SpecialMode( ) )
					{
						if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
							flSpread = ((1.3f) * (1 - m_flAccuracy()));
						else if( iSpeed > 5 )
							flSpread = ((0.25f) * (1 - m_flAccuracy()));
						else if( LocalPlayer->m_fFlags( ) & FL_DUCKING )
							flSpread = ((0.125f) * (1 - m_flAccuracy()));
						else
							flSpread = ((0.15f) * (1 - m_flAccuracy()));
					}
					else
					{
						if( !( LocalPlayer->m_fFlags( ) & FL_ONGROUND ) )
							flSpread = ((1.2f) * (1 - m_flAccuracy()));
						else if( iSpeed > 5 )
							flSpread = ((0.225f) * (1 - m_flAccuracy()));
						else if( LocalPlayer->m_fFlags( ) & FL_DUCKING )
							flSpread = ((0.08f) * (1 - m_flAccuracy()));
						else
							flSpread = ((0.1f) * (1 - m_flAccuracy()));
					}
					break;
				}
				case 5:
				{
					flSpread = 0.0725f;
					break;
				}
				default:
				{
					flSpread = 0.0f;
					break;
				}
			}
			
			return flSpread;
		}
	};

};

#endif //__CSWEAPON_H__