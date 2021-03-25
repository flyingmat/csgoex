#pragma once

struct InterfaceReg {
	void* (*m_CreateFn)();
	const char* m_pName;
	InterfaceReg* m_pNext;
};

InterfaceReg* GetInterfaceList(const char* module_name) {
	HMODULE hModule = GetModuleHandleA(module_name);
	if (!hModule)
		return nullptr;

	FARPROC pCaptureInterface = GetProcAddress(hModule, "CreateInterface");

	CloseHandle(hModule);

	if (!pCaptureInterface)
		return nullptr;

	uintptr_t jmp_rel = reinterpret_cast<uintptr_t>(pCaptureInterface) + 0x05;
	uintptr_t pCaptureInterfaceInternal = jmp_rel + 0x04 + *reinterpret_cast<int32_t*>(jmp_rel);

	return **reinterpret_cast<InterfaceReg***>(pCaptureInterfaceInternal + 0x06);
}

void DumpInterfaces(const char* module_name) {
	InterfaceReg* g_pInterfaceReg = GetInterfaceList(module_name);

	while (g_pInterfaceReg) {
		printf("%s\n", g_pInterfaceReg->m_pName);
		g_pInterfaceReg = g_pInterfaceReg->m_pNext;
	}
}

template <class T> T* CaptureInterface(const char* module_name, const char* name, const bool strict = true) {
	InterfaceReg* g_pInterfaceReg = GetInterfaceList(module_name);

	while (g_pInterfaceReg) {
		if ((strict && !strcmp(g_pInterfaceReg->m_pName, name)) || (!strict && strstr(g_pInterfaceReg->m_pName, name)))
			return reinterpret_cast<T*>(g_pInterfaceReg->m_CreateFn());
		g_pInterfaceReg = g_pInterfaceReg->m_pNext;
	}

	return nullptr;
}
