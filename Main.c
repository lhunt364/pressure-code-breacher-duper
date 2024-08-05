#include <stdio.h>
#include <windows.h>
#include <stdbool.h>


int main() {

    // main loop
    bool explode = false;
    while (true) {
        
        // start or exit loop
        printf("Press 'r' to start or 'u' to exit.\n");
        while (true) {
            if (GetAsyncKeyState('R') & 0x8000) {
                printf("Starting\n");
                break;
            } else if (GetAsyncKeyState('U') & 0x8000) {
                printf("Exiting\n");
                explode = true;
                break;
            }
            Sleep(10);
        }

        if (explode) {
            break;
        }

        // run BlowsUpPancakesWithMind.exe

        const char *exePath = "BlowsUpPancakesWithMind.exe";

        // make startup information and process information structures
        STARTUPINFO si = { sizeof(si) };
        PROCESS_INFORMATION pi;

        // initialize the STARTUPINFO structure
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE; // Hide the window

        // create process
        if (CreateProcess(
                NULL,             // Application name (NULL means use command line)
                (LPSTR)exePath,   // Command line (the path to the executable)
                NULL,             // Process security attributes
                NULL,             // Primary thread security attributes
                FALSE,            // Handle inheritance
                CREATE_NO_WINDOW, // Creation flags (no new console window)
                NULL,             // Environment variables
                NULL,             // Starting directory
                &si,              // STARTUPINFO pointer
                &pi)              // PROCESS_INFORMATION pointer
        ) {
            // wait until exit
            WaitForSingleObject(pi.hProcess, INFINITE);

            // close process and thread handles
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);

            printf("Macro completed\n");
        } else {
            printf("CreateProcess failed (%d).\n", GetLastError());
        }

        Sleep(250);
        
        }

    return 0;
}