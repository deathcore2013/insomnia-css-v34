#include "Main.h"

Aimbot g_Aimbot;

bool Aimbot::CheckVisible( Vector& vecAbsStart, Vector& vecAbsEnd, BasePlayer* Target, BasePlayer* LocalPlayer )
{
	CSWeapon* Weapon = ( CSWeapon* ) LocalPlayer->GetActiveBaseCombatWeapon( );
	if( !Weapon ) return false;

	trace_t Trace;
	Ray_t Ray;
	TraceFilterSkipTwoEntities TraceFilter( Target, 0 );

	// todo: proper vis check

	Ray.Init( vecAbsStart, vecAbsEnd );
	g_pEngineTrace->TraceRay( Ray, 0x46004003, ( ITraceFilter* )&TraceFilter, &Trace );
	return ( Trace.fraction == 1.f );

}

bool Aimbot::CheckVisibleAWallCheck( Vector& vecAbsStart, Vector& vecAbsEnd, BasePlayer* Target, BasePlayer* LocalPlayer )
{
	CSWeapon* Weapon = ( CSWeapon* ) LocalPlayer->GetActiveBaseCombatWeapon( );
	if( !Weapon ) return false;

	trace_t Trace;
	Ray_t Ray;
	TraceFilterSkipTwoEntities traceFilter( Target, 0 );

	// todo: proper vis check

	if( g_CVars.Aimbot.AutoWall )
	{
		BaseEntity* pPlayerHit = nullptr;
		if( GetTotalDamage( LocalPlayer, Weapon, &pPlayerHit ) >= g_CVars.Aimbot.MinDamage ) return true;
		else
		{
			Ray.Init( vecAbsStart, vecAbsEnd );
			g_pEngineTrace->TraceRay( Ray, 0x46004003, ( ITraceFilter* )&traceFilter, &Trace );
			return ( Trace.fraction == 1.f );
		}
	}
	else
	{
		Ray.Init( vecAbsStart, vecAbsEnd );
		g_pEngineTrace->TraceRay( Ray, 0x46004003, ( ITraceFilter* )&traceFilter, &Trace );
		return ( Trace.fraction == 1.f );
	}
}

