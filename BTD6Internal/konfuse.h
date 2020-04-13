#pragma once

typedef double (*konfuse_read_fn) (void* this_obj);
typedef void (*konfuse_write_fn) (void* this_obj, double number);

namespace konfuse_module {
	extern bool force_values;
	extern int forced_value;

	extern int forced_hp;
	extern int forced_shield;
	
	double konfuse_read_h(void* this_obj);
	
	void hook();
}


// class
class konfuse {
public:
	double read();
	void write(double input);
};