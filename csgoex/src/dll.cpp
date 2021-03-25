#include "stdafx.h"

VOID WINAPI DllThread(HINSTANCE hinstDLL) {
	if (!AllocConsole())
		return FreeLibraryAndExitThread(hinstDLL, 0);

	FILE* stream;
	if (freopen_s(&stream, "CONOUT$", "w", stdout)) {
		FreeConsole();
		return FreeLibraryAndExitThread(hinstDLL, 0);
	}

	printf("Hello World!\n");
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(DllThread), hinstDLL, NULL, NULL);

	return TRUE;
}
