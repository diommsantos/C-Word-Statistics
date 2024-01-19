ssize_t getline(char **lineptr, size_t *n, FILE *stream);
ssize_t get_txt_word(char **lineptr, size_t *n, FILE *stream);

char *bword;
int n = 0;

int isdelim(char c, char *delims){
    for(int i =0; delims[i] != '\0'; i++){
        if(c == delims[i]){
            return TRUE;
        }
    }
    return FALSE;
}

#define DELIMS ".,;[]() \n\r	\xFF"
ssize_t get_txt_word(char **lineptr, size_t *n, FILE *stream){
    int i = 0;
    char c;
    while(!isdelim(c = getc(stream), DELIMS)){
        if(i+1 > *n){ // reallocates more memory
            *n = *n + 50;
            *lineptr = (char *) realloc(*lineptr, *n);
        }
        (*lineptr)[i] = c;
        i++;
    }
    (*lineptr)[i] = '\0';
    while (isdelim(c = getc(stream), DELIMS) && c != EOF){}
    if(c != EOF) fseek(stream, -1, SEEK_CUR);
    return (ssize_t) *n;
}

int get_biggest_word(char *word, int *ln, char **lbword){
    if(strlen(word) > *ln){
        *ln = strlen(word);
        *lbword = (char *) realloc(*lbword, (*ln+1) * sizeof(char));
        memcpy(*lbword, word, *ln+1);
        return *ln;
    }
}

void thread_func(FILE *stream){
    char *lbword = malloc(0);
    int ln;

    HANDLE FileMutex = OpenMutexW(SYNCHRONIZE, FALSE, L"FileMutex");
    HANDLE GVMutex = OpenMutexW(SYNCHRONIZE, FALSE, L"GVMutex");
    char *txt_word = (char *) malloc(20);
    size_t len_n = 20;
    while(*txt_word != '\0'){
        WaitForSingleObject(FileMutex, INFINITE);
        get_txt_word(&txt_word, (size_t *) &len_n, stream);
        ReleaseMutex(FileMutex);
        get_biggest_word(txt_word, &ln, &lbword);
    }
    if(ln > n){
        WaitForSingleObject(GVMutex, INFINITE);
        n = ln;
        bword = (char *) realloc(bword, (n+1) * sizeof(char));
        memcpy(bword, lbword, (ln+1) * sizeof(char));
        ReleaseMutex(GVMutex);
    }
}

void print_info(void){
    printf("The biggest word is: %s\n"
           "It has a size of %d\n", bword, n);
}