#pragma once
#include "internals.h"
#include "player_struct.h"

typedef void (*player_ctor_fn) (void* this_obj);
typedef float (*player_get_tower_xp_fn) (void* this_obj, string_t* tower);
typedef void (*player_add_tower_xp_fn) (void* this_obj, string_t* tower, float xp);
typedef float (*player_get_monkey_money_fn) (void* this_obj);
typedef void (*player_add_instant_tower_fn) (void* this_obj, string_t* tower, array_t* upgrades, int amount);

namespace player {
	void hook();

	player_object* obj();

	void add_tower_xp(string_t* tower, float xp);
	void add_instant_monkey(string_t* tower, int a, int b, int c, int amt=1);
	
	void ctor_h(void* this_obj);
	float get_tower_xp_h(void* this_obj, string_t* tower);
};