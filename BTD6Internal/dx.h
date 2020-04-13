#pragma once
#include <Windows.h>
#include <d3d11.h>

typedef HRESULT(__stdcall* D3D11PresentFn) (IDXGISwapChain* swap_chain, UINT sync_interval, UINT flags);

namespace dx {
	bool hook();

	DXGI_SWAP_CHAIN_DESC chain_desc();

	HRESULT __stdcall d3d11_preset_h(IDXGISwapChain* swap_chain, UINT sync_interval, UINT flags);
}
