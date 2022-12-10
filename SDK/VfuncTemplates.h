/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __VFUNC_TEMPLATES_H__
#define __VFUNC_TEMPLATES_H__

namespace Valve
{
//Without returnvalue
#define VFUNCN0(funcname, offs) inline void funcname()\
	{ ((void (__thiscall*)(CLASSNAME*))*(void**)((*(int*)this)+offs))(this); }

#define VFUNCN1(funcname, offs, arg1) inline void funcname(arg1 a1)\
	{ ((void (__thiscall*)(CLASSNAME*, arg1))*(void**)((*(int*)this)+offs))(this, a1); }
	
#define VFUNCN2(funcname, offs, arg1, arg2) inline void funcname(arg1 a1, arg2 a2)\
	{ ((void (__thiscall*)(CLASSNAME*, arg1, arg2))*(void**)((*(int*)this)+offs))(this, a1, a2); }
	
#define VFUNCN3(funcname, offs, arg1, arg2, arg3) inline void funcname(arg1 a1, arg2 a2, arg3 a3)\
	{ ((void (__thiscall*)(CLASSNAME*, arg1, arg2, arg3))*(void**)((*(int*)this)+offs))(this, a1, a2, a3); }

#define VFUNCN4(funcname, offs, arg1, arg2, arg3, arg4) inline void funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4)\
	{ ((void (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4); }

#define VFUNCN5(funcname, offs, arg1, arg2, arg3, arg4, arg5) inline void funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5)\
	{ ((void (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5); }

#define VFUNCN6(funcname, offs, arg1, arg2, arg3, arg4, arg5, arg6) inline void funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5, arg6 a6)\
	{ ((void (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5, arg6))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5, a6); }

#define VFUNCN7(funcname, offs, arg1, arg2, arg3, arg4, arg5, arg6, arg7) inline void funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5, arg6 a6, arg7 a7)\
	{ ((void (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5, arg6, arg7))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5, a6, a7); }

#define VFUNCN8(funcname, offs, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) inline void funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5, arg6 a6, arg7 a7, arg8 a8)\
	{ ((void (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5, a6, a7, a8); }



//With returnvalue
#define VFUNCR0(funcname, offs, rt) inline rt funcname()\
	{ return ((rt (__thiscall*)(CLASSNAME*))*(void**)((*(int*)this)+offs))(this); }

#define VFUNCR1(funcname, offs, rt, arg1) inline rt funcname(arg1 a1)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1))*(void**)((*(int*)this)+offs))(this, a1); }

#define VFUNCR2(funcname, offs, rt, arg1, arg2) inline rt funcname(arg1 a1, arg2 a2)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1, arg2))*(void**)((*(int*)this)+offs))(this, a1, a2); }

#define VFUNCR3(funcname, offs, rt, arg1, arg2, arg3) inline rt funcname(arg1 a1, arg2 a2, arg3 a3)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1, arg2, arg3))*(void**)((*(int*)this)+offs))(this, a1, a2, a3); }

#define VFUNCR4(funcname, offs, rt, arg1, arg2, arg3, arg4) inline rt funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4); }

#define VFUNCR5(funcname, offs, rt, arg1, arg2, arg3, arg4, arg5) inline rt funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5); }

#define VFUNCR6(funcname, offs, rt, arg1, arg2, arg3, arg4, arg5, arg6) inline rt funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5, arg6 a6)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5, arg6))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5, a6); }

#define VFUNCR7(funcname, offs, rt, arg1, arg2, arg3, arg4, arg5, arg6, arg7) inline rt funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5, arg6 a6, arg7 a7)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5, arg6, arg7))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5, a6, a7); }

#define VFUNCR8(funcname, offs, rt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) inline rt funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5, arg6 a6, arg7 a7, arg8 a8)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5, a6, a7, a8); }

#define VFUNCR9(funcname, offs, rt, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) inline rt funcname(arg1 a1, arg2 a2, arg3 a3, arg4 a4, arg5 a5, arg6 a6, arg7 a7, arg8 a8, arg9 a9)\
	{ return ((rt (__thiscall*)(CLASSNAME*, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9))*(void**)((*(int*)this)+offs))(this, a1, a2, a3, a4, a5, a6, a7, a8, a9); }


};


#endif //__VFUNC_TEMPLATES_H__