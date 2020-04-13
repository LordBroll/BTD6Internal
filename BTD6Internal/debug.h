#pragma once
#include <cstdarg>
#include <cstdio>
#include <iostream>

namespace dbg {
	__forceinline void log(const char* fmt, ...) {
#ifdef _DEBUG
		va_list args;

		va_start(args, fmt);
		vprintf(fmt, args);
		printf("\n");
		va_end(args);
#endif
	}

	__forceinline void fail(const char* msg) {
#ifdef _DEBUG
		dbg::log("[-] error: %s", msg);
		while (std::cin.get() != '\n') {}
#else
		MessageBoxA(NULL, "error", "error", MB_APPLMODAL | MB_ICONERROR);
#endif

		exit(0);
	}

	__forceinline void alloc_console() {
#ifdef _DEBUG
		AllocConsole();
		SetConsoleCtrlHandler(nullptr, true);

		FILE* f_in;
		FILE* f_out;
		freopen_s(&f_in, "conin$", "r", stdin);
		freopen_s(&f_out, "conout$", "w", stdout);
		freopen_s(&f_out, "conout$", "w", stderr);
		
		SetConsoleTitleA("dbg console");
#endif
	}
}
