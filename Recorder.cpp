#include "Main.h"
#include "Recorder.h"

CMovementRecorder MovementRecorder;

CMovementRecorder::CMovementRecorder( )
{
	Ticks = 0;
	bFindStart = false;
	FindStart = 1;

	Movements = new CRecord[ MaxRecordTicks ];
	DrawPath = new Vector[ MaxRecordTicks ];
	TempCmd = new SRecord[ MaxRecordTicks ];

	State = NOTHING;
	AutoPlayer = false;
}

std::string szDirFileDemosDll( const char* pszName )
{
	char appdata[ 0xFF ];
	strcpy( appdata, /*C:\\*/XorStr<0x5E,4,0x2C453A01>("\x1D\x65\x3C"+0x2C453A01).s ); //m_pszDllPath );	
	strcat( appdata, /*\\Demos\\*/XorStr<0x8C,8,0xB5FB852C>("\xD0\xC9\xEB\xE2\xFF\xE2\xCE"+0xB5FB852C).s );
	strcat( appdata, pszName );
	puts( appdata );

	return appdata;
}

float GetSpeedByDistance( float distance )
{
	if( distance > 8.5 ) return 250;
	if( distance > 5.5 ) return 100;
	if( distance > 3.5 ) return 70;
	if( distance > .5 ) return 30;
	return 20;
}

void NormalizeAngles( QAngle &output )
{
	for( int i = 0; i < 3; i++ )
	{
		if( output[ i ] > 180.f ) output[ i ] -= 360.f;
		if( output[ i ] < -180.f ) output[ i ] += 360.f;
	}
}

void CMovementRecorder::SmootherAngles( BasePlayer* LocalPlayer )
{
	if( State != PLAYING ) return;

	if( g_CVars.MovementRecorder.setangleyinm && !( g_CVars.MovementRecorder.angle_y_in_m_equal ) )
	{
		QAngle Angle = Movements[ Ticks + 1 ].viewangles;
		QAngle norm;
		norm.x = g_Stuff.GuwopNormalize( Angle.x );
		norm.y = g_Stuff.GuwopNormalize( Angle.y );
		norm.z = g_Stuff.GuwopNormalize( Angle.z );

		static QAngle Interpolated;
		//InterpolateAngles( Interpolated, norm, Interpolated, 1.0f - ConVars.correctangle_inm->GetFloat( ) );
		NormalizeAngles( Interpolated );

		QAngle FirstSet = Movements[ Ticks ].viewangles;
		{
			QAngle Set = norm - QAngle( 0.0f, g_CVars.MovementRecorder.angle_y_in_m, 0.0f );
			float Angle = g_Stuff.GuwopNormalize( g_CVars.MovementRecorder.angle_y_in_m );
			if( ( Angle > 90.0f || Angle < -90.0f ) && g_CVars.MovementRecorder.surf_style ) Set.x = 89.0f;

			g_pPrediction->SetViewAngles( Set );
			g_pPrediction->SetLocalViewAngles( Set );
			g_pEngineClient->SetViewAngles( Set );
			Interpolated = Interpolated;
		}
	}
}

