//detours.h

class CDetour
{
public:
	DWORD DetourFunction(DWORD dwAddress, void *pFunction);
	void RetourFunction();

private:
	int iOpcodeLength;
	DWORD dwOrigAddress;
	BYTE *bOldLocation;
};

extern CDetour g_Detour;