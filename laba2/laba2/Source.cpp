#define _CRT_SECURE_NO_WARNINGS
#include "windows.h"
#include <time.h>
#include<Windows.h>
#include<iostream>
#include<string>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <memory.h>
#define DIV 1024
#define WIDTH 7
SYSTEM_INFO sSysInfo;
using namespace std;
const char* menu =
"Choose what you want"
"\n"
"1. Print information about your RAM\n"
"2. Create page of virtual memory\n"
"3. Exit\n";


int main() {
    GetSystemInfo(&sSysInfo);
    LPVOID address = NULL;
    int exmas[] = { 1,2,3,4,5,6,7 };
    MEMORYSTATUS status;
    status.dwLength = sizeof(status);
    GlobalMemoryStatus(&status);
    int truex = 1;
    char checklet;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
    int choice, i;
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
        case 1:{
            while (truex) {
                cout << "This is percent of memory use : " << status.dwMemoryLoad << endl;
                cout << "This is total KB of physical memory :" << status.dwTotalPhys / DIV << endl;
                cout << "This is free KB of physical memory :" << status.dwAvailPhys / DIV << endl;
                cout << "Press q for EXIT" << endl;
                Sleep(1000);
                if (GetAsyncKeyState(0x51)) {  
                    cin.clear();
                    system("cls");
                    break;
                }
            }
            break;
        }
        case 2: {
            int numbervirtual, numberphysical, startnumber, rewritephyspage, rewritestart;
            MEMORY_BASIC_INFORMATION info;
            cout << "How much page of virtual memory you want?(Print number)" << endl;
            cin >> numbervirtual;
            while (!numbervirtual && numbervirtual != 0 || (cin.peek() != '\n')) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "\n Print again(without symbols): ";
                cin >> numbervirtual;
            }
            if (numbervirtual != 0) {
                cout << "Page size : " << sSysInfo.dwPageSize << "\nGranularity : " << sSysInfo.dwAllocationGranularity <<
                    "\nMin addr : " << sSysInfo.lpMinimumApplicationAddress << "\nMax addr : " << sSysInfo.lpMaximumApplicationAddress << endl;
                //int* mas = (int*)VirtualAlloc(NULL, numbervirtual * sizeof(int), MEM_RESERVE, PAGE_READWRITE);
                int* mas = new int[numbervirtual] ;
                cout << "VIRTUAL PAGE ADDRESSES :"<<endl;
               for (int i = 0; i < numbervirtual; i++) {
                   cout << i<<" - ";
                  mas[i] = (int)VirtualAlloc(NULL, 4096, MEM_RESERVE, PAGE_READWRITE);
                   cout << (void*)mas[i] << endl;
               }

                if (mas != NULL) {
                    cout << "How much pages you want to switch to physical memory?(Print number)" << endl;
                    cin >> numberphysical;
                    while (!numberphysical && numberphysical != 0 || numberphysical>numbervirtual || (cin.peek() != '\n')) {
                        cin.clear();
                        while (cin.get() != '\n');
                        cout << "\n Print again(without symbols and incorrectly(true choose pages)): ";
                        cin >> numberphysical;
                    }
                    if (numberphysical != 0) {
                        cout << "\nPrint page, where you want to start physical memory: ";
                        cin >> startnumber;
                        while (!startnumber && startnumber != 0 || startnumber > numbervirtual - numberphysical || (cin.peek() != '\n')) {
                            cin.clear();
                            while (cin.get() != '\n');
                            cout << "\n Print again(without symbols and incorrectly(true choose pages): ";
                            cin >> startnumber;
                        }
                        cout << "INFORMATION APOUT PHYSICAL MEMORY(AND REMAINS OF PAGE)" << endl << endl;
                        for (int i = startnumber; i < numberphysical + startnumber; i++) {
                            mas[i] = (int)VirtualAlloc(NULL, 4096, MEM_COMMIT, PAGE_READWRITE);
                            cout << "Page with physical memory \nPage - " << i << "\nAddress - " << (void*)mas[i] << endl;
                            memcpy_s((void*)mas[i], 4096, exmas, sizeof(exmas));
                            cout << "Copied massive is : ";
                            cout << endl;
                            VirtualQuery((void*)mas[i], &info, 4096);
                            cout << "Allocation Base: " << info.AllocationBase << "\n"
                                << "BaseAddress: " << info.BaseAddress << "\n"
                                << "Protection: " << info.Protect << "\n"
                                << "State: " << info.State << "\n"
                                << "Region size: " << info.RegionSize << endl << endl;;
                            Sleep(1000);
                            
                        }
                        if (startnumber + numberphysical > numbervirtual) {
                            cout << "WE CANT CREATE PHYSICAL PAGE" << endl;
                            break;
                        }
                        else {
                            for (i = startnumber + numberphysical; i < numbervirtual; i++) {
                                VirtualQuery((void*)mas[i], &info, 4096);
                                cout << "Page - " << i << endl;
                                cout << "Allocation Base: " << info.AllocationBase << "\n"
                                    << "BaseAddress: " << info.BaseAddress << "\n"
                                    << "Protection: " << info.Protect << "\n"
                                    << "State: " << info.State << "\n"
                                    << "Region size: " << info.RegionSize << endl << endl;;
                                Sleep(1000);
                            }
                            cout << "INFORMATION NEXT PAGE AFTER PHYSICAL PAGES" << endl;
                            mas[startnumber + numberphysical] = (int)VirtualAlloc(NULL, 4096, MEM_COMMIT, PAGE_READONLY);
                            VirtualQuery((void*)mas[startnumber + numberphysical], &info, 4096);
                            cout << "Page - " << startnumber + numberphysical << endl;
                            cout << "Address - " << (void*)mas[startnumber + numberphysical] << endl;
                            cout << "Allocation Base: " << info.AllocationBase << "\n"
                                << "BaseAddress: " << info.BaseAddress << "\n"
                                << "Protection: " << info.Protect << "\n"
                                << "State: " << info.State << "\n"
                                << "Region size: " << info.RegionSize << endl << endl;;
                        
                        cout << "Print how much physical pages need to rewrite to virtual memory : ";
                        cin >> rewritephyspage;
                        while (!rewritephyspage && rewritephyspage != 0 || rewritephyspage > numberphysical || (cin.peek() != '\n')) {
                            cin.clear();
                            while (cin.get() != '\n');
                            cout << "\n Print again(without symbols and incorrectly(true choose pages)): ";
                            cin >> rewritephyspage;
                        }
                        cout << "Print where need to start : ";
                        cin >> rewritestart;
                        while (!rewritestart && rewritestart != 0 || rewritestart < startnumber || rewritestart > startnumber + numberphysical || rewritestart + rewritephyspage > startnumber + numberphysical || (cin.peek() != '\n')) {
                            cin.clear();
                            while (cin.get() != '\n');
                            cout << "\n Print again(without symbols and incorrectly(true choose pages)): ";
                            cin >> rewritestart;
                        }
                        for (int i = rewritestart; i < rewritephyspage + rewritestart; i++) {
                            VirtualFree((void*)mas[i], sizeof(mas[i]), MEM_DECOMMIT);
                            VirtualQuery((void*)mas[i], &info, 4096);
                            cout << "Page - " << i << endl;
                            cout << "Address - " << (void*)mas[i] << endl;
                            cout << "Allocation Base: " << info.AllocationBase << "\n"
                                << "BaseAddress: " << info.BaseAddress << "\n"
                                << "Protection: " << info.Protect << "\n"
                                << "State: " << info.State << "\n"
                                << "Region size: " << info.RegionSize << endl << endl;;
                            Sleep(1000);
                        }
                        VirtualFree((void*)mas, 0, MEM_RELEASE);

                    } 
                    }
                    else {
                        for (int i = 0; i < numbervirtual; i++) {
                            cout << "Pages virtual \nNumber - " << i << "\nAddress - " << (void*)mas[i];
                            break;
                        }
                    }
                }
                else {
                    cout << "Error Alloc memory " << endl;
                }

            }
            else {
                cout << "GOODBYE!!!"<<endl;
                break;
            }

            break;
        }
        case 3: {
            break;
        }
        default:
            cout << "\nChoose again\n\n";
        }
    } while (choice != 3);
    return 0;
}