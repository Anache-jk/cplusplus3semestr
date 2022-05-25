#include<iostream>
using namespace std;

#ifndef __functionsDLL_cpp__
#define __functionsDLL_cpp__

#include "functions.h"

DWORD WINAPI Threadstring1(LPVOID lpParam) {
    char bruh[] = { "Hello Semen!" };
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < strlen(bruh); j++) {
            cout<<bruh[j];
        }
        cout<<endl;


    }
    return 0;
}
DWORD WINAPI Threadstring2(LPVOID lpParam) {
    char bruh[] = { "Hello Alexey!" };
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < strlen(bruh); j++) {
            cout << bruh[j];
        }
        cout << endl;
    }
    return 0;
}
DWORD WINAPI ModThreadstring1(LPVOID lpParam) {
    char bruh[] = { "Hello Semen with CSynchronize!" };

    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < strlen(bruh); j++) {
            cout << bruh[j];
            Sleep(200);
        }
        cout << endl;
    }
    return 0;
}
DWORD WINAPI ModThreadstring2(LPVOID lpParam) {
    char bruh[] = { "Hello Alexey with CSynchronize!" };
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < strlen(bruh); j++) {
            cout << bruh[j];
            Sleep(100);
        }
        cout << endl;
    }
    return 0;
}
DWORD WINAPI CSThreadstring1(LPVOID lpParam) {
    char bruh[] = { "Hello Semen with CSection!" };
    EnterCriticalSection(&CS);
    while (counts < 25) {
        
        if (counts % 2 == 1) {

            for (int j = 0; j < strlen(bruh); j++) {
                cout << bruh[j];
                Sleep(100);
            }
            cout << endl;
            counts++;
        }
       
    }
    LeaveCriticalSection(&CS);
    return 0;
}
DWORD WINAPI CSThreadstring2(LPVOID lpParam) {
    char bruh[] = { "Hello Alexey with CSection!" };
    EnterCriticalSection(&CS);
    while (counts < 25) {
      
        if (counts % 2 == 0) {
            for (int j = 0; j < strlen(bruh); j++) {
                cout << bruh[j];
                Sleep(100);
            }
            cout << endl;
            counts++;
        }
        
    }
    LeaveCriticalSection(&CS);
    return 0;
}
DWORD WINAPI MutexThreadstring1(LPVOID lpParam) {
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
DWORD WINAPI MutexThreadstring2(LPVOID lpParam) {
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

#endif