#include "stdafx.h"
#define PROCESSNAME L"csgo.exe"
#define DLLNAME L"csgoex.dll"

inline HANDLE GetProcessHandle(const wchar_t* process_name) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	do {
		if (!wcscmp(pe32.szExeFile, process_name))
			return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);
	} while (Process32Next(hProcessSnap, &pe32));

	return nullptr;
}

inline LPVOID DllPathAlloc(HANDLE* hProcess, const wchar_t* dll_name) {
	std::wstring dllPath = std::filesystem::canonical(dll_name).wstring();

	LPVOID pDllBaseAddress = VirtualAllocEx(*hProcess, NULL, dllPath.size() * 2, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	if (pDllBaseAddress)
		if (!WriteProcessMemory(*hProcess, pDllBaseAddress, dllPath.c_str(), dllPath.size() * 2, nullptr))
			return nullptr;

	return pDllBaseAddress;
}

int main() {
	HANDLE hProcess = GetProcessHandle(PROCESSNAME);
	if (!hProcess)
		return 1;

	LPVOID pDllBaseAddress = DllPathAlloc(&hProcess, DLLNAME);
	if (!pDllBaseAddress) {
		CloseHandle(hProcess);
		return 2;
	}

	HANDLE hDllThread = CreateRemoteThread(hProcess, NULL, NULL, LPTHREAD_START_ROUTINE(LoadLibrary), pDllBaseAddress, NULL, NULL);
	if (!hDllThread) {
		CloseHandle(hProcess);
		return 3;
	}

	DWORD result = WaitForSingleObject(hDllThread, 2000);
	
	CloseHandle(hProcess);
	CloseHandle(hDllThread);

	if (result != WAIT_OBJECT_0)
		return 4;

	return 0;
}
