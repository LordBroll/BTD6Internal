#pragma once
#include <Windows.h>

namespace addr {
	void init();
	DWORD64 sig(const char* bytes, const char* mask);
	DWORD64 abs_sig(const char* bytes, const char* mask, int loc_offset = 0, int final_offset = 0);

	extern DWORD64 assembly_base;
	extern DWORD64 assembly_size;

	extern DWORD64 simulation_simulate;
	extern DWORD64 simulation_set_cash;
	extern DWORD64 simulation_get_cash;
	extern DWORD64 simulation_add_xp;

	extern DWORD64 konfuse_write;
	extern DWORD64 konfuse_read;

	extern DWORD64 player_ctor;
	extern DWORD64 player_get_tower_xp;
	extern DWORD64 player_add_tower_xp;
	extern DWORD64 player_gain_monkey_money;
	extern DWORD64 player_get_monkey_money;
	
	extern DWORD64 constants_get_aes;

	extern DWORD64 map_can_place;

}
