#pragma once
#include <d3d11.h>

namespace menu_internal {
	void on_preset(IDXGISwapChain* swap_chain, ID3D11Device* d3d_device, ID3D11DeviceContext* d3d_ctx);
	LRESULT CALLBACK game_wndproc_h(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
}
