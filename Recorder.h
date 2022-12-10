#ifndef __RECORDER_H__
#define __RECORDER_H__

#define MaxRecordTicks 1000000

class CRecord
{
public:

	QAngle	viewangles;     
	float	forwardmove;   
	float	sidemove;      
	float	upmove;         
	int		buttons;		      
	int		weaponselect;	
	int		weaponsubtype;

	CRecord( )
	{
		viewangles.Init( );
		forwardmove = 0.0f;
		sidemove = 0.0f;
		upmove = 0.0f;
		buttons = 0;
		weaponselect = 0;
		weaponsubtype = 0;
	}

	void Reset( )
	{
		viewangles.Init( );
		forwardmove = 0.0f;
		sidemove = 0.0f;
		upmove = 0.0f;
		buttons = 0;
		weaponselect = 0;
		weaponsubtype = 0;
	}
};

struct SRecord
{
	int buttons;
	float forward;
	float side;
	float up;
	QAngle view;
};

class CMovementRecorder
{
public:
	CMovementRecorder( void );

	void RecordMovement( CUserCmd* pCmd, BasePlayer* LocalPlayer, QAngle viewangle );
	CRecord *Movements;
	SRecord *TempCmd;
	int Ticks;
	int State;
	Vector *DrawPath;
	int TickEnd;
	bool AutoPlayer;
	int FindStart;
	bool bFindStart;
	void SmootherAngles( BasePlayer* LocalPlayer );
};

extern CMovementRecorder MovementRecorder;

enum
{
	NOTHING = 0,
	RECORDING = 1,
	PLAYING = 2,
	STARTPOS = 3
};

#endif