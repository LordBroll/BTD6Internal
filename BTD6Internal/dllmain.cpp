#include <Windows.h>


#include "addr.h"
#include "debug.h"
#include "detours/detours.h"
#include "dx.h"
#include "player.h"
#include "simulation.h"
#include "internals.h"
#include "dumping.h"
#include "bloon_map.h"
#include "constants.h"

HMODULE wait_for_dll(const char* name) {
	dbg::log("[+] waiting for %s", name);
	
	HMODULE result = GetModuleHandleA(name);

	while (result == nullptr) {
		Sleep(100);

		result = GetModuleHandleA(name);
	}

	return result;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
	    case DLL_PROCESS_ATTACH:
			CreateThread(NULL, 0, [](LPVOID _) -> DWORD {
				dbg::alloc_console();
				wait_for_dll("d3d11.dll");
				wait_for_dll("GameAssembly.dll");

				addr::init();
				constants::init();
	    	
				konfuse_module::hook();
				dumping::hook();
				simulation::hook();
				player::hook();
				bloon_map::hook();
	    	
				dx::hook();

				return 0;
		    }, NULL, NULL, NULL);
			break;
	    case DLL_THREAD_ATTACH:
	    case DLL_THREAD_DETACH:
	    case DLL_PROCESS_DETACH:
	        break;
    }
    return TRUE;
}

