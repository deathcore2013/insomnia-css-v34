/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __MOVEHELPER_H__
#define __MOVEHELPER_H__
#include "VfuncTemplates.h"
#include "ClientClass.h"


namespace Valve
{
	class BaseEntity;


#define CLASSNAME IMoveHelper
	class IMoveHelper
	{
	public:
		// Call this to set the singleton
		static IMoveHelper* GetSingleton( ) { return sm_pSingleton; }
	
		virtual	void	function0();
		virtual void	function1();
		virtual void	function2();
		virtual void	function3();
		virtual void	function4();
		virtual void	function5();
		virtual void	function6();
		virtual void	function7();
		virtual void	function8();
		virtual void	function9();
		virtual void	function10();
		virtual void	function11();

		static void SetSingleton( IMoveHelper* pMoveHelper ) { sm_pSingleton = pMoveHelper; }
		virtual			~IMoveHelper() {}
		static IMoveHelper* sm_pSingleton;
	};

	IMoveHelper* IMoveHelper::sm_pSingleton = 0;

	inline IMoveHelper* MoveHelper( )
	{
		return IMoveHelper::GetSingleton();
	}

};

#endif //__MOVEHELPERCLIENT_H__