/*
* Nome: Henrique Gomes Zanin
* nUSP: 10441321
*
* Nome: Gabriel Guimarães Vilas Boas Marin
* nUSP: 11218521
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils.h>

BOOL checkEndOfLine(char character){
    if(strchr(EOL, character) || character == EOF) return TRUE;
    else return FALSE;
}

char *readLine(FILE *fp){
    char *textLine = NULL;
    unsigned int size = 0;

    do{
        textLine = (char*)realloc(textLine, (size+1)*sizeof(char));
        textLine[size] = fgetc(fp);
    }while(!checkEndOfLine(textLine[size++]));
    textLine[size-1] = '\0';

    return textLine;
}


Error *newError(){
    return (Error *)calloc(1, sizeof(Error));
}

void ErrorFormat(char *message, Error *err){
    if(!err) return;
    if(!err->message)
        err->message = (char *)calloc(strlen(message)+1, sizeof(char));
    else{
        err->message = (char *)realloc(err->message, strlen(err->message)+strlen(message));
        strcat(err->message, "; ");
    }
    strcat(err->message, message);
}

unsigned int hasError(Error *err){
    return (err->message) ? 1:0;
}

void PrintError(Error *err){
    if(hasError(err))
        printf("%s\n", err->message);
}

void freeError(Error *err){
    if(!err) return;
    if(!err->message) free(err->message);
    free(err);
}