void Aimbot::GetHitbox( int iHitbox, BasePlayer* Entity )
{
	if( g_CVars.Aimbot.Interpolation.LagPrediction )
	{
		g_Stuff.StoreTickRecord( Entity, &pBackupData[ Entity->entindex( ) ] );
		g_Stuff.ApplyTickRecord( Entity, &pPlayerHistory[ Entity->entindex( ) ][ 0 ] );

		int m_iAccumulatedBoneMask = *( int* )( ( DWORD ) Entity + 0x49C + 0x4 );
		int m_nReadableBones = *( int* )( ( DWORD ) Entity + 0x4A8 + 0x4 );
		int m_nWritableBones = *( int* )( ( DWORD ) Entity + 0x4AC + 0x4 );
		int m_iPrevBoneMask = *( int* )( ( DWORD ) Entity + 0x498 + 0x4 );

		*( int* )( ( DWORD ) Entity + 0x4A8 + 0x4 ) = 0;							// baseanimating + 0x4A8
		*( int* )( ( DWORD ) Entity + 0x4AC + 0x4 ) = 0;							// baseanimating + 0x4AC
		*( int* )( ( DWORD ) Entity + 0x498 + 0x4 ) = m_iAccumulatedBoneMask;		// baseanimating + 0x498
		*( int* )( ( DWORD ) Entity + 0x49C + 0x4 ) = 0;							// baseanimating + 0x49C
	}

	matrix3x4_t matrix[ 128 ];
	if( !( Entity->SetupBones( matrix, 128, 0x100, Entity->m_flSimulationTime( ) ) ) ) return;
	void* pModel = Entity->GetModel( );
	if( !pModel ) return;
	studiohdr_t* studiohdr = g_pModelInfo->GetStudiomodel( pModel );
	mstudiohitboxset_t* studiohitboxset = studiohdr->pHitboxSet( Entity->m_nHitboxSet( ) );	
	if( !studiohitboxset ) return;
	mstudiobbox_t* studiobbox = studiohitboxset->pHitbox( iHitbox );
	if( !studiobbox ) return;

	float scalecenter = g_pGlobals->interval_per_tick * g_CVars.Aimbot.PointScale;

	mins[ Entity->entindex( ) ] = studiobbox->bbmin;
	maxs[ Entity->entindex( ) ] = studiobbox->bbmax;

	Vector points[ ] = { ( ( studiobbox->bbmin + studiobbox->bbmax ) * .5f ),
		Vector( studiobbox->bbmin.x + ( studiobbox->bbmax.x * ( 1 - g_CVars.Aimbot.PointScale ) * .5f ), studiobbox->bbmin.y + ( studiobbox->bbmax.y * ( 1 - g_CVars.Aimbot.PointScale ) ), studiobbox->bbmin.z + ( studiobbox->bbmax.z * ( 1 - g_CVars.Aimbot.PointScale ) ) ),
	  Vector( studiobbox->bbmin.x + ( studiobbox->bbmax.x * ( 1 - g_CVars.Aimbot.PointScale ) * .5f ), studiobbox->bbmax.y - ( studiobbox->bbmax.y * ( 1 - g_CVars.Aimbot.PointScale ) ), studiobbox->bbmin.z + ( studiobbox->bbmax.z * ( 1 - g_CVars.Aimbot.PointScale ) ) ),
	  Vector( studiobbox->bbmax.x - ( studiobbox->bbmax.x * ( 1 - g_CVars.Aimbot.PointScale ) * .5f ), studiobbox->bbmax.y - ( studiobbox->bbmax.y * ( 1 - g_CVars.Aimbot.PointScale ) ), studiobbox->bbmin.z + ( studiobbox->bbmax.z * ( 1 - g_CVars.Aimbot.PointScale ) ) ),
	  Vector( studiobbox->bbmax.x - ( studiobbox->bbmax.x * ( 1 - g_CVars.Aimbot.PointScale ) * .5f ), studiobbox->bbmin.y + ( studiobbox->bbmax.y * ( 1 - g_CVars.Aimbot.PointScale ) ), studiobbox->bbmin.z + ( studiobbox->bbmax.z * ( 1 - g_CVars.Aimbot.PointScale ) ) ),
	  Vector( studiobbox->bbmax.x - ( studiobbox->bbmax.x * ( 1 - g_CVars.Aimbot.PointScale ) * .5f ), studiobbox->bbmax.y - ( studiobbox->bbmax.y * ( 1 - g_CVars.Aimbot.PointScale ) ), studiobbox->bbmax.z - ( studiobbox->bbmax.z * ( 1 - g_CVars.Aimbot.PointScale ) ) ),
	  Vector( studiobbox->bbmin.x + ( studiobbox->bbmax.x * ( 1 - g_CVars.Aimbot.PointScale ) * .5f ), studiobbox->bbmax.y - ( studiobbox->bbmax.y * ( 1 - g_CVars.Aimbot.PointScale ) ), studiobbox->bbmax.z - ( studiobbox->bbmax.z * ( 1 - g_CVars.Aimbot.PointScale ) ) ),
	  Vector( studiobbox->bbmin.x + ( studiobbox->bbmax.x * ( 1 - g_CVars.Aimbot.PointScale ) * .5f ), studiobbox->bbmin.y + ( studiobbox->bbmax.y * ( 1 - g_CVars.Aimbot.PointScale ) ), studiobbox->bbmax.z - ( studiobbox->bbmax.z * ( 1 - g_CVars.Aimbot.PointScale ) ) ),
	  Vector( studiobbox->bbmax.x - ( studiobbox->bbmax.x * ( 1 - g_CVars.Aimbot.PointScale ) * .5f ), studiobbox->bbmin.y + ( studiobbox->bbmax.y * ( 1 - g_CVars.Aimbot.PointScale ) ), studiobbox->bbmax.z - ( studiobbox->bbmax.z * ( 1 - g_CVars.Aimbot.PointScale ) ) ) };

	float flPitch = Entity->m_angEyeAngles( ).x;

	if( iHitbox == 12 )
	{
		if( g_CVars.Aimbot.HitboxMode == 0 )
		{
			if( g_CVars.Aimbot.AutoHeightMode[ Entity->entindex( ) ] == 1 )
			{
				if( Entity->m_vecVelocity( ).Length2D( ) < 40.f && !( Entity->m_fFlags( ) & FL_DUCKING ) )
				{
					Vector a = ( ( points[ 3 ] + points[ 5 ] ) * .5f );

					if( ( flPitch > 50.f ) && ( flPitch < 91.f ) )
					{
						Vector b = ( ( ( a - points[ 0 ] ) / 3 ) * 4 );
						Vector c = ( points[ 0 ] + ( b * .7f ) );
						points[ 0 ] = c;
					}
					else if( ( flPitch >= -91.f ) && ( flPitch <= -50.f ) ) points[ 0 ].z -= 1.f;
				}
				else
				{
					if( ( flPitch > 50.f ) && ( flPitch < 91.f ) )
					{
						points[ 0 ].x = studiobbox->bbmin.x * .75f;
						points[ 0 ].y = studiobbox->bbmax.y * .75f; 
						points[ 0 ].z = ( studiobbox->bbmin.z + studiobbox->bbmax.z ) * .5f;
					}
					else if( ( flPitch >= -91.f ) && ( flPitch <= -50.f ) ) points[ 0 ].z -= 1.f;
				}
			}
		}
		else
		{
			if( g_CVars.Aimbot.HitboxMode == 2 || g_CVars.Aimbot.HitboxMode == 3 )
			{		
				if( ( flPitch > 50.f ) && ( flPitch < 91.f ) )
				{
					points[ 0 ].x = studiobbox->bbmin.x * .75f;
					points[ 0 ].y = studiobbox->bbmax.y * .75f; 
					points[ 0 ].z = ( studiobbox->bbmin.z + studiobbox->bbmax.z ) * .5f;

					if( g_CVars.Aimbot.HitboxMode == 2 ) points[ 0 ] += Vector( 0, .9f, .5f );
				}
				else if( ( flPitch >= -91.f ) && ( flPitch <= -50.f ) ) points[ 0 ].z -= 1.f;
			}
			else if( g_CVars.Aimbot.HitboxMode == 4 )
			{
				Vector a = ( ( points[ 3 ] + points[ 5 ] ) * .5f );

				if( ( flPitch > 50.f ) && ( flPitch < 91.f ) )
				{
					Vector b = ( ( ( a - points[ 0 ] ) / 3 ) * 4 );
					Vector c = ( points[ 0 ] + ( b * .7f ) );
					points[ 0 ] = c;
				}
				else if( ( flPitch >= -91.f ) && ( flPitch <= -50.f ) ) points[ 0 ].z -= 1.f;
			}
		}
	}
	else points[ 0 ] += points[ 0 ] * .5f;

	for( int index = 0; index <= 8; ++index ) VectorTransform( points[ index ], matrix[ studiobbox->bone ], vecCorners[ index ] );

	if( g_CVars.Aimbot.Interpolation.LagPrediction ) g_Stuff.ApplyTickRecord( Entity, &pBackupData[ Entity->entindex( ) ] ); 
}

