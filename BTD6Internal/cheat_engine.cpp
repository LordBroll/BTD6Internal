#include "cheat_engine.h"

std::map<void*, cheat_engine_value> values;

cheat_engine_value& get_metadata(void* v) {
	if(!values.count(v)) {
		values[v] = cheat_engine_value();
	}

	return values[v];
}

bool cheat_engine::on_value_read(void* v, double* output) {
	cheat_engine_value& m = get_metadata(v);

	if(m.last_read == m.override) {
		m.override = *output;
		m.last_read = *output;

		return false;
	}

	m.last_read = *output;
	*output = m.override;
	
	return true;
}

std::map<void*, cheat_engine_value>& cheat_engine::map() {
	return values;
}
