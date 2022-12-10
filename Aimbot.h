#ifndef __AIMBOT_H__
#define __AIMBOT_H__

enum Bones_t
{
    BONE_PELVIS,
    BONE_LEFT_THIGH,
    BONE_LEFT_CALF,
    BONE_LEFT_FOOT,
    BONE_LEFT_TOE,
    BONE_RIGHT_THIGH,
    BONE_RIGHT_CALF,
    BONE_RIGHT_FOOT,
    BONE_RIGHT_TOE,
    BONE_SPINE,
    BONE_SPINE1,
    BONE_SPINE3,
    BONE_SPINE4,
    BONE_NECK,
    BONE_HEAD,
    BONE_LEFT_CLAVICLE,
    BONE_LEFT_UPPER_ARM,
    BONE_LEFT_FOREARM,
    BONE_LEFT_HAND,
    BONE_LEFT_FINGER2,
    BONE_LEFT_FINGER21,
    BONE_LEFT_FINGER22,
    BONE_LEFT_FINGER1,
    BONE_LEFT_FINGER11,
    BONE_LEFT_FINGER12,
    BONE_LEFT_FINGER0,
    BONE_LEFT_FINGER01,
    BONE_LEFT_FINGER02,
    BONE_RIGHT_CLAVICLE,
    BONE_RIGHT_UPPER_ARM,
    BONE_RIGHT_FOREARM,
    BONE_RIGHT_HAND,
    BONE_RIGHT_FINGER2,
    BONE_RIGHT_FINGER21,
    BONE_RIGHT_FINGER22,
    BONE_RIGHT_FINGER1,
    BONE_RIGHT_FINGER11,
    BONE_RIGHT_FINGER12,
    BONE_RIGHT_FINGER0,
    BONE_RIGHT_FINGER01,
    BONE_RIGHT_FINGER02,
    BONE_RIGHT_WRIST,
    BONE_LEFT_WRIST,
    BONE_LEFT_ULNA,
    BONE_RIGHT_ULNA,
    BONE_WEAPON_BONE,
    BONE_WEAPON_BONE_RIGHT_HAND,
    BONE_WEAPON_BONE_LEFT_HAND,
    BONE_WEAPON_BONE_CLIP,
    BONE_FORWARD
};

class Aimbot
{
public:
	bool CheckVisible( Vector&, Vector&, BasePlayer*, BasePlayer* );
	bool CheckVisibleAWallCheck( Vector&, Vector&, BasePlayer*, BasePlayer* );
	void GetHitbox( int, BasePlayer* );
	bool GetBone( int, BasePlayer*, Vector& );
	int GetTotalDamage( BaseEntity*, CSWeapon*, BaseEntity** );
	void Reset( );
	void Main( CUserCmd*, BasePlayer* );
	Vector vecDirection, vecFinalDirection, TempDirection;
	Vector vecCorners[ 10 ];
	int Shots[ 64 ];
	int TargetIndex, Temp;
	float Distance;
	bool IsAimbotting;
	QAngle qFinalAngle;
	Vector mins[ 64 ], maxs[ 64 ];
};

extern Aimbot g_Aimbot;

#endif //__AIMBOT_H__