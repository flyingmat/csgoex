#include "stdafx.h"
#include "dll.hpp"

HINSTANCE dll;
FILE* stream;

VOID WINAPI DllThread(HINSTANCE hinstDLL) {
	if (!AllocConsole())
		return FreeLibraryAndExitThread(hinstDLL, 0);

	if (freopen_s(&stream, "CONOUT$", "w", stdout)) {
		FreeConsole();
		return FreeLibraryAndExitThread(hinstDLL, 0);
	}

	dll = hinstDLL;

	pIBaseClientDLL = CaptureInterface<IBaseClientDLL>("client.dll", "VClient018");
	pIClientMode = **reinterpret_cast<IClientMode***>((*reinterpret_cast<uintptr_t**>(pIBaseClientDLL))[10] + 5);
	pIDirect3DDevice9 = **reinterpret_cast<IDirect3DDevice9***>(FindPattern("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

	hkIClientMode = new VmtHook(pIClientMode);
	hkIDirect3DDevice9 = new VmtHook(pIDirect3DDevice9);

	menu = new Menu(FindWindowA(0, "Counter-Strike: Global Offensive"), pIDirect3DDevice9);

	//hkIClientMode->Hook(hkCreateMove, 24);
	hkIDirect3DDevice9->Hook(hkEndScene, 42);
}

void DllUnload() {
	delete hkIClientMode;
	delete hkIDirect3DDevice9;
	delete menu;

	if (openvr_init)
		vr::VR_Shutdown();

	FreeConsole();
	fclose(stream);
	FreeLibraryAndExitThread(dll, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(DllThread), hinstDLL, NULL, NULL);

	return TRUE;
}
