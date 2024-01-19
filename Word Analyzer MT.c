#include <stdio.h>
#include <windows.h>
#include ".\MTwslib.c"
#include <tchar.h>
#include <time.h>

#define THREAD_NR 16
int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Error: No filename provided\n");
        return -1;
    }

    printf("Analyzing multi-thread...\n");
    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);
    struct tm *begin_timeinfo = localtime(&begin.tv_sec);
    printf("Started analysing the file at: %s", asctime(begin_timeinfo));



    DWORD dwThreadId;
    HANDLE Threads[THREAD_NR];
    FILE *aaa = fopen(argv[1], "r");
    CreateMutexW(NULL, FALSE, L"FileMutex");
    CreateMutexW(NULL, FALSE, L"GVMutex");
    for(int i = 0; i < THREAD_NR; i++)
        Threads[i] = CreateThread(NULL, 0, thread_func, (void *) aaa, 0, &dwThreadId);
    WaitForMultipleObjects(THREAD_NR, Threads, TRUE, INFINITE);
    print_info();


    clock_gettime(CLOCK_REALTIME, &end);
    struct tm *end_timeinfo = localtime(&end.tv_sec);
    printf("Ended analysing the file at %s"
           "Took %.9fs to analyse the file.\n", asctime(end_timeinfo), (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9);
}