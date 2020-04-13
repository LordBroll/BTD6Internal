#include "dumping.h"
#include <Windows.h>
#include "detours/detours.h"
#include "addr.h"
#include "debug.h"
#include "dumping_struct.h"

constants_get_aes_fn get_aes_o = nullptr;
void* dumping::get_aes_h(void* keyderiver) {
	kengen_object* keygen = (kengen_object*)keyderiver;

	internal_array::dump_byte_array("m_buffer", keygen->m_buffer);
	internal_array::dump_byte_array("m_salt", keygen->m_salt);
	internal_array::dump_byte_array("m_password", keygen->m_password);
	
	aes_object* aes = (aes_object*)get_aes_o(keyderiver);
	
	return aes;
}

void dumping::hook() {
	get_aes_o = (constants_get_aes_fn)addr::constants_get_aes;
	
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)get_aes_o, (PBYTE)get_aes_h);
	DetourTransactionCommit();
}