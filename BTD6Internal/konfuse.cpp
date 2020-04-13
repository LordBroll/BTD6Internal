#include "konfuse.h"
#include "addr.h"
#include <Windows.h>
#include "detours/detours.h"
#include "imgui/imgui.h"
#include "simulation.h"
#include "cheat_engine.h"

// module
bool konfuse_module::force_values = false;
int konfuse_module::forced_value = 10000;

int konfuse_module::forced_hp = 1;
int konfuse_module::forced_shield = 1;

konfuse_read_fn konfuse_read_o = nullptr;
double konfuse_module::konfuse_read_h(void* this_obj) {
	double read_value = konfuse_read_o(this_obj);

	if(cheat_engine::on_value_read(this_obj, &read_value)) {
		return read_value;
	}

	simulation_object* sim = simulation::obj();

	if (sim) {
		if (this_obj == sim->health && forced_hp > 1) {
			return forced_hp;
		}

		if (this_obj == sim->shield && forced_shield > 1) {
			return forced_shield;
		}
	}
	
	if(force_values) {
		return forced_value;
	}
	
	return read_value;
}

void konfuse_module::hook() {
	konfuse_read_o = (konfuse_read_fn)addr::konfuse_read;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)konfuse_read_o, (PBYTE)konfuse_read_h);
	DetourTransactionCommit();
}

// class
double konfuse::read() {
	return konfuse_read_o(this);
}

void konfuse::write(double input) {
	((konfuse_write_fn)(addr::konfuse_write))(this, input);
}