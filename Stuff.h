#ifndef __STUFF_H__
#define __STUFF_H_

class CVars
{
public:
	void Init( );
	class Menu
	{
	public:
		int x, y, w, h;
	};

	class Radar
	{
	public:
		int x, y, w, h;
	};

	class ColorSelector
	{
	public:
		int x, y, w, h;
		int Entity, Mode, Element;

		class ESP
		{
		public:
			Color CT, TT, Wpn;
		};

		class Chams
		{
		public:
			Color CTVis, TTVis, CTInvis, TTInvis, WpnVis, WpnInvis, CTOutline, TTOutline, WpnOutline;
		};

		int CurrentColor[ 2 ][ 3 ][ 3 ][ 4 ];

		ESP ESP;
		Chams Chams;
	};

	class Aimbot
	{
	public:
		bool Active, AutoShoot, AutoWall, MultiSpot, HitScan, FriendlyFire, Silent, PerfectSilent, AntiSMAC, BodyAWP, SnapLimiter;
		int TargetSelection, Hitbox, HitboxMode, Height, AngleLimit, MinDamage, Key, AutoHeightMode[ 64 ];
		float AngleLimitTens, PointScale;

		class Resolver
		{
		public:
			bool Active, Smart, State[ 64 ], LastState[ 64 ];
			int Mode, Type;
		};
		Resolver Resolver;

		class Interpolation
		{
		public:
			int LagPrediction;
		};
		Interpolation Interpolation;
	};

	class Triggerbot
	{
	public:
		bool Active, Seed, IsShooting, Spread, Recoil;
		int Strength, Key, Hitbox;
	};

	class Accuracy
	{
	public:
		bool ForceSeed, PerfectAccuracy;
		int NoSpreadMode;
	};

	class Visuals
	{
	public:
		class ESP
		{
		public:
			bool Box, Name, Health, Weapon, Bone, AimSpot, Hit, Ground, EnemyOnly;
		};

		class Chams
		{
		public:
			bool Active, Weapons, Shadows, Outline, HandsOutline, EnemyOnly;
		};

		class Crosshair
		{
		public:
			int Type;
			bool Dynamic;
		};

		float ASUS;
		bool Radar, NoSky, NoHands, NoSmoke, NoFlash, NoVisualRecoil;

		ESP ESP;
		Chams Chams;
		Crosshair Crosshair;
		
	};

	class Miscellaneous
	{
	public:
		class AntiAim
		{
		public:
			bool Active, Static, WallDetection, DuckInAir, TurnOff, AtTargets;
			int Pitch, Yaw, Variation, DuckPitch, DuckYaw, DuckVariation, WallDetectionMode;
			float RealValue, FakeValue;
		};

		class Fakelag
		{
		public:
			bool Active, InAttack, AirOnly;
			int Mode, Value;
		};

		bool BunnyHop, AutoStrafe, CircleStrafe, EdgeJump, Speedhack, OriginCorrection, AutoKnife, RoundSay, CheatsBypass, AirStuck, AirStuckPress, ThirdPerson, Save, Load;
		int SpeedhackValue;

		AntiAim AntiAim;
		Fakelag Fakelag;
	};

	class PlayerList
	{
	public:
		int Index, Pitch[ 64 ], Yaw[ 64 ];
		bool Friend[ 64 ], Jitter[ 64 ];
		QAngle ViewAngles[ 64 ];
	};

	class Colors
	{
	public:
		int Scheme;

		Color gui_fill;
		Color gui_fill2;
		Color gui_outline;
		Color gui_outline2;
		Color gui_sections;
		Color inside_fill;
		Color inside_outline;

		Color tabs_fill;
		Color tabs_outline;

		Color radar_fill;
		Color radar_fill2;
		Color radar_outline;
		Color radar_outline2;
		Color radar_inside_fill;
		Color radar_inside_outline;
		Color radar_separator;

		Color maincolor;
		Color maincolorfade;
		Color mouseoutline;
	};

