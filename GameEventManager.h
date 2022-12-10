#ifndef __GAMEEVENTMANAGER_H__
#define __GAMEEVENTMANAGER_H__

typedef struct hit_s
{
	int idx;
	int dmg;
	float time;
	Vector pos;
	bool setpos;
} hit_t;
std::vector< hit_s > hit;

class cGameEvent : public IGameEventListener2
{
public:
	void FireGameEvent( IGameEvent *event );
	void RegisterSelf( );
};

extern cGameEvent g_GameEventManager;

#endif //__GAMEEVENTMANAGER_H__