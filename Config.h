#ifndef __CONFIG_H__
#define __CONFIG_H__

class CConfig
{
public:
	void SetModule( HMODULE hModule );

	void Load( void );
	void Save( void );

private:
	HMODULE m_hModule;
};

extern CConfig g_Config;

#endif // __CONFIG_H__