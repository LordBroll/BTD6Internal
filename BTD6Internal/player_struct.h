#pragma once
#include "konfuse.h"

struct player_profile {
public:
	char pad_0000[272]; //0x0000
	konfuse* monkeyMoney; //0x0110
	konfuse* xp; //0x0118
	konfuse* trophies; //0x0120
	konfuse* knowledgePoints; //0x0128
	konfuse* rank; //0x0130
}; //Size: 0x0138

struct player_object {
public:
	char pad_0000[16]; //0x0000
	void* CheckingPlaySessionEvent; //0x0010
	void* CheckingEtagEvent; //0x0018
	void* SavingDataEvent; //0x0020
	void* SyncDoneEvent; //0x0028
	void* CheckPlaySessionDoneEvent; //0x0030
	void* PlaySessionConflictEvent; //0x0038
	void* DataConflictEvent; //0x0040
	void* ErrorEvent; //0x0048
	void* DataInvalidatedEvent; //0x0050
	player_profile* PlayerData; //0x0058
}; //Size: 0x0060