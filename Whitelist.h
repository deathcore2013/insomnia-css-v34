#ifndef __WHITELIST_H__
#define __WHITELIST_H__

class Whitelist
{
public:
	void Init( );
	bool List( int index );
	bool IsWhitelisted[ 65 ];
	std::vector< std::string > names;
	std::vector< std::string > SteamIDs;
};

extern Whitelist g_Whitelist;

#endif __WHITELIST_H__