	class MovementRecorder
	{
	public:
		bool Active, angle_y_in_m_equal, surf_style, setangleyinm;
		float angle_y_in_m;
		int rerecord;
	};

	Menu Menu;
	Radar Radar;
	ColorSelector ColorSelector;
	Aimbot Aimbot;
	Accuracy Accuracy;
	Triggerbot Triggerbot;
	Visuals Visuals;
	Miscellaneous Miscellaneous;
	PlayerList PlayerList;
	Colors Colors;
	MovementRecorder MovementRecorder;
};
extern CVars g_CVars;

enum InvalidatePhysicsBits_t
{
	POSITION_CHANGED	= 0x1,
	ANGLES_CHANGED		= 0x2,
	VELOCITY_CHANGED	= 0x4,
	ANIMATION_CHANGED	= 0x8,
};

class CTickRecord
{
public:
	CTickRecord( ){
		Reset( );
	}

	~CTickRecord( ) {
		Reset( );
	}

	CTickRecord& operator = ( CTickRecord &v )
	{
		m_Origin = v.m_Origin;
		m_Velocity = v.m_Velocity;
		m_Mins = v.m_Mins;
		m_Maxs = v.m_Maxs;

		m_EyeAngles = v.m_EyeAngles;

		m_SimulationTime = v.m_SimulationTime;
		m_Cycle = v.m_Cycle;

		for( int i = 0; i < 24; i++ ) m_PoseParameter[ i ] = v.m_PoseParameter[ i ];
		for( int i = 0; i < 4; i++ ) m_EncodedController[ i ] = v.m_EncodedController[ i ];
		for( int i = 0; i < 64; i++ ) m_flexWeight[ i ] = v.m_flexWeight[ i ];
		for( int i = 0; i < 15; i++ ) m_AnimationLayer[ i ] = v.m_AnimationLayer[ i ];

		m_Sequence = v.m_Sequence;
		m_Flags = v.m_Flags;
		return *this;
	}

	void Reset( )
	{
		m_Origin = Vector( 0, 0, 0 );
		m_Velocity = Vector( 0, 0, 0 );
		m_Mins = Vector( 0, 0, 0 );
		m_Maxs = Vector( 0, 0, 0 );

		m_EyeAngles = QAngle( 0, 0, 0 );

		m_SimulationTime = 0.f;
		m_Cycle = 0.f;

		for( int i = 0; i < 24; i++ ) m_PoseParameter[ i ] = 0.f;
		for( int i = 0; i < 4; i++ ) m_EncodedController[ i ] = 0.f;
		for( int i = 0; i < 64; i++ ) m_flexWeight[ i ] = 0.f;
		for( int i = 0; i < 15; i++ ) m_AnimationLayer[ i ] = C_AnimationLayer( );

		m_Sequence = 0;
		m_Flags = 0;
	}

	Vector m_Origin, m_Velocity, m_Mins, m_Maxs;
	float m_SimulationTime, m_Cycle;
	int m_Sequence, m_Flags;
	QAngle m_EyeAngles;
	float m_PoseParameter[ 24 ], m_EncodedController[ 4 ], m_flexWeight[ 64 ];
	C_AnimationLayer m_AnimationLayer[ 15 ];
};

extern CTickRecord pPlayerHistory[ 64 ][ 32 ];
extern CTickRecord pSimulationData[ 64 ];
extern CTickRecord pBackupData[ 64 ];

class Stuff
{
public:
	int Ticks[ 64 ];
	bool IsMoving[ 64 ];

	float sidemove_old;
	float forwardmove_old;
	QAngle viewangles_old;
	QAngle radarangles;
	QAngle cmdangles;

	class Mouse
	{
	public:
		void Draw( Color, Color );
		bool IsInBox( int, int, int, int );
		void Wrapper( );
		bool Click( int, int, int, int );
		bool RightClick( int, int, int, int );
		bool Hold( int, int, int, int );
		bool RightHold( int, int, int, int );
		void DragMenu( int&, int&, int, int );
		void DragRadar( int&, int&, int, int );
	};
	Mouse Mouse;

