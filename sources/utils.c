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