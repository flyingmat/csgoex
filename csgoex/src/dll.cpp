#include "stdafx.h"
#include "dll.hpp"

VOID WINAPI DllThread(HINSTANCE hinstDLL) {
	if (!AllocConsole())
		return FreeLibraryAndExitThread(hinstDLL, 0);

	FILE* stream;
	if (freopen_s(&stream, "CONOUT$", "w", stdout)) {
		FreeConsole();
		return FreeLibraryAndExitThread(hinstDLL, 0);
	}

	printf("Hello World!\n");

	while (!GetAsyncKeyState(VK_END)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	FreeConsole();
	fclose(stream);
	FreeLibraryAndExitThread(hinstDLL, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(DllThread), hinstDLL, NULL, NULL);

	return TRUE;
}
