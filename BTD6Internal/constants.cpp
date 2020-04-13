#include "constants.h"
#include "internals.h"

string_t* constants::empty;
string_t* constants::anti_url;

std::vector<std::pair<std::string, string_t*>> constants::towers;

void constants::init() {
	empty = internal_string::new_string("");
	anti_url = internal_string::new_string("&!* --COCKhttps://bjalls/`./gov../../../../../../../../../../../../../../../../%00%01%00/btd6internal");

	auto register_tower = [](const char* c) {
		towers.emplace_back(c, internal_string::new_string(c));
	};

	// takes like 5s to dump by just scrolling thru towers in player.cpp
	register_tower("DartMonkey");
	register_tower("BoomerangMonkey");
	register_tower("BombShooter");
	register_tower("TackShooter");
	register_tower("IceMonkey");
	register_tower("GlueGunner");
	register_tower("SniperMonkey");
	register_tower("MonkeySub");
	register_tower("MonkeyBuccaneer");
	register_tower("MonkeyAce");
	register_tower("HeliPilot");
	register_tower("MortarMonkey");
	register_tower("WizardMonkey");
	register_tower("SuperMonkey");
	register_tower("NinjaMonkey");
	register_tower("Alchemist");
	register_tower("Druid");
	register_tower("BananaFarm");
	register_tower("SpikeFactory");
	register_tower("MonkeyVillage");
	register_tower("EngineerMonkey");
}