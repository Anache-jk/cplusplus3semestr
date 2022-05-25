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
unsigned char IsStringOK(char str)
{
    if ((!isalpha((unsigned char)str)) || str == ' ') {
        return 0;
    }
    
    return 1;
}

void UpdatePrivilege(void)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
    {
        LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);

        tp.PrivilegeCount = 1;
        tp.Privileges[0].Luid = luid;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

        AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL);
    }
}

const char* menu =
"Choose what you want"
"\n"
"1. Create process the CALCULATOR\n"
"2. Create proscess the NOTEPAD\n"
"3. Exit\n";
using namespace std;
int main() {
    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
    STARTUPINFO cif;
    HANDLE hProccess;
    ZeroMemory(&cif, sizeof(STARTUPINFO));

    PROCESS_INFORMATION pi =
    {
      NULL,      /* returns process handle */
      0,         /* returns primary thread handle */
      0,         /* returns pid */
      0          /* returns tid */
    };

    SECURITY_ATTRIBUTES sa = { 0 };
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    PROCESS_INFORMATION processInfo = { 0 };
    int choice, i, checkstr,incheck = 1;
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

            CreateProcess("c:\\Windows\\System32\\calc1.exe", NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &cif, &pi);
            
                cout << "Process is started!\n";
                cout << "Process ID - " << pi.dwProcessId << endl;
                cout << "Handle process ID - " << GetProcessId(pi.hProcess) << endl;
            
            
            do {
                cin.clear();
                cout << "Choice what you want to do with CALCULATOR\n"
                    "s - stop the process\n"
                    "r - resume the process\n"
                    "t - delete the process\n";
                cin >> secchoice;
                checkstr = IsStringOK(secchoice);
                while (checkstr != 1) {
                    cout << "Print again(without numeric): ";
                    cin >> secchoice;
                    checkstr = IsStringOK(secchoice);
                }
                switch (secchoice) {
                case 's': {
                    system("cls");
                    if (incheck == 1) {
                        UpdatePrivilege();
                        SuspendThread(pi.hThread);

                        cout << "Process is stop!\n";
                        incheck = 0;
                    }
                    else {
                        cout << "PROCESS ALREADY STOPPED!"<<endl;
                    }
                    break;
                }
                case'r': {
                    if (incheck == 0) {
                        UpdatePrivilege();
                        ResumeThread(pi.hThread);

                        cout << "Process is resumed!\n";
                        incheck = 1;
                }
                    else {
                        cout << "Process is already working!!!\n";
                    }
                    break;
                }
                case't': {
                    UpdatePrivilege();
                    TerminateProcess(pi.hProcess,0);
                    CloseHandle(pi.hProcess);
                    break;
                }
                default:
                    cout << "SOMETHING WRONG, PLEASE PRINT AGAIN" << endl;

                }
            } while (secchoice != 't');

            break;
        }
        case 2: {
            CreateProcess("c:\\Windows\\notepad.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &cif, &pi);
            cout << "Process is started BUT IN WAITING MODE!\n";
            cout << "Process ID - " << pi.dwProcessId << endl;
            cout << "Handle process ID - " << GetProcessId(pi.hProcess) << endl;
            cout << endl << endl << endl;
            i = 0;
            while (i != 11) {
                cout << "Process will resume in a " << 10 - i <<" sec" << endl;
                i++;
                Sleep(1000);
            }
            cout << endl;
            UpdatePrivilege();
            ResumeThread(pi.hThread);
          

            cout << "Process is resumed!\n";
            cout << "Pocess has priority is \n";
            int potok = GetThreadPriority(pi.hThread);
            if (potok == 1) {
                cout << "Highest than normal on 1" << endl;
            }
            else if (potok == -1) {
                cout << "Lower than normal on 2" << endl;
            }
            else if (potok == 2) {
                cout << "Highest than normal on 2" << endl;
            }
            else if (potok == -2) {
                cout << "Lower than normal on 2" << endl;
            }
            else if (potok == 0) {
                cout << "Normal" << endl;
            }
            else if (potok == -15) {
                cout << "Process is so lower" << endl;
            }
            else if (potok == 15) {
                cout << "Process is so highest(may be virus?)" << endl;
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

}