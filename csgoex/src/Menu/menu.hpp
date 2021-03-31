#pragma once

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void DllUnload();

class Menu {
private:
	HWND hWnd;
	IDirect3DDevice9* pDevice;

	__forceinline void InitStyle() {
		ImGui::StyleColorsLight();
		ImGuiStyle* style = &ImGui::GetStyle();
		style->Colors[ImGuiCol_WindowBg] = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);
	}


	char openvr_message[64];

public:
	WNDPROC oWndProc;

	bool enabled;

	Menu(HWND hWnd, IDirect3DDevice9* pDevice) : hWnd(hWnd), pDevice(pDevice) {
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(hWnd);
		ImGui_ImplDX9_Init(pDevice);
		
		this->InitStyle();

		oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWnd, GWLP_WNDPROC, LONG_PTR(hkWndProc)));

		sprintf_s(openvr_message, "Click to initialize OpenVR");
	}

	~Menu() {
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, LONG_PTR(oWndProc));

		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}

	bool HandleInput(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (uMsg == WM_KEYUP && wParam == VK_END)
			return CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)DllUnload, NULL, 0, NULL);

		if (uMsg == WM_KEYUP && wParam == VK_INSERT)
			this->enabled = !this->enabled;

		if (this->enabled && (uMsg == WM_MOUSEMOVE || uMsg == WM_LBUTTONDOWN || uMsg == WM_LBUTTONUP || uMsg == WM_LBUTTONDBLCLK || uMsg == WM_MOUSEWHEEL)) {
			ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
			return true;
		}
		else
			return false;
	}

	__forceinline void Render() {
		if (this->enabled) {
			ImGui::SetNextWindowSize(ImVec2(600, 300));
			ImGui::Begin("Settings");

			if (ImGui::Button("Init OpenVR")) {
				if (!openvr_init) {
					vr::HmdError result = OpenVR_Init();
					if (result == vr::VRInitError_None)
						sprintf_s(openvr_message, "Success!");
					else
						sprintf_s(openvr_message, "Error %u", result);
				}
				else
					sprintf_s(openvr_message, "OpenVR is already initialized!");
			}
			ImGui::SameLine();
			ImGui::Text(openvr_message);

			ImGui::End();
		}
	}
};

extern Menu* menu;

LRESULT __stdcall hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (menu->HandleInput(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(menu->oWndProc, hWnd, uMsg, wParam, lParam);
}
