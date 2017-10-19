#include "myList.h"
#include "myHeap.h"

struct myHeap
{
    myHeapType    mType;
    myHeapCmpCb  *mCmpFunc;

    uint32_t      mElementCnt;
    uint32_t      mArraySize; /* unit : sizeof(void *) */
    void        **mArray;
};

int32_t myHeapCreate(myHeap **aHeap, myHeapCmpCb *aCmpFunc, myHeapType aType)
{
    myHeap *sHeap = NULL;

    sHeap = (myHeap *)malloc(sizeof(myHeap));
    if (sHeap == NULL)
    {
        return -1;
    }
    else
    {
    }

    sHeap->mType       = aType;
    sHeap->mElementCnt = 0;
    sHeap->mCmpFunc    = aCmpFunc;
    sHeap->mArraySize  = 1024;

    sHeap->mArray = (void **)malloc(sizeof(void *) * sHeap->mArraySize);
    if (sHeap->mArray == NULL)
    {
        free(sHeap);
        return -1;
    }
    else
    {
    }

    *aHeap = sHeap;

    return 0;
}

void myHeapDestroy(myHeap *aHeap)
{
    assert(aHeap->mElementCnt == 0);

#ifdef MY_DEBUG
    memset(aHeap->mArray, 0xDE, aHeap->mArraySize * sizeof(void *));
#endif
    free(aHeap->mArray);

#ifdef MY_DEBUG
    memset(aHeap, 0xDE, sizeof(myHeap));
#endif
    free(aHeap);
}

static int32_t myHeapExpandArray(myHeap *aHeap)
{
    size_t   sNewArraySize;
    void   **sTempArray;

    sNewArraySize = aHeap->mArraySize * 2;

    sTempArray = (void **)realloc(aHeap->mArray, sNewArraySize);

    if (sTempArray == NULL)
    {
        return -1;
    }
    else
    {
        aHeap->mArray     = sTempArray;
        aHeap->mArraySize = (uint32_t)sNewArraySize;
        return 0;
    }
}

static void myHeapSwapObjects(myHeap *aHeap, uint32_t aParentIndex, uint32_t aChildIndex)
{
    void *sTmpObject;

    sTmpObject                  = aHeap->mArray[aParentIndex];
    aHeap->mArray[aParentIndex] = aHeap->mArray[aChildIndex];
    aHeap->mArray[aChildIndex]  = sTmpObject;
}

static void myHeapBubbleUp(myHeap *aHeap, uint32_t aStartIndex)
{
    uint32_t  sParentIndex;
    void     *sParentObject;

    uint32_t  sChildIndex;
    void     *sChildObject;

    if (aStartIndex == 0)
    {
        return;
    }
    else
    {
    }

    sParentIndex  = (aStartIndex - 1) / 2;
    sParentObject = aHeap->mArray[sParentIndex];

    sChildIndex   = aStartIndex;
    sChildObject  = aHeap->mArray[sChildIndex];

    if (aHeap->mType == MY_HEAP_TYPE_MAX)
    {
        /* MAX heap */

        if ((*aHeap->mCmpFunc)(sParentObject, sChildObject) == MY_HEAP_LESS)
        {
            myHeapSwapObjects(aHeap, sParentIndex, sChildIndex);
            myHeapBubbleUp(aHeap, sParentIndex);
        }
        else
        {
            return;
        }
    }
    else
    {
        /* MIN heap */

        if ((*aHeap->mCmpFunc)(sParentObject, sChildObject) == MY_HEAP_GREATER)
        {
            myHeapSwapObjects(aHeap, sParentIndex, sChildIndex);
            myHeapBubbleUp(aHeap, sParentIndex);
        }
        else
        {
            return;
        }
    }
}

void myHeapPushObject(myHeap *aHeap, void *aObjectToPush)
{
    if (aHeap->mElementCnt >= aHeap->mArraySize)
    {
        assert(myHeapExpandArray(aHeap) == 0);
    }
    else
    {
    }

    aHeap->mArray[aHeap->mElementCnt] = aObjectToPush;

    myHeapBubbleUp(aHeap, aHeap->mElementCnt);

    aHeap->mElementCnt++;
}

