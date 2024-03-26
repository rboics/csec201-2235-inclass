#include <stdio.h>
#include <windows.h>

typedef (__stdcall* dllFunction)();

int main(void) {
	printf("Hello from main!\n");

	//Load Library
	//1: Asks the OS to load the library into memory
	//2: Provides a pointer for interacting with the library
	//HINSTANCE importedDLL = LoadLibrary(L"D:\\csec201-2235-inclass\\dynamic-linking\\DLLExample\\x64\\Debug\\DLLExample.dll");
	HINSTANCE importedDLL = LoadLibrary(L"D:\\csec201-2235-inclass\\dynamic-linking\\DLLExample\\Debug\\DLLExample.dll");

	
	dllFunction myFunc;

	myFunc = GetProcAddress(importedDLL, "dllDemo");

	//myFunc = (dllFunction)"\x01\x02\x03\x04";

	myFunc();

}