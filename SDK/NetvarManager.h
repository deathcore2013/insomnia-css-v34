/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*		   Credits to Marcus Thorman(kiro) for his functions			*
*																		*
************************************************************************/
#ifndef __NETVARMANAGER_H__
#define __NETVARMANAGER_H__
#include "ClientClass.h"
#include <vector>
namespace HackInterfaces
{
	class NetvarManager;

	class NetvarManager
	{
	public:
		//static NetvarManager* Singleton();
		NetvarManager( void );
		int GetOffset(const char *tableName, const char *propName);
		bool HookRecvProp(const char *tableName, const char *propName, Valve::RecvVarProxyFn function, Valve::RecvVarProxyFn* pfnOld = 0);
		bool Init();

	private:
		int GetRecvProp(const char *tableName, const char *propName, Valve::RecvProp **prop = 0);
		int GetRecvProp(Valve::RecvTable *recvTable, const char *propName, Valve::RecvProp **prop = 0);
		Valve::RecvTable *GetTable(const char *tableName);
		
		NetvarManager(const NetvarManager& other);
		std::vector<Valve::RecvTable*> m_recvTables;
		bool m_ready;
	};
};
extern HackInterfaces::NetvarManager* g_pNetvarManager;

namespace Valve
{
#define TOSTR(a) #a
#define NETVAR(t, cn, vn)\
	inline t& vn()\
	{ \
		static int s_iOffset=HackInterfaces::NetvarManager( ).GetOffset(TOSTR(cn), TOSTR(vn));\
		return *(t*)((DWORD)this+s_iOffset);\
	}
#define NETVARN(t, cn, vn, n)\
	inline t& n()\
	{ \
		static int s_iOffset=HackInterfaces::NetvarManager( ).GetOffset(TOSTR(cn), TOSTR(vn));\
		return *(t*)((DWORD)this+s_iOffset);\
	}
#define NETVARPLUS(t, cn, vn, n, offs)\
	inline t& n()\
	{ \
		static int s_iOffset=HackInterfaces::NetvarManager( ).GetOffset(TOSTR(cn), TOSTR(vn)) + offs;\
		return *(t*)((DWORD)this+s_iOffset);\
	}
};

#endif //__NETVARMANAGER_H__