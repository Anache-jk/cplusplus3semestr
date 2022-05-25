#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <time.h>
#include<Windows.h>
#include<string>
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <memory.h>
SYSTEM_INFO sSysInfo;
using namespace std;
const char* menu =
"Choose what you want"
"\n"
"1. Create dynamic massive and sort him\n"
"2. Exit\n";

int main() {
    GetSystemInfo(&sSysInfo);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
    int choice, checker1, checker2, stroke, numbers, *plusarr;
    HANDLE handlee;
    handlee = HeapCreate(0, 0x100000, 0);
    int** array;
    int chec, aaraydop[11];
    for (int i = 0; i < 11; i++) {
        aaraydop[i] = 11;
    }
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
            if (handlee != NULL) {
                cout << "UNSORTED ARRAY IS " << endl << endl;
                numbers = rand()%5 + 1;
                array = new int* [numbers];
                plusarr = new int [numbers];
               // cout << numbers << " 0num" << endl;
                for (int i = 0; i < numbers; i++) {
                    stroke = rand() % 10 + 1;
                    //array[i] = (int*)HeapAlloc(handlee, 0, stroke*sizeof(int));
                    array[i] = new int[stroke];
                    array[i] = (int*)HeapAlloc(handlee, 0, stroke * sizeof(int));  
                    if (array[i] != NULL) {
                        checker1 = HeapSize(handlee, 0, array[i]);
                        //cout << checker1 << endl << endl;
                        plusarr[i] = stroke;
                        for (int j = 0; j < stroke; j++) {
                            array[i][j] = rand() % 10 + 1;

                            cout << array[i][j] << " ";
                        }
                        
                        cout << endl;
                    }
                    else {
                        cout << "SOMETHING WRONG" << endl;
                    }
                }
              
                cout << endl;

                for (int k = 0; k < numbers; k++) {
                    for (int i = 0; i < numbers - 1; i++) {
                        if (plusarr[i] > plusarr[i + 1]) {
                            for (int j = 0; j < plusarr[i + 1]; j++) {
                                aaraydop[j] = array[i + 1][j];
                            }
                           array[i+1] = (int*)HeapReAlloc(handlee, 0 ,array[i + 1], plusarr[i]*sizeof(int));

                            for (int j = 0; j < plusarr[i]; j++) {
                                array[i + 1][j] = array[i][j];
                            }
                            array[i] = (int*)HeapReAlloc(handlee, 0, array[i], plusarr[i+1]* sizeof(int));
                            for (int j = 0; j < 11; j++) {
                                if (aaraydop[j] != 11) {
                                    array[i][j] = aaraydop[j];
                                }
                                aaraydop[j] = 11;
                            }
                            chec = plusarr[i];
                            plusarr[i] = plusarr[i+1];
                            plusarr[i + 1] = chec;
                        }
                    }
                    
                }
                cout << endl;
                cout << endl;
                cout << "SORTED ARRAY IS " << endl << endl;
                for (int i = 0; i < numbers; i++) {
                    for (int j = 0; j < plusarr[i]; j++) {
                        cout << array[i][j] << " ";
                    }
                    cout << endl;
                    HeapFree(handlee, 0, array[i]);
                }

            }
            break;
        }
        case 2: {
            break;
        }
        default:    
            system("cls");
            cout << "\nChoose again\n\n";
        }
    } while (choice != 2);
    HeapDestroy(handlee);
    return 0;
}