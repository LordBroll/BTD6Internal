#include "player.h"
#include "addr.h"
#include "debug.h"
#include "detours/detours.h"
#include "internals.h"

player_object* player_instance = nullptr;

player_ctor_fn ctor_o = nullptr;
void player::ctor_h(void* this_obj) {
	player_instance = (player_object*)this_obj;
	
	return ctor_o(this_obj);
}

player_get_tower_xp_fn get_tower_xp_o = nullptr;
float player::get_tower_xp_h(void* this_obj, string_t* tower) {
	player_instance = (player_object*)this_obj;

	// used to dump towers
	// dbg::log("[+] tower: %s", internal_string::str(tower).c_str());
	
	return get_tower_xp_o(this_obj, tower);
}

player_object* player::obj() {
	return player_instance;
}

void player::add_tower_xp(string_t* tower, float xp) {
	((player_add_tower_xp_fn)addr::xp_add_tower_xp)(player_instance, tower, xp);
}

void player::add_instant_monkey(string_t* tower, int a, int b, int c, int amt) {
	//array_t* arr = internal_array::new_int_array(new int[3] { a, b, c }, 3); // cba to free this, its like 8 bytes either way

	//((player_add_instant_tower_fn)addr::player_add_instant_monkey)(player_instance, tower, arr, amt);
}


void player::hook() {
	ctor_o = (player_ctor_fn)addr::simulation_simulate;
	get_tower_xp_o = (player_get_tower_xp_fn)addr::player_get_tower_xp;
	
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)ctor_o, (PBYTE)ctor_h);
	DetourAttach(&(LPVOID&)get_tower_xp_o, (PBYTE)get_tower_xp_h);
	DetourTransactionCommit();
}
