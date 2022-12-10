/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __VMTHOOK_H__
#define __VMTHOOK_H__

#include <Windows.h>

class CVMTHook
{
public:
	CVMTHook(void* instance);
	~CVMTHook();
	void* HookFunction( size_t iIndex, void* pfnHook );
	void* GetOriginalFunction( size_t iIndex );
	void SetHookEnabled( bool bEnabled = true );
	template< typename T > T Function( int iIndex )
	{
		return ( T )( m_pOriginalVTable[ iIndex ] );
	}

	size_t m_iNumIndices;
	void** m_pOriginalVTable;
	void** m_pNewVTable;
	void*** m_pInstance;
};

#endif //__VMTHOOK_H__