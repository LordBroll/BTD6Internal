#include "menu_internal.h"


#include "debug.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"

#include "dx.h"
#include "imgui/imgui_impl_dx11.h"
#include "menu.h"

bool did_menu_init = false;
HWND game_window;

bool show_menu = false;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
WNDPROC game_wndproc_o = nullptr;

ID3D11RenderTargetView* target_view;

LRESULT menu_internal::game_wndproc_h(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
	if (msg == WM_KEYDOWN && w_param == VK_INSERT) {
		show_menu = !show_menu;
	}
	
	if(show_menu) {
		ImGui_ImplWin32_WndProcHandler(hwnd, msg, w_param, l_param);
		return true;
	}

	return CallWindowProc(game_wndproc_o, hwnd, msg, w_param, l_param);
}

void menu_internal::on_preset(IDXGISwapChain* swap_chain, ID3D11Device* d3d_device, ID3D11DeviceContext* d3d_ctx) {
	if (!did_menu_init) {
		did_menu_init = true;

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ImeWindowHandle = game_window;
		
		game_window = dx::chain_desc().OutputWindow;
		game_wndproc_o = (WNDPROC)SetWindowLongPtr(game_window, GWLP_WNDPROC, (LONG_PTR)game_wndproc_h);

		ID3D11Texture2D* target_texture;
		if (SUCCEEDED(swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&target_texture))) {
			d3d_device->CreateRenderTargetView(target_texture, NULL, &target_view);
			target_texture->Release();
		} else {
			dbg::fail("failed to get render target view");
		}

		IMGUI_CHECKVERSION();


		ImGui::CreateContext();
		ImGui_ImplWin32_Init(game_window);
		ImGui_ImplDX11_Init(d3d_device, d3d_ctx);
		ImGui_ImplDX11_CreateDeviceObjects();

		ImGuiStyle* style = &ImGui::GetStyle();

		style->ChildRounding = 0;
		style->FrameRounding = 0;
		style->GrabRounding = 0;
		style->PopupRounding = 0;
		style->TabRounding = 0;
		style->WindowRounding = 0;
		style->ScrollbarRounding = 0;
		
		ImVec4* colors = style->Colors;

		colors[ImGuiCol_Text] = ImVec4(0.921569, 0.921569, 0.921569, 1.000000);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.619608, 0.619608, 0.619608, 1.000000);
		colors[ImGuiCol_WindowBg] = ImVec4(0.054902, 0.054902, 0.054902, 1.000000);
		colors[ImGuiCol_ChildBg] = ImVec4(0.054902, 0.054902, 0.054902, 1.000000);
		colors[ImGuiCol_PopupBg] = ImVec4(0.054902, 0.054902, 0.054902, 1.050980);
		colors[ImGuiCol_Border] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_BorderShadow] = ImVec4(1.000000, 0.999997, 0.999990, 1.000000);
		colors[ImGuiCol_FrameBg] = ImVec4(0.098039, 0.098039, 0.098039, 1.000000);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.274510, 0.274510, 0.274510, 1.000000);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.321569, 0.321569, 0.321569, 1.000000);
		colors[ImGuiCol_TitleBg] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.000000, 0.980000, 0.950000, 0.750000);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.054902, 0.054902, 0.054902, 1.000000);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.062745, 0.062745, 0.062745, 1.100000);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.274510, 0.274510, 0.274510, 1.000000);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.321569, 0.321569, 0.321569, 1.000000);
		colors[ImGuiCol_CheckMark] = ImVec4(0.419608, 0.419608, 0.419608, 1.000000);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.321569, 0.321569, 0.321569, 1.000000);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_Button] = ImVec4(0.200000, 0.199998, 0.199998, 1.000000);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.222857, 0.222855, 0.222855, 1.000000);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.200000, 0.199998, 0.199998, 1.000000);
		colors[ImGuiCol_Header] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.274510, 0.274510, 0.274510, 1.000000);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.321569, 0.321569, 0.321569, 1.000000);
		colors[ImGuiCol_Separator] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.274510, 0.274510, 0.274510, 1.000000);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.321569, 0.321569, 0.321569, 1.000000);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.274510, 0.274510, 0.274510, 1.000000);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.321569, 0.321569, 0.321569, 1.000000);
		colors[ImGuiCol_Tab] = ImVec4(0.160000, 0.159086, 0.159086, 1.000000);
		colors[ImGuiCol_TabHovered] = ImVec4(0.211429, 0.207804, 0.207804, 1.000000);
		colors[ImGuiCol_TabActive] = ImVec4(0.268571, 0.268569, 0.268569, 1.000000);
		colors[ImGuiCol_TabUnfocused] = ImVec4(0.068000, 0.102000, 0.148000, 0.972400);
		colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.136000, 0.262000, 0.424000, 1.000000);
		colors[ImGuiCol_PlotLines] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.274510, 0.274510, 0.274510, 1.000000);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.235294, 0.235294, 0.235294, 1.000000);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.274510, 0.274510, 0.274510, 1.000000);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.274510, 0.274510, 0.274510, 1.000000);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.000000, 1.000000, 0.000000, 0.900000);
		colors[ImGuiCol_NavHighlight] = ImVec4(0.260000, 0.590000, 0.980000, 1.000000);
		colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.921569, 0.921569, 0.921569, 0.700000);
		colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.721569, 0.721569, 0.721569, 0.200000);
		colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.000000, 0.000000, 0.000000, 0.750000);
	}

	d3d_ctx->OMSetRenderTargets(1, &target_view, NULL);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if(show_menu) {
		menu::draw();
	}

	menu::overlay();

	ImGui::Render();

	d3d_ctx->OMSetRenderTargets(1, &target_view, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}