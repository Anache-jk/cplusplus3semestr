#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <time.h>
#include<Windows.h>
#include<string>
#include <conio.h>
#include <memory.h>
#include<AclAPI.h>
#include "functions.h"
const char* menu =
"Choose what you want"
"\n"
"1. Create two THREAD\n"
"2. Create two thread but with problem of SYNCHRONIZATION\n"
"3. Create two synchronization thread with CRITICAL SECTION\n"
"4. Create two synchronization thread with MUTEX\n"
"5. EXIT\n";


using namespace std;


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
  
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
            hthread1 = CreateThread(NULL, 0, Threadstring1, NULL, 0, &threadid1);
            hthread2 = CreateThread(NULL, 0, Threadstring2, NULL, 0, &threadid2);

            WaitForSingleObject(hthread1, INFINITE);
            WaitForSingleObject(hthread2, INFINITE);

            CloseHandle(hthread1);
            CloseHandle(hthread2);
            hthread1 = NULL;
            hthread2 = NULL;
            break;
        }
        case 2: {
            hthread1 = CreateThread(NULL, 0, ModThreadstring1, NULL, 0, &threadid1);
            hthread2 = CreateThread(NULL, 0, ModThreadstring2, NULL, 0, &threadid2);

            WaitForSingleObject(hthread1, INFINITE);
            WaitForSingleObject(hthread2, INFINITE);

            CloseHandle(hthread1);
            CloseHandle(hthread2);

            hthread1 = NULL;
            hthread2 = NULL;
            break;
        }
        case 3: {
            InitializeCriticalSection(&CS);

            hthread1 = CreateThread(NULL, 0, CSThreadstring1, NULL, 0, &threadid1);
            hthread2 = CreateThread(NULL, 0, CSThreadstring2, NULL, 0, &threadid2);

            WaitForSingleObject(hthread1, INFINITE);
            WaitForSingleObject(hthread2, INFINITE);

            CloseHandle(hthread1);
            CloseHandle(hthread2);

            DeleteCriticalSection(&CS);

            hthread1 = NULL;
            hthread2 = NULL;
            break;
        }
        case 4: {
            hthread1 = CreateThread(NULL, 0, MutexThreadstring1, NULL, 0, &threadid1);
            hthread2 = CreateThread(NULL, 0, MutexThreadstring2, NULL, 0, &threadid2);

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

}

