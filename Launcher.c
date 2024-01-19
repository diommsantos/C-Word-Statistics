#include <stdio.h>
#include <windows.h>
#include <tchar.h>

int main(int argc, char *argv[])
{

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    char *cmdline_args;
    if (strcmp("-s", argv[1]) == 0)
    {   
        asprintf(&cmdline_args, "\"./Word Analyzer ST.exe\" %s", argv[2]);
        if (!CreateProcessA("Word Analyzer ST.exe",
                            cmdline_args,
                            NULL,
                            NULL,
                            FALSE,
                            0,
                            NULL,
                            NULL,
                            &si,
                            &pi))
        {
            printf("Creation of Singlethreaded Process Failed\n");
        }
    }
    else if (strcmp("-m", argv[1]) == 0)
    {   
        asprintf(&cmdline_args, "\"./Word Analyzer MT.exe\" %s", argv[2]);
        if (!CreateProcessA("./Word Analyzer MT.exe",
                            cmdline_args,
                            NULL,
                            NULL,
                            FALSE,
                            0,
                            NULL,
                            NULL,
                            &si,
                            &pi))
        {
            printf("Creation of Multithreaded Process Failed\n");
        }
    }
    else
    {
        printf(
            "Usage: Launcher.exe [mode]\n"
            "       mode  -s singlethread\n"
            "             -m multithread\n"
            );
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
}