static void myHeapBubbleDown(myHeap *aHeap, uint32_t aStartIndex);

static myHeapCmpRc gBubbleDownCondition[] =
{
    MY_HEAP_LESS,       /* MAX heap */
    MY_HEAP_GREATER     /* MIN heap */
};

/*
 * aCondition is MY_HEAP_LESS when the heap is MAX heap
 *               MY_HEAP_GREATER when the heap is MIN heap
 */
static void myHeapBubbleDownInternal(myHeap     *aHeap,
                                     uint32_t    aParentIndex,
                                     uint32_t    aLeftChildIndex,
                                     uint32_t    aRightChildIndex,
                                     myHeapCmpRc aCondition)
{
    void *sParentObject     = aHeap->mArray[aParentIndex];
    void *sLeftChildObject  = NULL;
    void *sRightChildObject = NULL;

    if (aLeftChildIndex >= aHeap->mElementCnt)
    {
        return;
    }
    else
    {
    }

    sLeftChildObject = aHeap->mArray[aLeftChildIndex];

    if ((*aHeap->mCmpFunc)(sParentObject, sLeftChildObject) == aCondition)
    {
        if (aRightChildIndex >= aHeap->mElementCnt)
        {
            /* biggest is LeftChild */
            myHeapSwapObjects(aHeap, aParentIndex, aLeftChildIndex);
            myHeapBubbleDown(aHeap, aLeftChildIndex);
        }
        else
        {
            sRightChildObject = aHeap->mArray[aRightChildIndex];

            if ((*aHeap->mCmpFunc)(sLeftChildObject, sRightChildObject) == aCondition)
            {
                /* biggest is RightChild */
                myHeapSwapObjects(aHeap, aParentIndex, aRightChildIndex);
                myHeapBubbleDown(aHeap, aRightChildIndex);
            }
            else
            {
                /* biggest is LeftChild */
                myHeapSwapObjects(aHeap, aParentIndex, aLeftChildIndex);
                myHeapBubbleDown(aHeap, aLeftChildIndex);
            }
        }
    }
    else
    {
        if (aRightChildIndex >= aHeap->mElementCnt)
        {
            return;
        }
        else
        {
            sRightChildObject = aHeap->mArray[aRightChildIndex];

            if ((*aHeap->mCmpFunc)(sParentObject, sRightChildObject) == aCondition)
            {
                /* biggest is RightChild */
                myHeapSwapObjects(aHeap, aParentIndex, aRightChildIndex);
                myHeapBubbleDown(aHeap, aRightChildIndex);
            }
            else
            {
                /* biggest is Parent */
                return;
            }
        }
    }
}

static void myHeapBubbleDown(myHeap *aHeap, uint32_t aStartIndex)
{
    uint32_t  sParentIndex;
    uint32_t  sLeftChildIndex;
    uint32_t  sRightChildIndex;

    if (aHeap->mElementCnt <= aStartIndex)
    {
        return;
    }
    else
    {
    }

    sParentIndex      = aStartIndex;
    sLeftChildIndex   = sParentIndex * 2 + 1;
    sRightChildIndex  = sLeftChildIndex + 1;

    myHeapBubbleDownInternal(aHeap,
                             sParentIndex,
                             sLeftChildIndex,
                             sRightChildIndex,
                             gBubbleDownCondition[aHeap->mType]);
}

void *myHeapPopObject(myHeap *aHeap)
{
    void *sRetObject;

    if (aHeap->mElementCnt > 0)
    {
        sRetObject       = aHeap->mArray[0];
        aHeap->mArray[0] = aHeap->mArray[aHeap->mElementCnt - 1];
        aHeap->mArray[aHeap->mElementCnt - 1] = NULL;

        aHeap->mElementCnt--;

        myHeapBubbleDown(aHeap, 0);
    }
    else
    {
        return NULL;
    }

    return sRetObject;
}

void myHeapIterate(myHeap *aHeap, myHeapIterateCb *aCallback)
{
    uint32_t i;

    for (i = 0; i < aHeap->mElementCnt; i++)
    {
        (void)(*aCallback)(aHeap->mArray[i]);
    }
}

