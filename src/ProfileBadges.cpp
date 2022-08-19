#include <iostream>
#include "Safety/MemoryTest.hpp"
#include "Hooks/ProfilePage.hpp"
#include "Hooks/CommentCell.hpp"


#include <spdlog/spdlog.h>

DWORD WINAPI modThread(void* hModule){
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
    freopen_s(reinterpret_cast<FILE**>(stdin), "CONIN$", "r", stdin);
    spdlog::set_level(spdlog::level::trace);
    ProfilePage::hookInit();
    CommentCell::hookInit();
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, modThread, hModule, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}