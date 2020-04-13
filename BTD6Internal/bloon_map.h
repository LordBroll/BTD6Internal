#pragma once

typedef bool (*map_can_place_fn)(void* this_obj, void* tower_model, void* tower, bool unk1);

namespace bloon_map {

	extern bool place_anywhere;
	
	bool can_place_h(void* this_obj, void* tower_model, void* tower, bool unk1);
	
	void hook();
}
