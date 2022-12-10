/************************************************************************
*					Portable v34 SDK by InUrFace						*
*							15. 03. 2014								*
*					 Not for commercial purposes						*
*																		*
*																		*
************************************************************************/
#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "VfuncTemplates.h"

namespace Valve
{
	struct surfacephysicsparams_t
	{
		// vphysics physical properties
		float			friction;
		float			elasticity;				// collision elasticity - used to compute coefficient of restitution
		float			density;				// physical density (in kg / m^3)
		float			thickness;				// material thickness if not solid (sheet materials) in inches
		float			dampening;
	};

	struct surfaceaudioparams_t
	{
		// sounds / audio data
		float			reflectivity;		// like elasticity, but how much sound should be reflected by this surface
		float			hardnessFactor;	// like elasticity, but only affects impact sound choices
		float			roughnessFactor;	// like friction, but only affects scrape sound choices

		// audio thresholds
		float			roughThreshold;	// surface roughness > this causes "rough" scrapes, < this causes "smooth" scrapes
		float			hardThreshold;	// surface hardness > this causes "hard" impacts, < this causes "soft" impacts
		float			hardVelocityThreshold;	// collision velocity > this causes "hard" impacts, < this causes "soft" impacts
		// NOTE: Hard impacts must meet both hardnessFactor AND velocity thresholds
	};

	struct surfacesoundnames_t
	{
		unsigned short	stepleft;
		unsigned short	stepright;

		unsigned short	impactSoft;
		unsigned short	impactHard;

		unsigned short	scrapeSmooth;
		unsigned short	scrapeRough;

		unsigned short	bulletImpact;
		unsigned short	rolling;

		unsigned short	breakSound;
		unsigned short	strainSound;
	};

	struct surfacesoundhandles_t
	{
		short	stepleft;
		short	stepright;

		short	impactSoft;
		short	impactHard;

		short	scrapeSmooth;
		short	scrapeRough;

		short	bulletImpact;
		short	rolling;

		short	breakSound;
		short	strainSound;
	};

	struct surfacegameprops_t
	{
		// game movement data
		float			maxSpeedFactor;			// Modulates player max speed when walking on this surface
		float			jumpFactor;				// Indicates how much higher the player should jump when on the surface
		// Game-specific data
		unsigned short	material;
		// Indicates whether or not the player is on a ladder.
		unsigned char	climbable;
		unsigned char	pad;
	};
	struct surfacedata_t
	{
		surfacephysicsparams_t	physics;	// physics parameters
		surfaceaudioparams_t	audio;		// audio parameters
		surfacesoundnames_t		sounds;		// names of linked sounds
		surfacegameprops_t		game;		// Game data / properties

		surfacesoundhandles_t		soundhandles;
	};


#define CLASSNAME IPhysicsSurfaceProps
	class IPhysicsSurfaceProps
	{
	public:
		VFUNCR1(GetSurfaceData, 0x14, surfacedata_t*, int);
	};
};

#endif //__PHYSICS_H__