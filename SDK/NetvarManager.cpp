/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*			Credits to Marcus Thormann for his functions				*
*																		*
************************************************************************/
#include "NetvarManager.h"
#include "BaseClient.h"
#include <Windows.h>

extern Valve::IBaseClientDLL* g_pBaseClientDll;

using namespace HackInterfaces;

NetvarManager* g_pNetvarManager = 0;
/*
NetvarManager* NetvarManager::Singleton()
{
	return g_pNetvarManager;
}
*/
NetvarManager::NetvarManager( void )
{
	m_recvTables.clear( );
	m_ready = false;

	Valve::ClientClass *clientClass = g_pBaseClientDll->GetAllClasses( );
 
    if ( !clientClass )
    {
		//printf( "ClientClass not found!" );
        return;
    }
 
    while ( clientClass )
    {
        Valve::RecvTable *recvTable = clientClass->m_pRecvTable;
        m_recvTables.push_back( recvTable );
        clientClass = clientClass->m_pNext;
    }
}
bool NetvarManager::Init()
{
	Valve::ClientClass* pClass=g_pBaseClientDll->GetAllClasses();
	if(!pClass)
		return false;
	while(pClass)
	{
		if(pClass->m_pRecvTable)
			m_recvTables.push_back(pClass->m_pRecvTable);
		pClass=pClass->m_pNext;
	}
	m_ready=true;
	return true;
}

int NetvarManager::GetOffset(const char *tableName, const char *propName)
{
    int offs = GetRecvProp(tableName, propName);
	//printf( "%s: %s -> %x\n", tableName, propName, offs );
	return offs;
}

int NetvarManager::GetRecvProp(const char *tableName, const char *propName, Valve::RecvProp **prop)
{
    Valve::RecvTable* recvTable=GetTable(tableName);
 
    if(!recvTable)
		return 0;
 
    return GetRecvProp(recvTable, propName, prop);
}
int NetvarManager::GetRecvProp(Valve::RecvTable *recvTable, const char *propName, Valve::RecvProp **prop)
{
    int extraOffset=0;
    for(int i=0; i<recvTable->m_nProps; ++i)
    {
        Valve::RecvProp *recvProp=&recvTable->m_pProps[i];
 
 
       Valve:: RecvTable *child=recvProp->m_pDataTable;
 
        if(child && ( child->m_nProps>0))
        {
            int tmp = GetRecvProp(child, propName, prop);
            if (tmp)
            {
                extraOffset+=(recvProp->m_Offset + tmp);
            }
        }
 
 
        if(_stricmp(recvProp->m_pVarName, propName))
            continue;
 
 
        if(prop)
            *prop = recvProp;

        return (recvProp->m_Offset+extraOffset);
    }
    return extraOffset;
}
Valve::RecvTable *NetvarManager::GetTable(const char *tableName)
{
	if( m_recvTables.empty( ) )
	{
		return 0;
	}
 
	for(auto Iterator=m_recvTables.begin(); Iterator!=m_recvTables.end(); Iterator++)
	{
		Valve::RecvTable* table=*Iterator._Ptr;
		if( !table )
		{
			continue;
		}

		if(_stricmp(table->m_pNetTableName, tableName)==0)
		{
			return table;
		}
	}

	return 0;
}
bool NetvarManager::HookRecvProp(const char *tableName, const char *propName, Valve::RecvVarProxyFn function, Valve::RecvVarProxyFn* pfnOld)
{
	Valve::RecvProp *recvProp = 0;
	GetRecvProp(tableName, propName, &recvProp);

    if(!recvProp)
        return false;

	if(pfnOld)
		*pfnOld=recvProp->m_ProxyFn;
    recvProp->m_ProxyFn=function;
 
    return true;
}
	

