#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<iostream>
#include<math.h>
#include<string>

const char* menu =
"Choose what you want"
"\n"
"1. Exercise 1\n"
"2. Exercise 2\n"
"3. Exit\n";


using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    system("cls");
    char let[2];
    int choice,i;
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
        switch (choice)
        {
        case 1: {
            cout << "Print Letter of disk:";
            cin >> let[1];
            cin.ignore(32767, '\n');
            cin.clear();
            while ((!isalpha((unsigned char)let[1])) && (let[1] != ' ')) {
                cout << "PRINT LETTER OF DISK AGAIN:";
                cin >> let[1];
                cin.ignore(32767, '\n');
                cin.clear();
            }
            cout << endl;
            DWORD ds = GetLogicalDrives();
            let[1] = (char)toupper(let[1]);
            LPCSTR let3[26] = { "A:\\","B:\\","C:\\","D:\\","E:\\","F:\\","G:\\","H:\\","I:\\","J:\\","K:\\","L:\\","M:\\","N:\\"
,"O:\\","P:\\","Q:\\","R:\\","S:\\","T:\\","U:\\","V:\\","W:\\","X:\\","Y:\\","Z:\\" };
            if (ds == 1&&let[1] =='A') {
                cout << "Disc" << let[1] << "Exist"<<endl;
                i = 0;
            
            }
            else if (ds == 2 && let[1] == 'B') {
                cout << "Disc " << let[1] << " Exist" << endl;
                i = 1;
             
            }
            else if (ds == 4 && let[1] == 'C') {
                cout << "Disc " << let[1] << " Exist" << endl;
                i = 2;
                
            }
            else if (ds == 8 && let[1] == 'D') {
                cout << "Disc " << let[1] << " Exist" << endl;
                i = 3;
              
            }
            else if (ds == 16 && let[1] == 'E') {
                cout << "Disc " << let[1] << " Exist" << endl;
                i = 4;
                
            }
            else if (ds == 32 && let[1] == 'F') {
                cout << "Disc " << let[1] << " Exist" << endl;
                i = 5;
              
            }
            else {
                cout << "Disc " << let[1] << " DOESNT Exist" << endl;
                break;
            }
            cout << "DISK IS: \n\n";
            DWORD d = GetDriveType(let3[i]);
            if (d == DRIVE_UNKNOWN) cout << " UNKNOWN" << endl;
            if (d == DRIVE_NO_ROOT_DIR) cout << " DRIVE NO ROOT DIR" << endl;
            if (d == DRIVE_REMOVABLE) cout << " REMOVABLE" << endl;
            if (d == DRIVE_FIXED) cout << " FIXED" << endl;
            if (d == DRIVE_REMOTE) cout << " REMOTE" << endl;
            if (d == DRIVE_CDROM) cout << " CDROM" << endl;
            if (d == DRIVE_RAMDISK) cout << " RAMDISK" << endl;
            cout << endl;
            cout << endl;
            
            char VolumeNameBuffer[100];
            char FileSystemNameBuffer[100];
            unsigned long VolumeSerialNumber;

           
            BOOL GetVolumeInformationFlag = GetVolumeInformationA(
                let3[i],
                VolumeNameBuffer,
                100,
                &VolumeSerialNumber,
                NULL, //&MaximumComponentLength,
                NULL, //&FileSystemFlags,
                FileSystemNameBuffer,
                100
            );

            if (GetVolumeInformationFlag != 0)
            {
                cout << "Disk Name is " << let[1] <<endl;
                cout << "Disk Serial Number is " << VolumeSerialNumber << endl;
                cout << "File System is " << FileSystemNameBuffer << endl;
            }
            else { cout << "Information about disk" << let<< "IS NOT FOUND"<<endl; }


            __int64 FreeBytesAvailable;
            __int64 TotalNumberOfBytes;
            __int64 TotalNumberOfFreeBytes;

            BOOL GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx(
                let3[i],					  // directory name
                (PULARGE_INTEGER)&FreeBytesAvailable,     // bytes available to caller
                (PULARGE_INTEGER)&TotalNumberOfBytes,     // bytes on disk
                (PULARGE_INTEGER)&TotalNumberOfFreeBytes  // free bytes on disk
            );

            if (GetDiskFreeSpaceFlag != 0)
            {
                cout << "Total Number Of Free Bytes = " << TotalNumberOfFreeBytes
                    << "( " << TotalNumberOfFreeBytes / 1024 / 1000
                    << " Mb )" << endl;
                cout << "Total Number Of Bytes = " << TotalNumberOfBytes
                    << "( " << TotalNumberOfBytes / 1024 / 1000
                    << " Mb )" << endl;
                cout << endl;
            }
            else { cout << "Number of bytes about disc " << let << " NOT FOUND" << endl; }
      
            break; }
        case 2: {
            char st3[20];
            int pointers;
            HANDLE muf;
            cout << "Print name of file: " << endl;
            cin.getline(st3,20);
            cout << "Print number of moving pointer: ";
            cin >> pointers;
            while (!pointers && pointers != 0|| pointers <0||(cin.peek() != '\n')) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "\n Print number CORRECTLY(without symbols): ";
                cin >> pointers;
            }
            cin.ignore();

            muf = CreateFile(st3,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_WRITE | FILE_SHARE_READ,
                NULL, 
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, 
                0);
            int Error = GetLastError();

            if (Error != 0) {

                cout << "File doesnt exist!"<<endl;
            }
            else {
                cout << "File is exist and already changed!" << endl;
                char cBuffer[512] = { 0 };
                DWORD lpNumberOfBytesRead = 0;
                DWORD dwBytesWritten;
                OVERLAPPED olf = { 0 };
                LARGE_INTEGER li = { 0 };

                li.QuadPart = pointers;
                olf.Offset = li.LowPart;
                olf.OffsetHigh = li.HighPart;

                ReadFile(muf, cBuffer, 512, &lpNumberOfBytesRead, &olf);
                CloseHandle(muf);
                DeleteFile(st3);
                HANDLE muf2 = CreateFile(st3,
                    GENERIC_READ | GENERIC_WRITE,
                    FILE_SHARE_WRITE | FILE_SHARE_READ,
                    NULL,
                    CREATE_ALWAYS,
                    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                    0);
                li.QuadPart = 0;
                olf.Offset = li.LowPart;
                olf.OffsetHigh = li.HighPart;
                WriteFile(muf2, cBuffer, 512,&dwBytesWritten, &olf);
                CloseHandle(muf2);

                break;
            }
            CloseHandle(muf);
           break; }

        
        case 3: {
            break;
        }
        default:
            cout << "\nChoose again\n\n";
        }
    } while (choice != 3);

    return 0;
}