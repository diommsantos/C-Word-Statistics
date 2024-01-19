#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include "./wslib.c"
#include "time.h"


int main(int argc, char *argv[]){
    if(argc != 2){
        printf("Error: No filename provided\n");
        return -1;
    }

    struct timespec begin, end; 
    clock_gettime(CLOCK_REALTIME, &begin);
    struct tm *begin_timeinfo = localtime(&begin.tv_sec);
    printf("Started analysing the file at: %s", asctime(begin_timeinfo));


    FILE *aaa = fopen(argv[1], "r");
    char *txt_word = (char *) malloc(20);
    size_t n = 20;
    initialize_info();
    while(*txt_word != '\0'){
        get_txt_word(&txt_word, (size_t *) &n, aaa);
        execute_functions(txt_word);
    }
    print_info();


    clock_gettime(CLOCK_REALTIME, &end);
    struct tm *end_timeinfo = localtime(&end.tv_sec);
    printf("Ended analysing the file at %s"
           "Took %.9fs to analyse the file.\n", asctime(end_timeinfo), (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) / 1e9);
}