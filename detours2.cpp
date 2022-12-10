#include "main.h"

CDetour g_Detour;

DWORD CDetour::DetourFunction(DWORD dwAddress, void *pFunction)
{
    //Init
    BYTE *bOpcodes = (BYTE*)dwAddress;
    iOpcodeLength = 0;

    //Find 5 bytes
    for( ; iOpcodeLength < 5 ; iOpcodeLength += oplen(bOpcodes), bOpcodes += iOpcodeLength)
    {
        int iOpcodeLen = oplen(bOpcodes);

        if(!iOpcodeLen)
            return 0;

        if(iOpcodeLen == 5)
        {
            iOpcodeLength += (iOpcodeLen - 1);
            break;
        }
    }

    //Allocate space and store original jmp location
    DWORD dwJmpAddress = (DWORD)bOpcodes;
    bOldLocation = new BYTE[iOpcodeLength];
    dwOrigAddress = dwAddress;
    
    DWORD dwHookedAddr = (DWORD)VirtualAlloc(0, iOpcodeLength, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    if(!dwHookedAddr)
        return 0;

    //Copy content from function to our new allocated space for retouring and orig func
    memcpy(bOldLocation, (void*)dwAddress, iOpcodeLength);
    memcpy((void*)dwHookedAddr, bOldLocation, iOpcodeLength);

    //Setup jmp to our orig func in the allocated space
    BYTE bJmpAddress[5] = { 0xE9, 0x00, 0x00, 0x00, 0x00 };
    *(DWORD*)&bJmpAddress[1] = (dwAddress + iOpcodeLength - 5) -  (dwHookedAddr + iOpcodeLength);
    memcpy((void*)(dwHookedAddr + iOpcodeLength), &bJmpAddress, sizeof(bJmpAddress));

    //Unprotect
    DWORD dwOld;
    VirtualProtect((void*)dwAddress, iOpcodeLength, PAGE_EXECUTE_READWRITE, &dwOld);

    //NOP, no need to NOP first 5 since thats our jmp
    for(BYTE i = 5; i < iOpcodeLength; ++i)
        *(BYTE*)(dwAddress + i) = 0x90;

    //Setup jmp to our hook in PreS_DynamicSound start
    *(DWORD*)&bJmpAddress[1] = (DWORD)pFunction - dwAddress - 0x5;
    memcpy((void*)dwAddress, &bJmpAddress, sizeof(bJmpAddress));

    //Set protections back
    VirtualProtect((void*)dwAddress, iOpcodeLength, dwOld, &dwOld);
    
    return dwHookedAddr;
}

void CDetour::RetourFunction()
{
    //Unprotect
    DWORD dwOld;
    VirtualProtect((void*)dwOrigAddress, iOpcodeLength, PAGE_EXECUTE_READWRITE, &dwOld);

    //Copy old code back to function to avoid crashes on detach etc
    memcpy((void*)dwOrigAddress, bOldLocation, iOpcodeLength);

    //Set protections back
    VirtualProtect((void*)dwOrigAddress, iOpcodeLength, dwOld, &dwOld);
    delete []bOldLocation;
}