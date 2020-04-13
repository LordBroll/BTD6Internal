#include "internals.h"

std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> internal_string::convert;
std::allocator<unsigned char> internal_string::allocator;

DWORD64 il2cpp_string_new_addr = 0;

string_t* internal_string::new_string(const char* str) {
	if (il2cpp_string_new_addr == 0) {
		il2cpp_string_new_addr = (DWORD64)GetProcAddress(GetModuleHandleA("GameAssembly.dll"), "il2cpp_string_new");
	}

	typedef string_t* (*il2cpp_string_new_fn)(const char* s);

	if (il2cpp_string_new_addr == 0) {
		dbg::fail("cannot find il2cpp_string_new");
		return nullptr;
	}

	return ((il2cpp_string_new_fn)il2cpp_string_new_addr)(str);
}
