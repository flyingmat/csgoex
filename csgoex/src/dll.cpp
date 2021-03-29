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

	while (!vr::VR_IsHmdPresent())
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	printf("HMD Present\n");
	vr::HmdError peError;
	vr_ptr = vr::VR_Init(&peError, vr::VRApplication_Other);
	printf("VR Init | peError: %u\n", peError);

	pIBaseClientDLL = CaptureInterface<IBaseClientDLL>("client.dll", "VClient018");
	pIClientMode = **reinterpret_cast<IClientMode***>((*reinterpret_cast<uintptr_t**>(pIBaseClientDLL))[10] + 5);

	pIDirect3DDevice9 = **reinterpret_cast<IDirect3DDevice9***>(FindPattern("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

	hkIClientMode = std::make_unique<VmtHook>(pIClientMode);
	hkIClientMode->Hook(hkCreateMove, 24);

	ImGui::CreateContext();
	ImGui_ImplWin32_Init(FindWindowA(0, "Counter-Strike: Global Offensive"));
	ImGui_ImplDX9_Init(pIDirect3DDevice9);

	ImGui::StyleColorsLight();
	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);

	hkIDirect3DDevice9 = std::make_unique<VmtHook>(pIDirect3DDevice9);
	hkIDirect3DDevice9->Hook(hkEndScene, 42);

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	delete hkIClientMode.release();
	delete hkIDirect3DDevice9.release();

	vr::VR_Shutdown();

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	FreeConsole();
	fclose(stream);
	FreeLibraryAndExitThread(hinstDLL, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH)
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(DllThread), hinstDLL, NULL, NULL);

	return TRUE;
}
