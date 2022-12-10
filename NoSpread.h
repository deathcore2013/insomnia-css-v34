#ifndef __NOSPREAD_H__
#define __NOSPREAD_H__

enum WeaponIDsCSS
{
	WEAPON_NULL,
	WEAPON_P228,
	WEAPON_GLOCK,
	WEAPON_SCOUT,
	WEAPON_HE_GRENADE,
	WEAPON_XM1014,
	WEAPON_C4,
	WEAPON_MAC10,
	WEAPON_AUG,
	WEAPON_SMOKE_GRENADE,
	WEAPON_ELITES,
	WEAPON_FIVESEVEN,
	WEAPON_UMP,
	WEAPON_SG550,
	WEAPON_GALIL,
	WEAPON_FAMAS,
	WEAPON_USP,
	WEAPON_AWP,
	WEAPON_MP5,
	WEAPON_M249,
	WEAPON_M3,
	WEAPON_M4A1,
	WEAPON_TMP,
	WEAPON_G3SG1,
	WEAPON_FLASHBANG,
	WEAPON_DEAGLE,
	WEAPON_SG552,
	WEAPON_AK47,
	WEAPON_KNIFE,
	WEAPON_P90
};

class NoSpread
{
public:
	uintptr_t GetWeaponData( CSWeapon* );
	WeaponInfo GetWeaponInfo( CSWeapon* );
	float GetSpread( BasePlayer*, int );
	void Main( CUserCmd*, QAngle&, BasePlayer*, CSWeapon*, bool );
	void Iterative( CUserCmd*, QAngle&, BasePlayer*, CSWeapon*, bool );
	void CoolNospreee( CUserCmd*, QAngle&, BasePlayer*, CSWeapon*, bool );
};

extern NoSpread g_NoSpread;

#endif //__NOSPREAD_H__