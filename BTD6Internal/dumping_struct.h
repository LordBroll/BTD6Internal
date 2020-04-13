#pragma once
#include <cstdint>

#include "internals.h"

struct aes_object {
public:
	char pad_0000[16]; //0x0000
	int32_t BlockSizeValue; //0x0010
	int32_t FeedbackSizeValue; //0x0014
	array_t* IVValue; //0x0018
	array_t* KeyValue; //0x0020
	array_t* LegalBlockSizesValue; //0x0028
	array_t* LegalKeySizesValue; //0x0030
	int32_t KeySizeValue; //0x0038
	int32_t ModeValue; //0x003C
	int32_t PaddingValue; //0x0040
}; //Size: 0x0044

struct kengen_object {
public:
	char pad_0000[16]; //0x0000
	array_t* m_buffer; //0x0010
	array_t* m_salt; //0x0018
	void* m_hmacsha1; //0x0020
	array_t* m_password; //0x0028
	uint32_t m_iterations; //0x0030
	uint32_t m_block; //0x0034
	int32_t m_startIndex; //0x0038
	int32_t m_endIndex; //0x003C
}; //Size: 0x0040