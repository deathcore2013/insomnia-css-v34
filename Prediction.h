#pragma once

#ifndef _PREDICTION_H_
#define _PREDICTION_H_

class Prediction
{
public:
	void Start( CUserCmd*, BasePlayer* );
	void End( CUserCmd*, BasePlayer* );
	void UpdatePlayerHistory( BasePlayer* );
	int m_nOldTickBase, PushTickBase, m_nTickBase;
	float OldFrametime, OldCurtime;
	IMoveHelper* Move;
    QAngle m_punchAngle;
    Vector m_velocity;
};
extern Prediction g_Prediction;

#endif // _PREDICTION_H_