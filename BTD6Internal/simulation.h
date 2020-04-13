#pragma once
#include "simulation_struct.h"

typedef void (*simulation_simulate_fn) (void* this_obj);
typedef void (*simulation_set_cash_fn) (void* this_obj, double cash, int index);
typedef double (*simulation_get_cash_fn) (void* this_obj, int index);
typedef void (*simulation_add_xp_fn) (void* this_obj, float amount);

namespace simulation {
	void hook();
	
	void set_cash(double cash, int index);
	double get_cash(int index);

	void add_xp(float xp);
	
	void simulate_h(void* this_obj);

	bool is_in_game();
	
	simulation_object* obj();
}
