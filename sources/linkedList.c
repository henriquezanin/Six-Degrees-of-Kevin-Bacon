/*
* Nome: Henrique Gomes Zanin
* nUSP: 10441321
*
* Nome: Gabriel Guimarães Vilas Boas Marin
* nUSP: 11218521
*/
#include <stdlib.h>
#include <stdio.h>
#include <utils.h>
#include <graph.h>
#include <linkedList.h>

List *newList(){
    return (List*)calloc(1,sizeof(List*));
}

listElement *_newListElement(int id, void *element){
    listElement *new = (listElement*)calloc(1, sizeof(listElement));
    new->element = element;
    new->id = id;
    return new;
}

Error *addElement(int id,void *element, int pos,List *list){
    Error *err = newError();
    if(!list){
        ErrorFormat("addElement: Null List", err);
        return err;
    }
    else if(pos > list->nElements || pos < 0){
        ErrorFormat("addElement: invalid position", err);
        return err;
    }
    listElement *new = _newListElement(id ,element);
    listElement **p = &list->first;
    int i;
    for(i = 0; i < pos; i++)
        p = &(*p)->next;
    new->next = *p;
    *p = new;
    list->nElements++;
    return err;
}

Error *addFirst(int id, void *element, List *list){
    Error *err = addElement(id,element,0,list);
    if(hasError(err))
        ErrorFormat("addFirst: Failed to add first element", err);
    return err;
}

Error *addLast(int id, void *element, List *list){
    Error *err = addElement(id,element,list->nElements,list);
    if(hasError(err)) ErrorFormat("addLast: Failed to add last element", err);
    return err;
}

int getElementIDbyPosition(int pos, List *list, Error *err){
    if(!err){
        puts("getElementIDbyPosition: uninitialized error");
        return -1;
    }
    if(!list){
        ErrorFormat("addElement: Null List", err);
        return -1;
    }
    if(pos > list->nElements || pos < 0){
        ErrorFormat("addElement: invalid position", err);
        return -1;
    }
    listElement *p = list->first;
    int i;
    for(i=0;i<pos;i++)
        p = p->next;
    return p->id;
}

void *getElement(int id, List *list){
    if(!list)
        return NULL;
    if(id < 0)
        return NULL;
    void *element;
    listElement *next = list->first;
    while(next && next->id != id){
        next = next->next;
    }
    if(next)
        element = next->element;
    return element;
}   

void **getAllElements(List *list){
    if(!list) return NULL;
    if(!list->nElements) return NULL;
    listElement *next = list->first;
    int i = 0;
    void **elements = (void **)malloc(list->nElements*sizeof(void*));
    while(next){
        elements[i++] = next->element;
        next = next->next;
    }
    return elements;
}

int *getAllIdElements(List *list){
    if(!list) return NULL;
    if(!list->nElements) return NULL;    
    listElement *next = list->first;
    int i = 0;
    int *elements = (int *)malloc(list->nElements*sizeof(int));
    while(next){
        elements[i++] = next->id;
        next = next->next;
    }
    return elements;
}

int getListSize(List *list){
    return list->nElements;
}

int removeElement(int pos, List *list, Error *err){
    if(!err){
        puts("removeElement: uninitialized error");
        return -1;
    }
    if(!list){
        ErrorFormat("removeElement: Null list", err);
        return -1;
    }
    if(pos < 0 || pos >= list->nElements){
        ErrorFormat("removeElement: Invalid position", err);
        return -1;
    }
    if(list->nElements == 0)
        return -1;
    listElement *old;
    listElement **p = &list->first;
    int i, id;
    for(i = 0; i < pos; i++)
        p = &(*p)->next;
    old = *p;
    *p = old->next;
    id = old->id;
    free(old->element);
    free(old);
    list->nElements--;
    return id;
}

int removeFirst(List *list, Error *err){
    if(!err){
        puts("removeFirst: uninitialized error");
        return -1;
    }
    if(!list){
        ErrorFormat("removeFirst: Null list", err);
        return -1;
    }
    return removeElement(0,list,err);
}

int removeLast(List *list, Error *err){
    if(!err){
        puts("removeFirst: uninitialized error");
        return -1;
    }
    if(!list){
        ErrorFormat("removeFirst: Null list", err);
        return -1;
    }
    if(list->nElements == 0)
        return -1;
    return removeElement(list->nElements-1,list,err);
}

/* Passar função de comparação e retirar o id */
void *removeElementById(int id, List *list){
    if(!list)
        return NULL;
    if(!list->nElements)
        return NULL;
    listElement **p = &list->first;
    listElement *old;
    void *element = NULL;
    while(*p && (*p)->id != id){
        p = &(*p)->next; 
    }
    if(*p){
        old = *p;
        *p = old->next;
        element = old->element;
        free(old);
    }
    list->nElements--;
    return element;
}

void **freeList(List *list){
    if(!list)
        return NULL;
    int i = 0;
    listElement *listItem = list->first;
    listElement *old;
    void **elements = NULL;
    if(list->nElements){
        elements = (void **)malloc(sizeof(void*)*list->nElements);
        while(listItem){
            old = listItem;
            listItem = listItem->next;
            elements[i++] = old->element;
            free(old);
        }
    }
    free(list);
    return elements;
}
