/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __CLIENTENTITY_H__
#define __CLIENTENTITY_H__
#include "VfuncTemplates.h"
#include "ClientClass.h"
#include "Vector.h"

namespace Valve
{
	class BaseEntity;
	class IClientEntity;
	class IClientUnknown;
	class IHandleEntity;
	class IClientNetworkable;
	class IClientRenderable;
	class IClientThinkable;
	typedef void* EHANDLE;

	class IHandleEntity
	{
	public:
		virtual ~IHandleEntity() {}
		virtual void SetRefEHandle( const EHANDLE &handle ) = 0;
		virtual const EHANDLE& GetRefEHandle() const = 0;
	};

	class IClientUnknown : public IHandleEntity
	{
	public:
		virtual void* GetCollideable() = 0;
		virtual IClientNetworkable* GetClientNetworkable() = 0;
		virtual IClientRenderable* GetClientRenderable() = 0;
		virtual IClientEntity* GetIClientEntity() = 0;
		virtual BaseEntity* GetBaseEntity() = 0;
		virtual IClientThinkable* GetClientThinkable() = 0;
	};
	
	class IClientRenderable
	{
	public:
		virtual void*	GetIClientUnknown() = 0;
		virtual Vector const& GetRenderOrigin( void ) = 0;
		virtual QAngle const& GetRenderAngles( void ) = 0;
		virtual bool	ShouldDraw( void ) = 0;
		virtual bool	IsTransparent( void ) = 0;
		virtual bool	UsesFullFrameBufferTexture() = 0;
		virtual void	GetShadowHandle() const = 0;
		virtual void	RenderHandle() = 0;
		virtual void*	GetModel( ) = 0;
		virtual int		DrawModel( int flags ) = 0;
		virtual int		GetBody() = 0;
		virtual void	ComputeFxBlend( ) = 0;
		virtual int		GetFxBlend( void ) = 0;
		virtual void	GetColorModulation( float* color ) = 0;
		virtual bool	LODTest() = 0;
		virtual bool	SetupBones( matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime ) = 0;
		virtual void	SetupWeights( void ) = 0;
		virtual void	DoAnimationEvents( void ) = 0;
		virtual void*	GetPVSNotifyInterface() = 0;
		virtual void	GetRenderBounds( Vector& mins, Vector& maxs ) = 0;
	};

	class IClientNetworkable
	{
	public:
		virtual IClientUnknown*	GetIClientUnknown() = 0;
		virtual void			Release() = 0;
		virtual Valve::ClientClass*	GetClientClass() = 0;
		virtual void			NotifyShouldTransmit( int state ) = 0;
		virtual void			OnPreDataChanged(int updateType) = 0;
		virtual void			OnDataChanged(int updateType) = 0;
		virtual void			PreDataUpdate( int updateType ) = 0;
		virtual void			PostDataUpdate( int updateType ) = 0;
		virtual bool			IsDormant() = 0;
		virtual int				entindex() const = 0;
		virtual void			ReceiveMessage(int classID, int &msg) = 0;
		virtual void*			GetDataTableBasePtr() = 0;
		virtual void			SetDestroyedOnRecreateEntities() = 0;
	};
	class IClientThinkable
	{
	public:
		virtual IClientUnknown*		GetIClientUnknown() = 0;
		virtual void				ClientThink() = 0;
		virtual void*				GetThinkHandle() = 0;
		virtual void				SetThinkHandle(void* hThink) = 0;
		virtual void				Release() = 0;
	};
	
	class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
	{
	public:
		virtual const Vector&		GetAbsOrigin( void ) const;
		virtual const QAngle&		GetAbsAngles( void ) const;
	};
};

#endif //__CLIENTENTITY_H__