bool BoneFilter( int bone )
{
	if( bone > 18 && bone < 28 ) return false; 
	else if( bone > 31 && bone < 41 ) return false;
	else return true; 
}

bool Aimbot::GetBone( int iBone, BasePlayer* Target, Vector& vBonePos )
{
	static matrix3x4_t matrix[ 128 ];

	if( !Target->SetupBones( matrix, 128, 0x100, Target->m_flSimulationTime( ) ) ) return false;

	vBonePos.x = matrix[ iBone ][ 0 ][ 3 ];
	vBonePos.y = matrix[ iBone ][ 1 ][ 3 ];
	vBonePos.z = matrix[ iBone ][ 2 ][ 3 ];

	return true;
}

int GetPlayerModifiedDamage( const float &constdamage, bool isHeadshot, bool isFriendly, bool hasHelmet, CSWeapon* Weapon, BaseEntity *targetEntity )
{
	WeaponInfo WeaponInfo = g_NoSpread.GetWeaponInfo( Weapon );

	float damage = constdamage;
	if( isFriendly ) damage *= .35f;

	int armor = targetEntity->m_ArmorValue( );
	if( ( armor > 0 ) && ( !isHeadshot || ( isHeadshot && hasHelmet ) ) )
	{
		float weaponArmorRatio = ( .5f * WeaponInfo.ArmorRatio );

		float newdamage = ( weaponArmorRatio * damage );
		float armordamage = ( ( damage - newdamage ) * .5f );

		if( armordamage <= ( float )armor )
		{
			armordamage = floor( armordamage );
		}
		else
		{
			newdamage = ( damage + ( ( float )armor * -2.f ) );
			armordamage = ( int )armor;
		}

		damage = floor( newdamage );
	}
	else damage = floor( damage );
	return ( int )damage;
}

