#include "generic.h"
#include "addr.h"
#include <Windows.h>

#include "debug.h"
#include "detours/detours.h"

bool generic::place_anywhere = false;
bool generic::fast_xp_gain = false;
bool generic::infinite_tier_five = false;

void* xp_instance = nullptr;

map_can_place_fn can_place_o = nullptr;
bool generic::can_place_h(void* this_obj, void* tower_model, void* tower, bool unk1) {
	if(place_anywhere) {
		return true;
	}

	return can_place_o(this_obj, tower_model, tower, unk1);
}

xp_tower_xp_fn add_tower_xp_o = nullptr;
void generic::add_tower_xp_h(void* this_obj, string_t* tower, float xp) {
	xp_instance = this_obj;
	
	float rad_xp = xp;
	if(fast_xp_gain) {
		rad_xp = 200000;
	}
	
	return add_tower_xp_o(this_obj, tower, rad_xp);
}

tower_inventory_is_path_tier_locked_fn is_path_tier_locked_o = nullptr;
bool generic::is_path_tier_locked_h(void* this_obj, void* tower, int unk1, int unk2) {
	if(infinite_tier_five) {
		return false;
	}

	return is_path_tier_locked_o(this_obj, tower, unk1, unk2);
}

void generic::hook() {
	can_place_o = (map_can_place_fn)addr::map_can_place;
	add_tower_xp_o = (xp_tower_xp_fn)addr::xp_add_tower_xp;
	is_path_tier_locked_o = (tower_inventory_is_path_tier_locked_fn)addr::tower_inventory_is_path_tier_locked;
	
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)can_place_o, (PBYTE)can_place_h);
	DetourAttach(&(LPVOID&)add_tower_xp_o, (PBYTE)add_tower_xp_h);
	DetourAttach(&(LPVOID&)is_path_tier_locked_o, (PBYTE)is_path_tier_locked_h);
	DetourTransactionCommit();
}
