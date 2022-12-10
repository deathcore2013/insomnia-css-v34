/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __INTERFACEMANAGER_H__
#define __INTERFACEMANAGER_H__

#include <Windows.h>
#include <iostream>
#define DEBUGLOG

namespace HackInterfaces
{

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);
class InterfaceManager;

class ModuleInfo
{
public:
	ModuleInfo(const char* szModuleName)
	{
		MEMORY_BASIC_INFORMATION mbi;
		hModule = GetModuleHandleA( szModuleName );
		while( !hModule )
		{
			Sleep(10);
			hModule = GetModuleHandleA( szModuleName );
		}

		//Code start is Base + sizeof(header)
		dwCodeBase = dwModuleBase + 0x1000;

		while( !VirtualQuery( (LPVOID)dwCodeBase, &mbi, sizeof( MEMORY_BASIC_INFORMATION ) ) )
			Sleep(10);
		dwCodeSize = mbi.RegionSize;

		pfnCreateInterface = (CreateInterfaceFn) GetProcAddress( hModule, "CreateInterface" );

	}
private:
	inline bool IsPatternMatching(char* pAddress, char* szPattern)
	{
		while( *szPattern )
		{
			if( ( *szPattern != *pAddress ) && ( *szPattern != '?' ) )
				return false;

			szPattern++;
			pAddress++;
		}
		return true;
	}

public:
	inline DWORD_PTR FindPattern(char* pattern)
	{
		if( !pbCodeBase )
			return NULL;

		//Skip initial unknowns
		while( *pattern == '?' ) pattern++;

		char* it = pbCodeBase;
		char* end = (char*) (dwCodeSize + dwCodeSize - strlen( pattern ) - 1 );

		while (it < end)
		{
			if( *it == *pattern )
			{
				if( IsPatternMatching ( it, pattern ) )
					return (DWORD_PTR) it;
			}
			it++;
		}
		return NULL;
	}
	void* FindInterfaceNoBruteforce(const char* szInterfaceName)
	{
		if( !pfnCreateInterface )
			return NULL;
		return pfnCreateInterface( szInterfaceName, NULL );
	}
	void* FindInterface(const char* szInterfaceName)
	{
		char buf[50];
		void* pInterface = NULL;
		if( !pfnCreateInterface )
			return NULL;

		for( int i=0; i<10; ++i )
		{
			sprintf_s( buf, 50, "%s00%d", szInterfaceName, i );
			pInterface = pfnCreateInterface( buf, NULL );
			if( pInterface )
			{
				return pInterface;
			}
		}
		for( int i=10; i<100; ++i )
		{
			sprintf_s( buf, 50, "%s0%d", szInterfaceName, i );
			pInterface = pfnCreateInterface( buf, NULL );
			if( pInterface )
			{	
				return pInterface;
			}
		}
		for( int i=100; i<300; ++i )
		{
			sprintf_s( buf, 50, "%s%d", szInterfaceName, i );
			pInterface = pfnCreateInterface( buf, NULL );
			if( pInterface )
			{
				return pInterface;
			}
		}
#ifdef DEBUGLOG
		printf( "%s not found!!!\n", szInterfaceName);
#endif //DEBUGLOG

		return NULL;
	}
	union
	{
		HMODULE hModule;
		DWORD_PTR dwModuleBase;
	};
	union
	{
		DWORD_PTR dwCodeBase;
		char* pbCodeBase;
	};
	SIZE_T dwCodeSize;
	CreateInterfaceFn pfnCreateInterface;
};

class InterfaceManager
{
public:
	inline bool ready()
	{
		return m_ready;
	}
	InterfaceManager();
	bool init();
private:

	bool m_ready;

public:
	//hl2.exe
	ModuleInfo m_mainModule;

	//Source Engine Dlls
	ModuleInfo m_clientDll;
	ModuleInfo m_engineDll;
	ModuleInfo m_vgui2Dll;
	ModuleInfo m_vguiMatSurfaceDll;
	ModuleInfo m_materialSystemDll;
	ModuleInfo m_vphysicsDll;
	ModuleInfo m_vstdlibDll;
	//ModuleInfo m_tier0Dll;

};


};
extern HackInterfaces::InterfaceManager* g_pInterfaceManager;

#endif //__INTERFACEMANAGER_H__