#pragma once
#include "dumping_struct.h"

typedef bool (*map_can_place_fn)(void* this_obj, void* tower_model, void* tower, bool unk1);
typedef void (*xp_tower_xp_fn)(void* this_obj, string_t* tower, float xp);

namespace generic {

	extern bool place_anywhere;
	extern bool fast_xp_gain;
	
	bool can_place_h(void* this_obj, void* tower_model, void* tower, bool unk1);
	void add_tower_xp_h(void* this_obj, string_t* tower, float xp);
	
	void hook();
}
