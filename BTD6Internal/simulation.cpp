#include "simulation.h"

#include <Windows.h>
#include "detours/detours.h"
#include "addr.h"
#include "debug.h"

simulation_object* simulation_instance = nullptr;

simulation_simulate_fn simulate_o = nullptr;
void simulation::simulate_h(void* this_obj) {
	simulation_instance = (simulation_object*)this_obj;
	
	simulate_o(this_obj);
}

simulation_object* simulation::obj() {
	return simulation_instance;
}

void simulation::set_cash(double cash, int index) {
	((simulation_set_cash_fn)(addr::simulation_set_cash))(simulation_instance, cash, index);
}

double simulation::get_cash(int index) {
	return ((simulation_get_cash_fn)(addr::simulation_get_cash))(simulation_instance, index);
}

void simulation::add_xp(float xp) {
	((simulation_add_xp_fn)(addr::simulation_add_xp))(simulation_instance, xp);
}

void simulation::hook() {
	simulate_o = (simulation_simulate_fn)addr::simulation_simulate;
	
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)simulate_o, (PBYTE)simulate_h);
	DetourTransactionCommit();
}




