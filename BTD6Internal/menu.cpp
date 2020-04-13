#include "menu.h"

#include "addr.h"
#include "bloon_map.h"
#include "debug.h"
#include "imgui/imgui.h"
#include "player.h"
#include "simulation.h"
#include "dumping.h"
#include "constants.h"
#include "cheat_engine.h"

void menu::draw() {
	simulation_object* sim = simulation::obj();

	ImGui::Begin("btd6 internal");

	ImGui::BeginTabBar("##tabs");

	if (ImGui::BeginTabItem("abuot")) {
		ImGui::TextDisabled("bloons td 6 internal cheat");
		ImGui::TextDisabled("written by vadmeme");
		
		ImGui::EndTabItem();
	}
	
	if (ImGui::BeginTabItem("map")) {
		ImGui::Checkbox("place anywhere", &bloon_map::place_anywhere);

		ImGui::EndTabItem();
	}
	
	if(ImGui::BeginTabItem("konfuse")) {
		ImGui::TextDisabled("forces all encrypted values to a certian number");
		
		ImGui::Checkbox("force values", &(konfuse_module::force_values));
		ImGui::SliderInt("##force_to", &(konfuse_module::forced_value), 1, 1000000, "force to: %d");
		
		ImGui::EndTabItem();
	}

	if(sim) {
		if (ImGui::BeginTabItem("game: basic")) {
			ImGui::TextDisabled("allows for editing of basic in-game features");
			
			static int wanted_cash = 50000;
			ImGui::SliderInt("##cash", &wanted_cash, 1, 1000000, "$%d");
			
			ImGui::SameLine();
			if (ImGui::Button("add")) {
				simulation::set_cash(simulation::get_cash(-1) + wanted_cash, -1);
			}

			if (konfuse_module::forced_hp > 1) {
				ImGui::SliderInt("##hp", &konfuse_module::forced_hp, 1, 10000, "force lives: %d hp");
			} else {
				ImGui::SliderInt("##hp", &konfuse_module::forced_hp, 1, 10000, "force lives: off");
			}

			if (konfuse_module::forced_shield > 1) {
				ImGui::SliderInt("##shield", &konfuse_module::forced_shield, 1, 10000, "force shield: %d hp");
			} else {
				ImGui::SliderInt("##hp", &konfuse_module::forced_shield, 1, 10000, "force shield: off");
			}

			ImGui::EndTabItem();
		}
		
		if (ImGui::BeginTabItem("game: flags")) {
			ImGui::TextDisabled("allows for editing of internal flags in game");
			
			ImGui::Checkbox("flag: debug", &sim->debugOptions);
			ImGui::Checkbox("flag: no lives lost", &sim->noLivesLost);
			ImGui::Checkbox("flag: instant cooldowns", &sim->instantCooldowns);
			ImGui::Checkbox("flag: can earn xp", &sim->canEarnXP);
			ImGui::Checkbox("flag: pause weapons", &sim->pauseWeapons);
			ImGui::Checkbox("flag: double cash", &sim->doubleCash);

			ImGui::EndTabItem();
		}
	}

	if (ImGui::BeginTabItem("cheat engine")) {
		ImGui::TextDisabled("allows for editing encrypted values directly");

		ImGui::Columns(4, "cheat_engine");
		ImGui::Separator();
		ImGui::Text("address"); ImGui::NextColumn();
		ImGui::Text("desc"); ImGui::NextColumn();
		ImGui::Text("value"); ImGui::NextColumn();
		ImGui::Text("override"); ImGui::NextColumn();
		ImGui::Separator();

		static char desc_search[128] = "";
		static int value_search = 0;
		static int override_search = 0;

		auto matches_search = [](cheat_engine_value v) -> bool {
			if (strlen(desc_search) > 0) {
				return strstr(v.desc, desc_search) != nullptr;
			}

			if (value_search != 0) {
				return floor(v.last_read) == value_search;
			}

			if (override_search != 0) {
				return floor(v.override) == override_search;
			}

			return true;
		};

		ImGui::NextColumn();

		ImGui::InputText("##text_search", desc_search, 128);
		ImGui::NextColumn();

		ImGui::SliderInt("##value_search", &value_search, 1, 10000, "search: %.3f");
		ImGui::NextColumn();

		ImGui::SliderInt("##override_search", &override_search, 1, 10000, "search: %.3f");
		ImGui::NextColumn();

		ImGui::Separator();

		int id = 0;
		std::map<void*, cheat_engine_value>& m = cheat_engine::map();
		std::map<void*, cheat_engine_value>::iterator it;

		for (it = m.begin(); it != m.end(); it++) {

			if (!matches_search(it->second)) {
				continue;
			}

			ImGui::PushID(id++);
			ImGui::Text("%p", it->first);
			ImGui::PopID();
			ImGui::NextColumn();

			ImGui::PushID(id++);
			ImGui::InputText("##text", it->second.desc, 128);
			ImGui::PopID();
			ImGui::NextColumn();

			ImGui::PushID(id++);
			ImGui::Text("%f (%d)", it->second.last_read, (int)floor(it->second.last_read));

			if (ImGui::IsItemHovered() && ImGui::IsAnyMouseDown()) {
				it->second.override = it->second.last_read;
			}

			ImGui::PopID();
			ImGui::NextColumn();

			ImGui::PushID(id++);
			float temp = it->second.override;
			ImGui::SliderFloat("##slider", &temp, 1, 10000);
			it->second.override = temp;
			ImGui::PopID();
			ImGui::NextColumn();
		}

		ImGui::EndTabItem();
	}
	
	ImGui::EndTabBar();
	
	ImGui::End();
}

void menu::overlay() {
	ImGui::GetForegroundDrawList()->AddText({ 11, 11 }, ImColor(0, 0, 0), "btd6 internal");
	ImGui::GetForegroundDrawList()->AddText({ 10, 10 }, ImColor(255, 0, 0), "btd6 internal");
}
