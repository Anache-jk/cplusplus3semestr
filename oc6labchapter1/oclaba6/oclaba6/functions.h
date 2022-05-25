#pragma once
#include<windows.h>

#ifndef __functionsDLL_h__
#define __functionsDLL_h__

#ifdef __functionsDLL_exports
#define MYFUNCTIONS_DLL __declspec(dllexport)
#else
#define MYFUNCTIONS_DLL __declspec(dllexport)
#endif

MYFUNCTIONS_DLL DWORD WINAPI Threadstring1(LPVOID lpParam);
MYFUNCTIONS_DLL DWORD WINAPI Threadstring2(LPVOID lpParam);
MYFUNCTIONS_DLL DWORD WINAPI ModThreadstring1(LPVOID lpParam);
MYFUNCTIONS_DLL DWORD WINAPI ModThreadstring2(LPVOID lpParam);
MYFUNCTIONS_DLL DWORD WINAPI CSThreadstring1(LPVOID lpParam);
MYFUNCTIONS_DLL DWORD WINAPI CSThreadstring2(LPVOID lpParam);
MYFUNCTIONS_DLL DWORD WINAPI MutexThreadstring1(LPVOID lpParam);
MYFUNCTIONS_DLL DWORD WINAPI MutexThreadstring2(LPVOID lpParam);
MYFUNCTIONS_DLL HANDLE hmutex;
MYFUNCTIONS_DLL int counts;
MYFUNCTIONS_DLL CRITICAL_SECTION CS;
#endif // !__functionsDLL_h__
