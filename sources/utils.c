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

char *readName(FILE *file, BOOL *endOfLine) {
    char *name = (char*) calloc(2, sizeof(char));
    int i = 0;

    while (fscanf(file, "%c", &name[i]) && name[i] != '/' && name[i] != '\n' && !feof(file)) {
        i++;
        name = (char*) realloc(name, (i+1)*sizeof(char));
    }
    if (name[i] == '\n' || feof(file)) *endOfLine = TRUE;
    name[i] = '\0';

    return name;
}

MOVIE* readMovie(FILE *file) {
    if (feof(file) || !file) return NULL;

    int i = 0;
    BOOL end = FALSE;
    MOVIE *movie = (MOVIE*) calloc(1, sizeof(MOVIE));

    movie->name = readName(file, &end);
    movie->actors = (char**) calloc(1, sizeof(char*));

    while ((movie->actors[i] = readName(file, &end)) && end != TRUE) {
        i++;
        movie->actorsCounter++;
        movie->actors = (char**) realloc(movie->actors, (i+1)*sizeof(char*));
    }
    movie->actorsCounter++;

    return movie;
}

void printMovie(MOVIE *movie) {
    int i = 0;
    printf("NAME: %s\n", movie->name);

    for (i = 0; i < movie->actorsCounter; i++) {
        printf("Actor %d: %s\n", i+1, movie->actors[i]);
    }

}

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