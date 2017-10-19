#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include <stdint.h>
#include <stdlib.h>

typedef int32_t bool_t;

typedef struct myList myList;
typedef struct myList myListNode;

struct myList
{
    myListNode *mPrev;
    myListNode *mNext;
    void       *mObject;
};

void   myListAppendNode(myList *aList, myListNode *aNewNode);
void   myListPrependNode(myList *aList, myListNode *aNewNode);
bool_t myListIsEmpty(myList *aList);

void   myListInitNode(myListNode *aNode, void *aObject);
void   myListInit(myList *aList);

#define MY_LIST_ITERATE(aList, aIterator)                                   \
    for ((aIterator) = (aList)->mNext;                                      \
         (aIterator) != (aList);                                            \
         (aIterator) = (aIterator)->mNext)

#define MY_LIST_ITERATE_SAFE(aList, aIterator, aNextNode)                   \
    for ((aIterator) = (aList)->mNext, (aNextNode) = (aIterator)->mNext;    \
         (aIterator) != (aList);                                            \
         (aIterator) = (aNextNode), (aNextNode) = (aIterator)->mNext)

#endif
