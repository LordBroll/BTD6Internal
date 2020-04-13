#pragma once
#include <vector>

#include "internals.h"


namespace constants {
	void init();
	
	extern string_t* empty;
	extern string_t* anti_url;
	
	extern std::vector<std::pair<std::string, string_t*>> towers;
}
