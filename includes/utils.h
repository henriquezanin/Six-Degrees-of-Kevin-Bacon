#ifndef __UTILS__
#define __UTILS__

#define BOOL unsigned char
#define TRUE 1
#define FALSE 0
/* End of line */
#define EOL "\n\r"

typedef struct errMessage{
    char *message;
}Error;

Error *newError();
void ErrorFormat(char *, Error *);
unsigned int hasError(Error *);
void PrintError(Error *);
void freeError(Error *);
char *readLine(FILE *);

#endif