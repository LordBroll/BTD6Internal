#pragma once
#include <map>

static const char* default_desc = "unknown value";
static const double blank_value = -142913;

class cheat_engine_value {
public:
	char desc[128];

	double last_read;
	double override;

	cheat_engine_value() {
		memcpy(desc, default_desc, strlen(default_desc) + 1);
		last_read = blank_value;
		override = blank_value;
	}
};

namespace cheat_engine {
	bool on_value_read(void* v, double* output);

	std::map<void*, cheat_engine_value>& map();
}
