/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/

#include "Main.h"

CVMTHook::CVMTHook(void* instance)
{
	HANDLE hProcessHeap;

	if( instance )
	{
		m_pInstance = (void***) instance;
		m_pOriginalVTable = *m_pInstance;
		
		//Count number of Pointers in the table

		m_iNumIndices = 0;
		
		//TODO: check if pointer into .text section
		while(m_pOriginalVTable[m_iNumIndices])
		{
			m_iNumIndices++;
		}


		//Allocate memory on the heap for our own copy of the table

		hProcessHeap = GetProcessHeap();

		if( hProcessHeap )
		{
			m_pNewVTable = (void**) HeapAlloc(hProcessHeap, 0, sizeof(void*) * m_iNumIndices);
			if( m_pNewVTable )
			{
				memcpy(m_pNewVTable, m_pOriginalVTable, sizeof(void*) * m_iNumIndices);
				SetHookEnabled();
			}
			CloseHandle(hProcessHeap);
		}
	}
}

CVMTHook::~CVMTHook()
{
	HANDLE hProcessHeap;

	//Reset the VTable pointer
	if( *m_pInstance == m_pNewVTable )
	{
		*m_pInstance = m_pOriginalVTable;
	}

	//Free our copy of the VTable
	hProcessHeap = GetProcessHeap();
	if(hProcessHeap)
	{

		HeapFree(hProcessHeap, 0, m_pNewVTable);
		CloseHandle(hProcessHeap);
	}
}

void* CVMTHook::GetOriginalFunction(size_t iIndex)
{
	return m_pOriginalVTable[iIndex];
}

void* CVMTHook::HookFunction(size_t iIndex, void* pfnHook)
{
	//Valid index?
	if(iIndex >= m_iNumIndices)
		return NULL;
	
	//Write new pointer
	m_pNewVTable[iIndex] = pfnHook;

	//And return pointer to original function
	return m_pOriginalVTable[iIndex];
}

void CVMTHook::SetHookEnabled(bool bEnabled)
{
	if(bEnabled)
	{
		//Point to our copy of the VTable
		*m_pInstance = m_pNewVTable;
	}
	else
	{
		//Point to the original VTable
		*m_pInstance = m_pOriginalVTable;
	}
}