void CMovementRecorder::RecordMovement( CUserCmd* pCmd, BasePlayer* LocalPlayer, QAngle viewangles )
{
	static bool init[ 3 ];
	QAngle OldAngleBeforeR = pCmd->viewangles;
	int OldButtons = pCmd->buttons;

	if( g_Macro.Save )
	{
		g_Macro.SaveMacro( Movements, DrawPath, TickEnd, szDirFileDemosDll( g_Macro.CurrentName ).c_str( ) );
		g_Macro.Save = false;
	}

	if( g_Macro.Load )
	{
		g_Macro.ReadMacro( Movements, DrawPath, TickEnd, szDirFileDemosDll( g_Macro.CurrentName ).c_str( ) );
		g_Macro.Load = false;
	}

	if( g_Macro.Load2 )
	{
		g_Macro.ReadMacro2( TempCmd, TickEnd, DrawPath[ 0 ], szDirFileDemosDll( g_Macro.CurrentName ).c_str( ) );
		for( int i = 0; i < MaxRecordTicks; i++ )
		{
			Movements[ i ].buttons = TempCmd[ i ].buttons;
			Movements[ i ].upmove = TempCmd[ i ].up;
			Movements[ i ].forwardmove = TempCmd[ i ].forward;
			Movements[ i ].sidemove = TempCmd[ i ].side;
			Movements[ i ].viewangles = TempCmd[ i ].view;
		}
		g_Macro.Load2 = false;
	}

	if( State == STARTPOS )
	{
		bFindStart = true;
		FindStart = 1;
	}

	if( bFindStart )
	{
		static bool doonce = false;
		static int dooncetimer = 0;
		if( FindStart == 1 )
		{
			Vector MyPos = LocalPlayer->GetAbsOrigin( );
			if( ( MyPos.x <= ( DrawPath[ 0 ].x + 250 ) ) && ( MyPos.x >= ( DrawPath[ 0 ].x - 250 ) ) && ( MyPos.y <= ( DrawPath[ 0 ].y + 250 ) ) && ( MyPos.y >= ( DrawPath[ 0 ].y - 250 ) ) )
			{
				FindStart = 2;
				dooncetimer = 0;
				doonce = true;
			}
			else
			{
				dooncetimer++;
				if( doonce )
				{
					//g_pEngineClient->ClientCmd( "say !tele" );
					doonce = false;
				}
				if( dooncetimer == 150 )
				{
					FindStart = 0;
					dooncetimer = 0;
					doonce = true;
				}
			}
		}

		if( FindStart == 2 )
		{
			static QAngle qCurrentView; 
			static QAngle qDelta;
			g_pEngineClient->GetViewAngles( qCurrentView );
			qDelta = Movements[ 0 ].viewangles - qCurrentView;

			if( qDelta[ 0 ] > 180.f ) qDelta[ 0 ] -= 360.f;
			if( qDelta[ 1 ] > 180.f ) qDelta[ 1 ] -= 360.f;
			if( qDelta[ 0 ] < -180.f ) qDelta[ 0 ] += 360.f;
			if( qDelta[ 1 ] < -180.f ) qDelta[ 1 ] += 360.f;
			 
			viewangles = qCurrentView + qDelta / 20.f;

			if( viewangles[ 0 ] >  180.f ) viewangles[ 0 ] -= 360.f;
			if( viewangles[ 1 ] >  180.f ) viewangles[ 1 ] -= 360.f;
			if( viewangles[ 0 ] < -180.f ) viewangles[ 0 ] += 360.f;
			if( viewangles[ 1 ] < -180.f ) viewangles[ 1 ] += 360.f;

			g_pEngineClient->SetViewAngles( viewangles );

			Vector MyPos = LocalPlayer->GetAbsOrigin( );
			QAngle AimAngle;
			VectorAngles( DrawPath[ 0 ] - MyPos, AimAngle );
			AimAngle.z = 0;

			Vector vDeltaOrigin = DrawPath[ 0 ] - MyPos;
			float distance = sqrtf( vDeltaOrigin.Length( ) );
			pCmd->forwardmove = GetSpeedByDistance( distance );

			if( pCmd->forwardmove < 51 ) pCmd->buttons |= IN_SPEED;
			pCmd->sidemove = 0;

			Vector Direction( pCmd->forwardmove, pCmd->sidemove, pCmd->upmove );
			float Velocity = Direction.Length( );
			QAngle Angles;
			VectorAngles(Direction, Angles);
			float delta = g_Stuff.GuwopNormalize( viewangles.y - AimAngle.y );
			float yaw = DEG2RAD( g_Stuff.GuwopNormalize( delta + Angles.y ) );

			pCmd->forwardmove = ( cosf( yaw ) * Velocity );
			pCmd->sidemove = ( sinf( yaw ) * Velocity );

			if( ( MyPos.x <= ( DrawPath[ 0 ].x + 0.01 ) ) && ( MyPos.x >= ( DrawPath[ 0 ].x - 0.01 ) ) && ( MyPos.y <= ( DrawPath[ 0 ].y + 0.01 ) ) && ( MyPos.y >= ( DrawPath[ 0 ].y - 0.01 ) ) )
			{
				Vector tPlayerVelocity = LocalPlayer->GetAbsVelocity( );
				float PlayerVelocity = tPlayerVelocity.Length( );
				if( PlayerVelocity <= 5 )
				{
					if( qDelta.x < 0.2f && qDelta.x > -0.2f && qDelta.y < 0.2f && qDelta.y > -0.2f )
					{
						State = PLAYING;
						bFindStart = false;
					}
					else
						FindStart = 3;
				}
			}
		}

		if( FindStart == 3 )
		{
			static QAngle qCurrentView;
			g_pEngineClient->GetViewAngles( qCurrentView );
			QAngle qDelta = Movements[ 0 ].viewangles - qCurrentView;

			if( qDelta[ 0 ] > 180.f ) qDelta[ 0 ] -= 360.f;
			if( qDelta[ 1 ] > 180.f ) qDelta[ 1 ] -= 360.f;
			if( qDelta[ 0 ] < -180.f ) qDelta[ 0 ] += 360.f;
			if( qDelta[ 1 ] < -180.f ) qDelta[ 1 ] += 360.f;
			 
			viewangles = qCurrentView + qDelta / 20.f;

			if( viewangles[ 0 ] > 180.f ) viewangles[ 0 ] -= 360.f;
			if( viewangles[ 1 ] > 180.f ) viewangles[ 1 ] -= 360.f;
			if( viewangles[ 0 ] < -180.f ) viewangles[ 0 ] += 360.f;
			if( viewangles[ 1 ] < -180.f ) viewangles[ 1 ] += 360.f;

			g_pEngineClient->SetViewAngles( viewangles );

			if( qDelta.x < 0.2f && qDelta.x > -0.2f && qDelta.y < 0.2f && qDelta.y > -0.2f )
			{
				State = PLAYING;
				bFindStart = false;				
			}
		}
	}

	if( State == RECORDING )
	{
		if( !init[ 0 ] )
		{
			bFindStart = false;
			if( g_CVars.MovementRecorder.rerecord < 1 ) Ticks = 0;
			init[ 0 ] = true;
		}

		DrawPath[ Ticks ] = LocalPlayer->GetAbsOrigin( );

		Movements[ Ticks ].buttons = pCmd->buttons;
		Movements[ Ticks ].upmove = pCmd->upmove;
		Movements[ Ticks ].sidemove = pCmd->sidemove;
		Movements[ Ticks ].forwardmove = pCmd->forwardmove;
		Movements[ Ticks ].viewangles = viewangles;
		Movements[ Ticks ].weaponsubtype = pCmd->weaponsubtype;
		Movements[ Ticks ].weaponselect = pCmd->weaponselect;

		TickEnd = Ticks;

		++Ticks;
	}
	else
		init[ 0 ] = false;

	if( State == PLAYING )
	{
		if( !init[ 1 ] )
		{
			Ticks = 0;
			bFindStart = false;
			init[ 1 ] = true;
		}

		if( g_CVars.MovementRecorder.rerecord > 0 )
		{
			if( Ticks >= g_CVars.MovementRecorder.rerecord ) State = RECORDING;
		}

		if( ( Ticks >= TickEnd ) && AutoPlayer ) State = STARTPOS;
		if( ( Ticks >= TickEnd ) && !AutoPlayer ) State = NOTHING;

		//DrawPath[ Ticks ] = LocalPlayer->GetAbsOrigin( );

		pCmd->buttons = Movements[ Ticks ].buttons;
		pCmd->upmove = Movements[ Ticks ].upmove;
		pCmd->sidemove = Movements[ Ticks ].sidemove;
		pCmd->forwardmove = Movements[ Ticks ].forwardmove;
		viewangles = Movements[ Ticks ].viewangles;
		pCmd->weaponsubtype = Movements[ Ticks ].weaponsubtype;
		pCmd->weaponselect = Movements[ Ticks ].weaponselect;

		Vector vecMove( ( float )pCmd->forwardmove, ( float )pCmd->sidemove, ( float )pCmd->upmove );
		float speed = ( float )sqrtf( vecMove.x * vecMove.x + vecMove.y * vecMove.y );
		QAngle angMove, qRealView( viewangles );
		VectorAngles( vecMove, angMove );
		angMove = QAngle( ( float ) angMove.x, ( float ) angMove.y, 0.0f );
		QAngle First;

		viewangles.y -= g_CVars.MovementRecorder.angle_y_in_m;

		float Angle = g_Stuff.GuwopNormalize( g_CVars.MovementRecorder.angle_y_in_m );
		if( ( Angle > 90.0f || Angle < -90.0f ) && g_CVars.MovementRecorder.surf_style ) viewangles.x = 89.0f;

		if( g_CVars.MovementRecorder.angle_y_in_m_equal ) viewangles = OldAngleBeforeR;

		NormalizeAngles( viewangles );
		g_pEngineClient->SetViewAngles( viewangles );

		float yaw = ( float )DEG2RAD( ( float )g_Stuff.GuwopNormalize( ( float )g_Stuff.GuwopNormalize( viewangles.y - qRealView.y ) + angMove.y ) );
		pCmd->forwardmove = ( float )cosf( yaw ) * speed;
		pCmd->sidemove = ( float )sinf( yaw ) * speed;

		++Ticks;
	}
	else
		init[ 1 ] = false;

	if( State == NOTHING )
	{
		if( !init[ 2 ] )
		{
			Ticks = 0;
			bFindStart = false;
			init[ 2 ] = true;
		}

	}
	else
		init[ 2 ] = false;

	if( State != PLAYING && State != RECORDING ) g_CVars.MovementRecorder.rerecord = 0;
}