float GetHitgroupModifiedDamage( float dmg, int hitgroup )
{
	static float hitgroupModifiers[ ] = { 1.f, 4.f, 1.f, 1.25f, 1.f, 1.f, .75f, .75f };
	return( dmg * hitgroupModifiers[ hitgroup ] );
}

int Aimbot::GetTotalDamage( BaseEntity* LocalPlayer, CSWeapon* Weapon, BaseEntity** ppPlayerHit )
{
	if( !LocalPlayer ) return -1;

	trace_t traceData, wallTraceData;
	Ray_t ray;

	WeaponInfo WeaponInfo = g_NoSpread.GetWeaponInfo( Weapon );

	int currentPenetration = WeaponInfo.Penetration;
	float currentPenetrationPower = WeaponInfo.PenetrationPower;
	float currentDamage = ( float )WeaponInfo.Damage;
	float currentMaxRange = WeaponInfo.MaxRange;

	Vector start = EyePosition, wall;
	Vector end;
	float tracedDistance = 0.f;
	float multiplier = 24.f;
	BaseEntity *skipPlayer = 0;
	BaseEntity *tmp = 0;
	TraceFilterSkipTwoEntities TraceFilter( LocalPlayer, skipPlayer );
	int totalDamage = 0;
	float wallThickness;
	bool isGrate;
	int material;

	float penetrationPowerModifier = 1.f;
	float damageModifier = .99f;

	Vector clip;
	static ConVar* mp_friendlyfire = g_pCvar->FindVar( /*mp_friendlyfire*/XorStr<0x7A,16,0x24CED9A4>("\x17\x0B\x23\x1B\x0C\x16\xE5\xEF\xE6\xEF\xFD\xE3\xEF\xF5\xED"+0x24CED9A4).s );
	float tmpDistance;

	while( true )
	{
		end = ( start + ( vecDirection * currentMaxRange ) );
		ray.Init( start, end );
		g_pEngineTrace->TraceRay( ray, 0x4600400B, ( ITraceFilter* )&TraceFilter, &traceData );
		clip = ( end + ( vecDirection * 40.0f ) );
		g_Stuff.ClipTraceToPlayers( start, clip, 0x4600400B, &TraceFilter, &traceData );
		tmp = traceData.m_pEnt;

		if( tmp && tmp->entindex( ) > 0 && tmp->entindex( ) <= g_pGlobals->maxClients ) 
			skipPlayer = tmp;
		else 
			skipPlayer = 0;

		if( traceData.fraction == 1.f ) break;
		
		tmpDistance = ( tracedDistance + ( currentMaxRange * traceData.fraction ) );
		currentDamage *= pow( WeaponInfo.RangeModifier, ( tmpDistance * .002f ) );

		if( skipPlayer )
		{
			if( ( g_CVars.Aimbot.FriendlyFire && ( skipPlayer->m_iTeamNum( ) == LocalPlayer->m_iTeamNum( ) ) ) || ( skipPlayer->m_iTeamNum( ) != LocalPlayer->m_iTeamNum( ) ) )
			{
				totalDamage += GetPlayerModifiedDamage( GetHitgroupModifiedDamage( currentDamage, traceData.hitgroup ),
					( traceData.hitgroup == 1 ), 
					( skipPlayer->m_iTeamNum( ) == LocalPlayer->m_iTeamNum( ) ), 
					skipPlayer->m_bHasHelmet( ), 
					Weapon, 
					skipPlayer );

				if( ppPlayerHit && !*ppPlayerHit ) *ppPlayerHit = skipPlayer;
			}
		}

		isGrate = ( traceData.contents & CONTENTS_GRATE );
		material = ( int )g_pPhysicsSurfaceProps->GetSurfaceData( traceData.surface.surfaceProps )->game.material;

		if( !isGrate ) Weapon->GetMaterialParameters( material, penetrationPowerModifier, damageModifier );
		if( tmpDistance > WeaponInfo.PenetrationRange ) currentPenetration = ( currentPenetration <= 0 ) ? currentPenetration : 0;
		if( ( currentPenetration < 0 ) || ( ( currentPenetration == 0 ) && !isGrate ) ) break;

		while( true )
		{
			multiplier += 24.f;
			wall = ( traceData.endpos + ( vecDirection * multiplier ) );
			if( !( g_pEngineTrace->GetPointContents( ( traceData.endpos + ( vecDirection * multiplier ) ), 0 ) & 0x200400B ) ) break;
			if( multiplier > 128.f )
			{
				multiplier = -1.f;
				break;
			}
		}

		if( multiplier == -1.f ) break;

		ray.Init( wall, traceData.endpos );
		g_pEngineTrace->TraceRay( ray, 0x4600400B, 0, &wallTraceData );

		if( wallTraceData.m_pEnt && ( wallTraceData.m_pEnt != traceData.m_pEnt ) )
		{
			g_Stuff.UTIL_TraceLine( wall, traceData.endpos, 0x4600400B, wallTraceData.m_pEnt, 0, &wallTraceData );
		}

		wallThickness = ( wallTraceData.endpos - traceData.endpos ).Length( );

		if( ( material == ( int )g_pPhysicsSurfaceProps->GetSurfaceData( wallTraceData.surface.surfaceProps )->game.material ) && ( ( material == 'W' ) || ( material == 'M' ) ) ) penetrationPowerModifier += penetrationPowerModifier;
		if( wallThickness > ( currentPenetrationPower * penetrationPowerModifier ) ) break;

		currentPenetrationPower -= ( wallThickness / penetrationPowerModifier );
		tracedDistance = ( tmpDistance + wallThickness );
		start = wallTraceData.endpos;
		currentMaxRange = ( ( currentMaxRange - tracedDistance ) * .5f );
		currentDamage *= damageModifier;
		currentPenetration--;
	}

	if( totalDamage == 0 ) totalDamage = -1;
	return totalDamage;
}

