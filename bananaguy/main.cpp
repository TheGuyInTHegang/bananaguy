#include <Windows.h>
#include <iostream>
#include <ctime>
#include <thread>
#include <tlhelp32.h>



int main() {

	INPUT input[4] = {};
	HANDLE snapshot = 0;
	PROCESSENTRY32 pe32 = { 0 };
	HANDLE process = nullptr;
	DWORD exitCode = 0;
	uintptr_t processId = 0;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	BYTE * client = 0;
	uintptr_t clientBaseAddr = 0;


	snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	Process32First(snapshot, &pe32);

	do {

		if (wcscmp(pe32.szExeFile, L"Banana Shooter.exe") == 0) {

			printf("Banana found man");
			processId = pe32.th32ProcessID;
			process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID);


		}
	} while (Process32Next(snapshot, &pe32));

	CloseHandle(snapshot);

	HANDLE Msnapshot = 0;
	MODULEENTRY32 me32 = { 0 };
	me32.dwSize = sizeof(MODULEENTRY32);
	Msnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processId);

	
	Module32First(Msnapshot, &me32);
	while (Module32Next(Msnapshot, &me32))
	{

		printf("%ws \n", me32.szModule);
		if (wcscmp(me32.szModule, L"GameAssembly.dll") == 0) {

			printf("The client dll is found man");
			//client = me32.modBaseAddr;
			client = me32.modBaseAddr;
			printf("ModuleEntry32.szModule= %S\n", me32.szModule);
			printf("dwModuleBaseAddress= %p\n", client);
			printf("dwModuleBaseAddress= %p\n", me32.modBaseAddr);
			

			break;
		}
	}
	
	CloseHandle(Msnapshot);

	int count = 0;
	uintptr_t onEnemy = 0;
	uintptr_t address = (uintptr_t)client + 0x029616f0;


	while (true) {

		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		ReadProcessMemory(process, (void*)address, &onEnemy, 8, NULL);

		onEnemy += 0xB8;

		ReadProcessMemory(process, (void*)onEnemy, &onEnemy, 8, NULL);

		onEnemy += 0x0;

		ReadProcessMemory(process, (void*)onEnemy, &onEnemy, 8, NULL);

		onEnemy += 0x28;

		ReadProcessMemory(process, (void*)onEnemy, &onEnemy, 8, NULL);

		onEnemy += 0x58;

		ReadProcessMemory(process, (void*)onEnemy, &onEnemy, 8, NULL);

		onEnemy += 0x10;

		ReadProcessMemory(process, (void*)onEnemy, &onEnemy, 8, NULL);

		onEnemy += 0xF0;

		ReadProcessMemory(process, (void*)onEnemy, &onEnemy, 8, NULL);

		onEnemy += 0x4560;

		ReadProcessMemory(process, (void*)onEnemy, &onEnemy, 8, NULL);

		if (onEnemy == 1) {

			count += 1;
			input[0].type = INPUT_MOUSE;
			input[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(ARRAYSIZE(input), input, sizeof(input));
		}

		else {

			input[0].type = INPUT_MOUSE;
			input[0].mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, input, sizeof(INPUT));

		}

		if (count == 10) {

			input[0].type = INPUT_KEYBOARD;
			input[0].ki.wVk = VK_LWIN;

			input[1].type = INPUT_KEYBOARD;
			input[1].ki.wVk = 'D';
		}
	}	



	return 0;

}