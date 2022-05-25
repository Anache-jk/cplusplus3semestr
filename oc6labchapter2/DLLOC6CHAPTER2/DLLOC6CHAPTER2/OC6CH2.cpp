#include<Windows.h>
#include<iostream>
using namespace std;
#ifdef __cplusplus
extern "C" {
#endif
	__declspec(dllexport) CRITICAL_SECTION __cdecl CS;
	__declspec(dllexport) int __cdecl counts;
	__declspec(dllexport) HANDLE __cdecl hmutex = CreateMutex(NULL, FALSE, NULL);

	__declspec(dllexport) int __cdecl Threadstring1(LPVOID lpParam) {
		char bruh[] = { "Hello Semen!" };
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < strlen(bruh); j++) {
				cout<<bruh[j];
			}
			cout << endl;
		}
		return 0;
	}
	__declspec(dllexport) int __cdecl Threadstring2(LPVOID lpParam) {
		char bruh[] = { "Hello Alexey!" };
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < strlen(bruh); j++) {
				cout << bruh[j];
			}
			cout << endl;
		}
		return 0;
	}
	__declspec(dllexport) int __cdecl ModThreadstring1(LPVOID lpParam) {
		char bruh[] = { "Hello Semen with CSync!" };

		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < strlen(bruh); j++) {
				cout << bruh[j];
				Sleep(200);
			}
			cout << endl;
		}
		return 0;
	}
	__declspec(dllexport) int __cdecl ModThreadstring2(LPVOID lpParam) {
		char bruh[] = { "Hello Alexey with CSync!" };
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < strlen(bruh); j++) {
				cout << bruh[j];
				Sleep(100);
			}
			cout << endl;
		}
		return 0;
	}
	__declspec(dllexport) int __cdecl CSThreadstring1(LPVOID lpParam) {
		char bruh[] = { "Hello Semen with CSection!" };
		while (counts < 25) {
			EnterCriticalSection(&CS);
			if (counts % 2 == 1) {

				for (int j = 0; j < strlen(bruh); j++) {
					cout << bruh[j];
					Sleep(100);
				}
				cout << endl;
				counts++;
			}
			LeaveCriticalSection(&CS);
		}
		return 0;
	}
	__declspec(dllexport) int __cdecl CSThreadstring2(LPVOID lpParam) {
		char bruh[] = { "Hello Alexey with CSection!" };
		while (counts < 25) {
			EnterCriticalSection(&CS);
			if (counts % 2 == 0) {
				for (int j = 0; j < strlen(bruh); j++) {
					cout << bruh[j];
					Sleep(100);
				}
				cout << endl;
				counts++;
			}
			LeaveCriticalSection(&CS);
		}
		return 0;
	}
	__declspec(dllexport) int __cdecl MutexThreadstring1(LPVOID lpParam) {
		char bruh[] = { "Hello Semen with MUTEX!" };
		while (counts < 25) {
			WaitForSingleObject(hmutex, INFINITE);
			if (counts % 2 == 0) {

				for (int j = 0; j < strlen(bruh); j++) {
					cout << bruh[j];
					Sleep(100);
				}
				cout << endl;
				counts++;
			}
			ReleaseMutex(hmutex);
		}
		return 0;
	}
	__declspec(dllexport) int __cdecl MutexThreadstring2(LPVOID lpParam) {
		char bruh[] = { "Hello Alexey with MUTEX!" };
		while (counts < 25) {
			WaitForSingleObject(hmutex, INFINITE);
			if (counts % 2 == 1) {
				for (int j = 0; j < strlen(bruh); j++) {
					cout << bruh[j];
					Sleep(100);
				}
				cout << endl;
				counts++;
			}
			ReleaseMutex(hmutex);
		}
		return 0;
	}

#ifdef __cplusplus
}
#endif