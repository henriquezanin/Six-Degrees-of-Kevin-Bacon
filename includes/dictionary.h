#ifndef _SET_STRUCTURE_
#define _SET_STRUCTURE_

typedef struct dictElement{
    int key;
    char *string;
} dictElement;

typedef struct dictionary{
    int size;
    dictElement **elements;
}Dictionary;

Dictionary *createDictionary();
int addDictionary(char *, int, Dictionary *);
int getDictionaryKey(char *, Dictionary *);
char *getDictionaryValue(int, Dictionary *);
void freeDictionary(Dictionary *);

#endif