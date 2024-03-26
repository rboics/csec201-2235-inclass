// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>


//This function cannot be imported by other executables
//Can only be called by code in dllExample.dll
void privateFunction(void) {
    printf("Hello from private function\n");
}

//Extern line marks dllDemo as a function
//That can be imported by other executables
extern "C" __declspec(dllexport)
void dllDemo(void) {
    printf("Hello from dllDemo\n");
    privateFunction();
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    printf("Hello from DLLMain!\n");
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        printf("DLL process attach!\n");
        break;
    case DLL_THREAD_ATTACH:
        printf("DLL thread attach!\n");
        break;
    case DLL_THREAD_DETACH:
        printf("DLL thread detach!\n");
        break;
    case DLL_PROCESS_DETACH:
        printf("DLL process detach!\n");
        break;
    }
    return TRUE;
}

