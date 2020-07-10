#ifndef __UTILS__
#define __UTILS__

typedef struct errMessage{
    char *message;
}Error;

Error *newError();
void ErrorFormat(char *, Error *);
unsigned int hasError(Error *);
void PrintError(Error *);
void freeError(Error *);

#endif