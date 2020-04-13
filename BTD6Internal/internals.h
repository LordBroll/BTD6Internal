#pragma once
#include <cstdint>
#include <string>
#include <codecvt>
#include <iomanip>
#include <sstream>
#include <Windows.h>

#include "debug.h"

typedef struct object_t {
    union {
        void* klass;
        void* vtable;
    };

    void* monitor;
} object_t;

typedef struct string_t : object_t {
	uint32_t length;
	uint16_t _char;
} string_t;

typedef struct array_bounds_t {
	uintptr_t length;
	int32_t lower_bound;
} array_bounds_t;

typedef struct array_t : object_t {
	array_bounds_t* bounds;
	uint32_t length;
	uint32_t max_length;
	void* vector[0];
} array_t;

namespace internal_array {
	__forceinline void dump_byte_array(const char* name, array_t* a) {
		if(a == nullptr) {
			dbg::log("[array dump] %s = nullptr", name);
			return;
		}

		std::stringstream result;

		unsigned char* data = (unsigned char*)a->vector;
		
		for(int i = 0; i < (a->length); i++) {
			result << std::setw(2) << std::setfill('0') << std::hex << ((int)data[i]) << " ";
		}

		result << "(len=" << a->length << ")";

		dbg::log("[array dump] %s = %s", name, result.str().c_str());
	}
}

namespace internal_string {
	extern std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> convert;
	extern std::allocator<unsigned char> allocator;
	
	__forceinline const char16_t* data(string_t* s) {
		return (char16_t*)&(*s)._char;
	}

	__forceinline const char16_t* data(string_t s) {
		return (char16_t*)&(s._char);
	}

	__forceinline std::u16string u16(string_t s) {
		return std::u16string(data(s), s.length);
	}

	__forceinline std::u16string u16(string_t* s) {
		return std::u16string(data(s), s->length);
	}

	__forceinline std::string str(string_t s) {
		return convert.to_bytes(u16(s));
	}

	__forceinline std::string str(string_t* s) {
		return convert.to_bytes(u16(s));
	}

	string_t* new_string(const char* str);
}
