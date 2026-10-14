#include <stdio.h>
#include <windows.h>

int main(void)
{
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    char command[] = "cmd.exe /c echo Child Process Running";

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (CreateProcessA(
            NULL, command, NULL, NULL, FALSE,
            CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
    {
        printf("Parent Process ID: %lu\n",
               (unsigned long)GetCurrentProcessId());

        printf("Child Process ID: %lu\n",
               (unsigned long)pi.dwProcessId);

        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else
    {
        printf("Process creation failed: %lu\n",
               (unsigned long)GetLastError());
    }

    return 0;
}