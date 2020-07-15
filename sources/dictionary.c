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
#include <dictionary.h>

Dictionary *createDictionary(){
    return (Dictionary*)calloc(1,sizeof(Dictionary));
}
//Mudar para strlen string, valgrind dando erro
dictElement *_createDictElem(char *string, int key){
     dictElement *elem = (dictElement*)malloc(sizeof(dictElement));
     elem->key = key;
     elem->string = (char*)calloc(200, sizeof(char));
     strcpy(elem->string, string);
     return elem;
}

int _binarySearch(dictElement **array, int left, int right, char *string){
    if(left > right){
        return -1;
    }
    int mid = (right+left)/2;
    if(!strcmp(array[mid]->string, string)){
        return mid;
    }
    else if(strcmp(array[mid]->string, string) > 0){
        return _binarySearch(array,left,mid-1,string);
    }
    else if(strcmp(array[mid]->string,string) < 0){
        return _binarySearch(array,mid+1,right,string);
    }
    return -1;
}

int binarySearch(Dictionary *dict, char *string){
    if(!dict->size)
        return -1;
    return _binarySearch(dict->elements,0,dict->size-1,string);
}

int addDictionary(char *string, int key, Dictionary *dict){
    if(!dict)
        return -2;
    int pos;
    int cmp = -1;
    for(pos = 0; pos < dict->size && cmp < 0; pos++){
        cmp = strcmp(dict->elements[pos]->string, string);
    }
    if(cmp > 0)
        pos--;
    if(!cmp)
        return dict->elements[--pos]->key;
    dict->size++;
    dict->elements = (dictElement**)realloc(dict->elements, (dict->size)*sizeof(dictElement*));
    if(pos < dict->size){
        memmove(&dict->elements[pos+1],&dict->elements[pos],(dict->size-pos-1)*sizeof(dictElement*));
    }
    dict->elements[pos] = _createDictElem(string, key);
    return dict->elements[pos]->key;
}

int getDictionaryKey(char *string, Dictionary *dict){
    int pos = binarySearch(dict, string);
    if(pos >= 0)
        return dict->elements[pos]->key;
    return -1;
}

char *getDictionaryValue(int id, Dictionary *dict){
    int pos;
    for(pos = 0; pos < dict->size && dict->elements[pos]->key != id; pos++);
    if(pos < dict->size)
        return dict->elements[pos]->string;
    return NULL;
}

void freeDictionary(Dictionary *dict){
    int i;
    for(i = 0; i < dict->size; i++){
        free(dict->elements[i]->string);
        free(dict->elements[i]);
    }
    free(dict->elements);
    free(dict);
}