#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <time.h>
#include<Windows.h>
#include<string>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <memory.h>
#include<AclAPI.h>

const char* menu =
"Choose what you want"
"\n"
"1. Create two THREAD\n"
"2. Create two thread but with problem of SYNCHRONIZATION\n"
"3. Create two synchronization thread with CRITICAL SECTION\n"
"4. Create two synchronization thread with MUTEX\n"
"5. EXIT\n";

using namespace std;
typedef int(__cdecl* FunThreadstring1)(LPVOID lpParam);
typedef int(__cdecl* FunThreadstring2)(LPVOID lpParam);
typedef int(__cdecl* FunModThreadstring1)(LPVOID lpParam);
typedef int(__cdecl* FunModThreadstring2)(LPVOID lpParam);
typedef int(__cdecl* FunCSThreadstring1)(LPVOID lpParam);
typedef int(__cdecl* FunCSThreadstring2)(LPVOID lpParam);
typedef int(__cdecl* FunMutexThreadstring1)(LPVOID lpParam);
typedef int(__cdecl* FunMutexThreadstring2)(LPVOID lpParam);
typedef void(__cdecl* FUNCS)(void);
typedef void(__cdecl* FUNhmutex)(void);
int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
    HMODULE hModule;
    hModule = LoadLibrary(TEXT("C:\\Users\\Simon\\Desktop\\DLLOC6CHAPTER2\\Debug\\DLLOC6CHAPTER2.dll"));
    if (hModule == NULL) {
        cout << "Library hasnt load. Error - "<<GetLastError()<<endl;
    }
    cout << "Library has load successful" << endl;
    FunThreadstring1 Threadstring1 = (FunThreadstring1)GetProcAddress(hModule, "Threadstring1");
    FunThreadstring2 Threadstring2 = (FunThreadstring2)GetProcAddress(hModule, "Threadstring2");
    FunModThreadstring1 ModThreadstring1 = (FunModThreadstring1)GetProcAddress(hModule, "ModThreadstring1");
    FunModThreadstring2 ModThreadstring2 = (FunModThreadstring2)GetProcAddress(hModule, "ModThreadstring2");
    FunCSThreadstring1 CSThreadstring1 = (FunCSThreadstring1)GetProcAddress(hModule, "CSThreadstring1");
    FunCSThreadstring2 CSThreadstring2 = (FunCSThreadstring2)GetProcAddress(hModule, "CSThreadstring2");
    FunMutexThreadstring1 MutexThreadstring1 = (FunMutexThreadstring1)GetProcAddress(hModule, "MutexThreadstring1");
    FunMutexThreadstring1 MutexThreadstring2 = (FunMutexThreadstring2)GetProcAddress(hModule, "MutexThreadstring2");
    FUNCS CS = (FUNCS)GetProcAddress(hModule, "CS");
    HANDLE hmutex = (HANDLE)GetProcAddress(hModule, "hmutex");
    HANDLE hthread1, hthread2;
    DWORD threadid1, threadid2;
    int choice, i, checkstr, incheck = 1;
    char secchoice;
    do {
        cout << menu;
        cin >> choice;
        while (!choice && choice != 0 || (cin.peek() != '\n')) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "\n Print again(without symbols): ";
            cin >> choice;
        }
        cin.ignore();
        cout << endl;
        system("cls");
        switch (choice) {
        case 1: {
            hthread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Threadstring1, NULL, 0, &threadid1);
            hthread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Threadstring2, NULL, 0, &threadid2);
            WaitForSingleObject(hthread1, INFINITE);
            WaitForSingleObject(hthread2, INFINITE);
            CloseHandle(hthread1);
            CloseHandle(hthread2);
            hthread1 = NULL;
            hthread2 = NULL;
            break;
        }
        case 2: {
            hthread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ModThreadstring1, NULL, 0, &threadid1);
            hthread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ModThreadstring2, NULL, 0, &threadid2);
            WaitForSingleObject(hthread1, INFINITE);
            WaitForSingleObject(hthread2, INFINITE);
            CloseHandle(hthread1);
            CloseHandle(hthread2);
            hthread1 = NULL;
            hthread2 = NULL;
            break;
        }
        case 3: {
            InitializeCriticalSection((LPCRITICAL_SECTION)CS);
            hthread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CSThreadstring1, NULL, 0, NULL);
            hthread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CSThreadstring2, NULL, 0, NULL);
            WaitForSingleObject(hthread1, INFINITE);
            WaitForSingleObject(hthread2, INFINITE);
            CloseHandle(hthread1);
            CloseHandle(hthread2);
            DeleteCriticalSection((LPCRITICAL_SECTION)CS);
            hthread1 = NULL;
            hthread2 = NULL;
            break;
        }
        case 4: {
            hthread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MutexThreadstring1, NULL, 0, &threadid1);
            hthread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MutexThreadstring2, NULL, 0, &threadid2);
          hmutex = CreateMutex(NULL, FALSE, NULL);
            WaitForSingleObject(hthread1, INFINITE);
            WaitForSingleObject(hthread2, INFINITE);
            CloseHandle(hthread1);
            CloseHandle(hthread2);
            hthread1 = NULL;
            hthread2 = NULL;
            break;
        }
        case 5: {
            break;
        }
        default:
            cout << "\nChoose again\n\n";
        }
    } while (choice != 5);
    FreeLibrary(hModule);
}