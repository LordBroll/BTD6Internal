#pragma once
#include "internals.h"
#include "player_struct.h"

typedef void (*player_ctor_fn) (void* this_obj);
typedef float (*player_get_tower_xp_fn) (void* this_obj, string_t* tower);
typedef void (*player_add_tower_xp_fn) (void* this_obj, string_t* tower, float xp);
typedef float (*player_get_monkey_money_fn) (void* this_obj);

namespace player {
	void hook();

	player_object* obj();

	void add_tower_xp(string_t* tower, float xp);
	
	void ctor_h(void* this_obj);
	float get_tower_xp_h(void* this_obj, string_t* tower);
	float get_monkey_money_h(void* this_obj);
};