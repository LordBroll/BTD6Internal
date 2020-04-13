#include "bloon_map.h"
#include "addr.h"
#include <Windows.h>
#include "detours/detours.h"

bool bloon_map::place_anywhere = false;

map_can_place_fn can_place_o = nullptr;
bool bloon_map::can_place_h(void* this_obj, void* tower_model, void* tower, bool unk1) {
	if(place_anywhere) {
		return true;
	}

	return can_place_o(this_obj, tower_model, tower, unk1);
}

void bloon_map::hook() {
	can_place_o = (map_can_place_fn)addr::map_can_place;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)can_place_o, (PBYTE)can_place_h);
	DetourTransactionCommit();
}
