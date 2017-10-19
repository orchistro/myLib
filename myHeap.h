#ifndef __MY_HEAP_H__
#define __MY_HEAP_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct myHeap myHeap;

typedef enum
{
    MY_HEAP_TYPE_MAX,
    MY_HEAP_TYPE_MIN
} myHeapType;

typedef enum
{
    MY_HEAP_EQUAL,
    MY_HEAP_GREATER,
    MY_HEAP_LESS
} myHeapCmpRc;

/*
 * type definitions of callback functions
 */
typedef myHeapCmpRc myHeapCmpCb(void *aElem1, void *aElem2);
typedef int32_t     myHeapIterateCb(void *aElement);

/*
 * Creating / Destroying instance
 */
int32_t  myHeapCreate(myHeap **aHeap, myHeapCmpCb *aCmpFunc, myHeapType aType);
void     myHeapDestroy(myHeap *aHeap);

/*
 * Heap functions
 */
void     myHeapPushObject(myHeap *aHeap, void *aObjectToPush);
void    *myHeapPopObject(myHeap *aHeap);

/*
 * Unitility functions
 */
void     myHeapIterate(myHeap *aHeap, myHeapIterateCb *aCallback);

#endif