	class MovementFix
	{
	public:
		Vector vMove;
		float flSpeed, flYaw;
		QAngle qMove;
		void FixMove( BasePlayer*, CUserCmd*, bool );
	};
	MovementFix MovementFix;

	class AntiAim
	{
	public:
		QAngle tmp;
		void AtTargets( BasePlayer*, CUserCmd* );
		bool WallDetection( BasePlayer*, CUserCmd*, float );
		void WallDetection2( BasePlayer*, CUserCmd*, bool, float, float );
	};
	AntiAim AntiAim;

	class KnifeBot
	{
	public:
		bool CanKnife( bool, CUserCmd*, BasePlayer*, BasePlayer* );
		void Main( CUserCmd*, BasePlayer* , CSWeapon* );
		int TargetIndex;
	};
	KnifeBot Knifebot;

	float GuwopNormalize( float );
	int Flags;
	void PredictLaggedMovement( BasePlayer* );
	void ForceCVars( );
	bool NextShotPredict( BasePlayer*, CSWeapon* );
	int GetFontIndexByDistance( int );
	void GetWorldSpaceCenter( BasePlayer*, Vector& );
	bool WorldToScreen( const Vector&, Vector& );
	void ForceMaterial( float, float, float, float, IMaterial*, bool, bool );
	IMaterial* CreateMaterial( bool, bool, bool );
	QAngle Clamp( QAngle& );
	float Clamp( float& );
	void ForceSeed( CUserCmd* );
	bool CanHit( Vector, QAngle, Vector, Vector, Vector, float, int, CSWeapon*, BasePlayer*, int );
	void SeedTrigger( CUserCmd*, BasePlayer*, CSWeapon* );
	void NoRecoil( CUserCmd*, BasePlayer*, bool );
	void AutoStrafe( CUserCmd*, BasePlayer* );
	void FixMove( CUserCmd*, BasePlayer* );
	void BunnyHop( CUserCmd*, BasePlayer* );
	void EdgeJump( CUserCmd*, BasePlayer* );
	bool CheckGround( BasePlayer* );
	float __fastcall fastSqrt( float );
	void VectorAngles_( const Vector&, const Vector&, QAngle& );
	void inline SinCos( float, float*, float* );
	void AngleVectors_( const float*, float*, float*, float* );
	void CalculateAngles( Vector, Vector, QAngle& );
	int lerp( int, int, int );
	bool IsReadyToShoot( BasePlayer*, CSWeapon* );
	void TraceFilterSkip2Entities( void*, const BaseEntity*, const BaseEntity*, int );
	void UTIL_TraceLine( const Vector&, const Vector&, unsigned int, const IHandleEntity*, int, trace_t* );
	void UTIL_TraceHull( const Vector&, const Vector&, const Vector&, const Vector&, unsigned int, const IHandleEntity*, int, trace_t* );
	void UTIL_TraceHull2( const Vector&, const Vector&, const Vector&, const Vector&, unsigned int, const IHandleEntity*, int, trace_t* );
	void FindHullIntersection( const Vector&, trace_t&, const Vector&, const Vector&, BaseEntity* );
	bool IsBSPModel( void* );
	void ClipTraceToPlayers( const Vector&, const Vector&, unsigned int, void*, trace_t* );
	void MoveToLastReceivedPosition( BasePlayer*, bool );
	void RemoveFromInterpolationList( BasePlayer* );
	void AddToInterpolationList( BasePlayer* );
	void SetAbsOrigin( BasePlayer*, const Vector& );
	void SetAbsAngles( BasePlayer*, const QAngle& );
	void EstimateAbsVelocity( BasePlayer*, Vector& );
	uintptr_t PatternScan( const std::string&, const std::string& );
	void FixCollision( BasePlayer*, BasePlayer* );
	void ApplyTickRecord( BasePlayer*, CTickRecord* );
	void StoreTickRecord( BasePlayer*, CTickRecord* );
};
extern Stuff g_Stuff;
#endif //__STUFF_H__