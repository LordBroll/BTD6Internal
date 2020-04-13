#pragma once
#include "internals.h"

typedef void* (*constants_get_aes_fn) (void* keyderiver);

/*
typedef string_t* (*passwordgen_get_password_fn) (void* this_obj, int version);
typedef array_t* (*key_deriver_get_bytes_fn) (void* keyderiver, int bytes);
typedef void* (*create_enc_dec_fn) (void* aes, array_t* key, array_t* iv);
typedef array_t* (*get_byte_array_fn) (void* object);
typedef string_t* (*passwordgen_get_password_fn) (void* this_obj, int version);
typedef void (*key_deriver_ctor_fn) (void* this_obj, string_t* password, int salt_size, int iterations);
*/

namespace dumping {
	void hook();

	string_t* passwordgen_get_password_h(void* this_obj, int version);
	void* get_aes_h(void* keyderiver);
}
