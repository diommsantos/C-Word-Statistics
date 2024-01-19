void print_info(void);
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
ssize_t get_txt_word(char **lineptr, size_t *n, FILE *stream);

char *bword;
int n;
void initialize_info(void){
    bword = malloc(1);
    n = 0;
}

ssize_t getline(char **lineptr, size_t *n, FILE *stream){
    int i = 0;
    char c;
    while( (c = getc(stream)) != '\n' && c != EOF ){
        if(i+1 > *n){ // reallocates more memory
            *n = *n + 50;
            *lineptr = (char *) realloc(*lineptr, *n);
        }
        (*lineptr)[i] = c;
        i++;
    }
    (*lineptr)[i] = '\0';
    return (ssize_t) *n;

}

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

int get_biggest_word(char *word){
    if(strlen(word) > n){
        n = strlen(word);
        bword = (char *) realloc(bword, (n+1) * sizeof(char));
        memcpy(bword, word, n+1);
        return n;
    }

}

#define NR_FUNCTIONS 1
int (*functions[NR_FUNCTIONS])(char *word) = {&get_biggest_word};
void execute_functions(char *word){
    for(int i=0; i < NR_FUNCTIONS; i++){
        (functions[i])(word);
    }
}

void print_info(void){
    printf("The biggest word is: %s\n"
           "It has a size of %d\n", bword, n);
}