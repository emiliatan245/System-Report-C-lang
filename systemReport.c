
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char hostname[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD nameSize = sizeof(hostname);

    MEMORYSTATUSEX mem;
    mem.dwLength = sizeof(mem);

    SYSTEM_INFO si;
    ULARGE_INTEGER freeBytes, totalBytes, totalFree;

    printf("========================================\n");
    printf("          REAL PC STATUS\n");
    printf("========================================\n");

    // Hostname
    if (GetComputerNameA(hostname, &nameSize))
        printf("\nHostname       : %s\n", hostname);

    // Windows version
    printf("Windows version: ");
    system("ver");

    // Processor information
    GetSystemInfo(&si);
    printf("Logical CPUs   : %lu\n",
           (unsigned long)si.dwNumberOfProcessors);

    // Memory status
    if (GlobalMemoryStatusEx(&mem)) {
        printf("\n--- MEMORY STATUS ---\n");
        printf("RAM Total      : %.2f GB\n",
               mem.ullTotalPhys / 1073741824.0);
        printf("RAM Available  : %.2f GB\n",
               mem.ullAvailPhys / 1073741824.0);
        printf("RAM Used       : %.2f GB\n",
               (mem.ullTotalPhys - mem.ullAvailPhys)
               / 1073741824.0);
        printf("RAM Usage      : %lu%%\n",
               (unsigned long)mem.dwMemoryLoad);
    }

    // Disk status
    printf("\n--- DISK STATUS (C:) ---\n");
    if (GetDiskFreeSpaceExA("C:\\", &freeBytes,
                            &totalBytes, &totalFree)) {
        printf("Total Space    : %.2f GB\n",
               totalBytes.QuadPart / 1073741824.0);
        printf("Free Space     : %.2f GB\n",
               freeBytes.QuadPart / 1073741824.0);
        printf("Used Space     : %.2f GB\n",
               (totalBytes.QuadPart - freeBytes.QuadPart)
               / 1073741824.0);
    }

    // Running processes
    printf("\n--- RUNNING PROCESSES ---\n");
    system("tasklist");

    printf("\n--- NETWORK CONFIGURATION ---\n");
    system("ipconfig");

    printf("\n========================================\n");
    printf("          REPORT COMPLETE\n");
    printf("========================================\n");

    return 0;
}
