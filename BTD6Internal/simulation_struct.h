#pragma once
#include <cstdint>

#include "konfuse.h"

enum cash_type {
	Normal = 0,
	Powers = 1,
	Ability = 2,
	EndOfRound = 3,
	NonTransformed = 4,
	CoopCash = 5
};

class simulation_object {
public:
	uint8_t _pad[16]; //0x0000
	void* entity; //0x0010
	void* model; //0x0018
	int32_t idNext; //0x0020
	int32_t localIdNext; //0x0024
	void* time; //0x0028
	void* roundTime; //0x0030
	bool canEarnXP; //0x0038
	bool debugOptions; //0x0039
	bool instantCooldowns; //0x003A
	bool pauseWeapons; //0x003B
	int32_t mostTowersAtOnce; //0x003C
	void* factory; //0x0040
	void* bloonManager; //0x0048
	void* towerManager; //0x0050
	void* _inputManager; //0x0058
	void* towerInventories; //0x0060
	void* placementAreas; //0x0068
	void* cashInventories; //0x0070
	void* cashManagers; //0x0078
	void* audioManager; //0x0080
	void* inGameMusicBehavior; //0x0088
	void* coopManager; //0x0090
	void* skinManagerSim; //0x0098
	void* trackArrowManager; //0x00A0
	void* progressiveDifficultyManager; //0x00A8
	void* audioLimiterManager; //0x00B0
	void* collisionChecker; //0x00B8
	void* powerManager; //0x00C0
	void* effectLimitManager; //0x00C8
	void* analyticsTrackerSimManager; //0x00D0
	void* process; //0x00D8
	double endOnRoundAdditionalTime; //0x00E0
	void* actions; //0x00E8
	void* throwawayEffects; //0x00F0
	bool hasCashChanged; //0x00F8
	bool hasHealthChanged; //0x00F9
	bool doubleCash; //0x00FA
	bool alternateHeliControls; //0x00FB
	uint8_t __pad[140]; //0x00FC
	int32_t showCancel; //0x0188
	int32_t roundEndPauseCount; //0x018C
	int64_t immunity; //0x0190
	konfuse* maxHealthIncrease; //0x0198
	char* difficultyId; //0x01A0
	konfuse* startingHealth; //0x01A8
	konfuse* softcapHealthPercentModifier; //0x01B0
	konfuse* maxSoftcapHealth; //0x01B8
	konfuse* maxHealth; //0x01C0
	konfuse* maxShield; //0x01C8
	konfuse* raceStartTimeStamp; //0x01D0
	konfuse* raceFinishTimeStamp; //0x01D8
	char* helperMessage; //0x01E0
	char* unlocalizedhelperMessage; //0x01E8
	void* heroOverride; //0x01F0
	bool gameStarted; //0x01F8
	bool gameWon; //0x01F9
	bool gameLost; //0x01FA
	bool noLivesLost; //0x01FB
	int32_t ___pad; //0x01FC
	void* behaviorCache; //0x0200
	void* sharedTowerGrid; //0x0208
	konfuse* shield; //0x0210
	konfuse* health; //0x0218
	void* map; //0x0220
	void* random; //0x0228
	void* unsyncedRandom; //0x023
};
