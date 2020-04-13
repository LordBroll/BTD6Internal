#include "dx.h"

#include <d3d11.h>

#include "debug.h"
#pragma comment(lib, "d3d11.lib")

#include "detours/detours.h"
#include "menu_internal.h"

bool did_dx_init = false;

ID3D11Device* d3d_device = nullptr;
ID3D11DeviceContext* d3d_ctx = nullptr;
DXGI_SWAP_CHAIN_DESC d3d_swap_desc;

D3D11PresentFn d3d11_preset_o;
HRESULT __stdcall dx::d3d11_preset_h(IDXGISwapChain* swap_chain, UINT sync_interval, UINT flags) {
	if(!did_dx_init) {
		did_dx_init = true;

		if(FAILED(swap_chain->GetDesc(&d3d_swap_desc))) {
			dbg::fail("failed to get swap chain desc on d3d hook");
		}

		if (SUCCEEDED(swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&d3d_device))) {
			swap_chain->GetDevice(__uuidof(d3d_device), (void**)&d3d_device);
			d3d_device->GetImmediateContext(&d3d_ctx);

			dbg::log("[+] got games d3d device and context");
		} else {
			dbg::fail("failed to get device on d3d hook");
		}
	}

	menu_internal::on_preset(swap_chain, d3d_device, d3d_ctx);
	
	return d3d11_preset_o(swap_chain, sync_interval, flags);
}

bool dx::hook() {
	dbg::log("[+] starting dx11 hook");
	
	IDXGISwapChain* swap_chain;

	WNDCLASSEXA wnd_class = { sizeof(WNDCLASSEX), CS_CLASSDC, [](HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) -> LRESULT {
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "_", NULL };

	RegisterClassExA(&wnd_class);

	HWND fake_hwnd = CreateWindowA(wnd_class.lpszClassName, NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wnd_class.hInstance, NULL);

	D3D_FEATURE_LEVEL requested_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtained_level;
	ID3D11Device* temp_d3d_device = nullptr;
	ID3D11DeviceContext* temp_d3d_ctx = nullptr;

	DXGI_SWAP_CHAIN_DESC chain_desc;
	ZeroMemory(&chain_desc, sizeof(chain_desc));
	chain_desc.BufferCount = 1;
	chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	chain_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	chain_desc.OutputWindow = fake_hwnd;
	chain_desc.SampleDesc.Count = 1;
	chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	chain_desc.Windowed = ((GetWindowLongPtr(fake_hwnd, GWL_STYLE) & WS_POPUP) != 0) ? false : true;

	chain_desc.BufferDesc.Width = 1;
	chain_desc.BufferDesc.Height = 1;
	chain_desc.BufferDesc.RefreshRate.Numerator = 0;
	chain_desc.BufferDesc.RefreshRate.Denominator = 1;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		requested_levels,
		sizeof(requested_levels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&chain_desc,
		&swap_chain,
		&temp_d3d_device,
		&obtained_level,
		&temp_d3d_ctx
	))) {
		dbg::log("[-] error: failed to create temp d3d11 device");
		return false;
	}

	DWORD_PTR* swap_chain_vt = (DWORD_PTR*)swap_chain;
	swap_chain_vt = (DWORD_PTR*)swap_chain_vt[0];

	if(swap_chain_vt == nullptr) {
		dbg::log("[-] error: swap chain vtable nullptr");
		return false;
	}

	d3d11_preset_o = (D3D11PresentFn)(DWORD_PTR*)swap_chain_vt[8];
	dbg::log("[+] d3d11 preset @ %p", d3d11_preset_o);
	
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(LPVOID&)d3d11_preset_o, (PBYTE)d3d11_preset_h);
	DetourTransactionCommit();

	temp_d3d_ctx->Release();
	temp_d3d_device->Release();
	swap_chain->Release();

	UnregisterClassA(wnd_class.lpszClassName, wnd_class.hInstance);
	CloseWindow(fake_hwnd);
}

DXGI_SWAP_CHAIN_DESC dx::chain_desc() {
	return d3d_swap_desc;
}
