#pragma once

#include <intrin.h>
#pragma intrinsic(_ReturnAddress)

typedef HRESULT(__stdcall* EndScene_t) (IDirect3DDevice9*);

HRESULT __stdcall hkEndScene(IDirect3DDevice9* thisptr) {
	EndScene_t oEndScene = hkIDirect3DDevice9->GetOriginalFunction<EndScene_t>(42);
	uintptr_t rtn = reinterpret_cast<uintptr_t>(_ReturnAddress());

	// avoid drawing over external overlays e.g. steam or discord
	if ((rtn & 0xFFFF) != 0xFAD3)
		return oEndScene(thisptr);

	// always render, some windows may be active at all times e.g. debug information,
	// this is easier and shouldn't drop too many frames
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	
	menu->Render();

	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return oEndScene(thisptr);
}
