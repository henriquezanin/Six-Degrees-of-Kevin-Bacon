#ifndef __UTILS__
#define __UTILS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOL unsigned char
#define TRUE 1
#define FALSE 0
/* End of line */
#define EOL "\n\r"

typedef struct errMessage{
    char *message;
}Error;

typedef struct movieInfos {
    char *name;
    int actorsCounter;
    char **actors;
} MOVIE;

Error *newError();
void ErrorFormat(char *, Error *);
unsigned int hasError(Error *);
void PrintError(Error *);
void freeError(Error *);
char *readLine(FILE *);
MOVIE* readMovie(FILE*);
void printMovie(MOVIE*);
void freeMovie(MOVIE*);

#endif