void Aimbot::Reset( )
{
	Distance = INT_MAX;
	Temp = INT_MAX;
	TargetIndex = -1;
	vecDirection.Init( 0, 0, 0 );
	for( int i = 0; i <= 8; ++i ) vecCorners[ i ].Init( 0, 0, 0 );
	IsAimbotting = false;
	qFinalAngle = QAngle( 0, 0, 0 );
}

int next_shot;
int Rate( BasePlayer* LocalPlayer, BasePlayer* Ent )
{
	int rate = 0;

	if( g_CVars.Aimbot.TargetSelection == 0 ) rate = LocalPlayer->GetAbsOrigin( ).DistTo( Ent->GetAbsOrigin( ) ); // distance
	if( g_CVars.Aimbot.TargetSelection == 1 ) rate = Ent->m_iHealth( ); // health
	if( g_CVars.Aimbot.TargetSelection == 2 || g_CVars.Aimbot.TargetSelection == 3 ) rate = Ent->entindex( ) > next_shot ? 0 : 1; // next shot, random

	return rate;
}

void Aimbot::Main( CUserCmd* pCmd, BasePlayer* LocalPlayer )
{
	CSWeapon* Weapon = ( CSWeapon* ) LocalPlayer->GetActiveBaseCombatWeapon( );
	if( !Weapon || !Weapon->IsWeapon( ) ) return;

	WeaponInfo wpnInfo = g_NoSpread.GetWeaponInfo( Weapon );

	Reset( );

	static int iSpot;
	static int Choose[ ] = { 12, 11, 5, 0, 1, 9, 10, 13, 14, 16, 17, 18, 8, 7, 6, 4, 3, 2, 15 };

	int m_iWeaponID = Weapon->GetWeaponID( );

	if( Weapon->GetWeaponID( ) == 17 )
	{
		if( g_CVars.Aimbot.BodyAWP ) iSpot = 10;
		else iSpot = g_CVars.Aimbot.Hitbox;
	}
	else iSpot = g_CVars.Aimbot.Hitbox;

    Choose[ 0 ] = iSpot;
 
    for( int i = 18; i >= 1; i-- )
    {
		if( Choose[ i ] == iSpot ) Choose[ i ] = g_CVars.Aimbot.Hitbox;
    }

	if( g_CVars.Aimbot.Key > 0 )
	{
		if( !GetAsyncKeyState( g_CVars.Aimbot.Key ) ) return;
	}

	for( auto i = g_pGlobals->maxClients; i >= 1; --i )
	{
		if( i == g_pEngineClient->GetLocalPlayer( ) ) continue;
		BasePlayer* Ent = ( BasePlayer* ) g_pClientEntityList->GetClientEntity( i );
		if( Ent == 0 ) continue;
		if( Ent->IsDormant( ) ) continue;
		if( Ent->m_lifeState( ) != 0 ) continue;

		if( !g_CVars.Aimbot.FriendlyFire )
		{
			if( Ent->m_iTeamNum( ) == LocalPlayer->m_iTeamNum( ) ) continue;
		}

		if( Ent->m_iHealth( ) > 500 ) continue;
		if( Ent->IsSpawnProtectedPlayer( ) ) continue;
		if( g_CVars.PlayerList.Friend[ i ] ) continue;
		if( Ent->m_vecOrigin( ).DistTo( EyePosition ) > wpnInfo.MaxRange ) continue;
		if( g_Whitelist.List( i ) ) iSpot = 12;
		int rate = Rate( LocalPlayer, Ent );
		if( rate > Temp ) continue;

		if( Weapon->GetWeaponID( ) == 17 ) // awp
		{
			// todo: fix issue with awp not hitting shit while backtracking is on
			
			GetHitbox( iSpot, Ent );
			
			if( CheckVisible( EyePosition, vecCorners[ 0 ], Ent, LocalPlayer ) )
			{
				VectorSubtract( vecCorners[ 0 ], EyePosition, vecDirection );
				VectorNormalizeFast( vecDirection );

				if( g_Stuff.IsReadyToShoot( LocalPlayer, Weapon ) )
				{
					VectorAngles( vecDirection, pCmd->viewangles );
					IsAimbotting = true;
				}

				TargetIndex = i;
				Temp = rate;
			}
		}
		else
		{
			if( g_CVars.Aimbot.MultiSpot )
			{
				if( g_CVars.Aimbot.HitScan )
				{
					for( int m_iHitbox = 18; m_iHitbox >= 0; m_iHitbox-- )
					{
						GetHitbox( Choose[ m_iHitbox ], Ent );						

						for( int m_iCorners = 8; m_iCorners > 0; m_iCorners-- )
						{
							VectorSubtract( vecCorners[ m_iCorners ], EyePosition, vecDirection );
							VectorNormalizeFast( vecDirection );

							if( CheckVisibleAWallCheck( EyePosition, vecCorners[ m_iCorners ], Ent, LocalPlayer ) )
							{
								if( g_Stuff.IsReadyToShoot( LocalPlayer, Weapon ) )
								{
									VectorAngles( vecDirection, pCmd->viewangles );
									IsAimbotting = true;
								}

								TargetIndex = i;
								Temp = rate;
							}
						}
					}

					for( int m_iHitbox = 18; m_iHitbox >= 0; m_iHitbox-- )
					{
						GetHitbox( Choose[ m_iHitbox ], Ent );
						VectorSubtract( vecCorners[ 0 ], EyePosition, vecDirection );
						VectorNormalizeFast( vecDirection );

						if( CheckVisibleAWallCheck( EyePosition, vecCorners[ 0 ], Ent, LocalPlayer ) )
						{
							if( g_Stuff.IsReadyToShoot( LocalPlayer, Weapon ) )
							{
								VectorAngles( vecDirection, pCmd->viewangles );
								IsAimbotting = true;
							}

							TargetIndex = i;
							Temp = rate;
						}
					}
				}
				else
				{
					GetHitbox( Choose[ 0 ], Ent );

					for( int m_iCorners = 8; m_iCorners > 0; m_iCorners-- )
					{
						VectorSubtract( vecCorners[ m_iCorners ], EyePosition, vecDirection );
						VectorNormalizeFast( vecDirection );

						if( CheckVisibleAWallCheck( EyePosition, vecCorners[ m_iCorners ], Ent, LocalPlayer ) )
						{
							if( g_Stuff.IsReadyToShoot( LocalPlayer, Weapon ) )
							{
								VectorAngles( vecDirection, pCmd->viewangles );
								IsAimbotting = true;
							}

							TargetIndex = i;
							Temp = rate;
						}
					}

					VectorSubtract( vecCorners[ 0 ], EyePosition, vecDirection );
					VectorNormalizeFast( vecDirection );

					if( CheckVisibleAWallCheck( EyePosition, vecCorners[ 0 ], Ent, LocalPlayer ) )
					{
						if( g_Stuff.IsReadyToShoot( LocalPlayer, Weapon ) )
						{
							VectorAngles( vecDirection, pCmd->viewangles );
							IsAimbotting = true;
						}

						TargetIndex = i;
						Temp = rate;
					}
				}
			}
			else
			{
				if( g_CVars.Aimbot.HitScan )
				{
					for( int m_iHitbox = 18; m_iHitbox >= 0; m_iHitbox-- )
					{
						GetHitbox( Choose[ m_iHitbox ], Ent );
						VectorSubtract( vecCorners[ 0 ], EyePosition, vecDirection );
						VectorNormalizeFast( vecDirection );

						if( CheckVisibleAWallCheck( EyePosition, vecCorners[ 0 ], Ent, LocalPlayer ) )
						{
							if( g_Stuff.IsReadyToShoot( LocalPlayer, Weapon ) )
							{
								VectorAngles( vecDirection, pCmd->viewangles );
								IsAimbotting = true;
							}

							TargetIndex = i;
							Temp = rate;
						}
					}
				}
				else
				{
					GetHitbox( Choose[ 0 ], Ent );
					VectorSubtract( vecCorners[ 0 ], EyePosition, vecDirection );
					VectorNormalizeFast( vecDirection );

					if( CheckVisibleAWallCheck( EyePosition, vecCorners[ 0 ], Ent, LocalPlayer ) )
					{
						if( g_Stuff.IsReadyToShoot( LocalPlayer, Weapon ) )
						{
							VectorAngles( vecDirection, pCmd->viewangles );
							IsAimbotting = true;
						}

						TargetIndex = i;
						Temp = rate;
					}
				}
			}
		}
	}

	if( IsAimbotting && TargetIndex != -1 )
	{
		if( g_CVars.Aimbot.AutoShoot ) pCmd->buttons |= IN_ATTACK;
	}

	if( g_CVars.Aimbot.TargetSelection == 3 ) next_shot = TargetIndex;

	if( IsAimbotting )
	{
		if( g_CVars.Aimbot.TargetSelection != 3 ) next_shot = TargetIndex;
	}
	else if( Weapon->ShouldReload( ) ) pCmd->buttons |= IN_RELOAD;

	if( !g_CVars.Aimbot.Silent ) g_pEngineClient->SetViewAngles( pCmd->viewangles );
}