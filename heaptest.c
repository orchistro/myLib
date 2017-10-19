#include "myHeap.h"

typedef struct myData
{
    uint32_t mValue;
} myData;

static myData *myDataCreate(uint32_t aValue)
{
    myData *sData = (myData *)malloc(sizeof(myData));

    if (sData != NULL)
    {
        sData->mValue = aValue;
    }
    else
    {
    }

    return sData;
}

static void myDataDestroy(myData *aData)
{
    free(aData);
}

static myHeapCmpRc myCmpFunc(void *aElem1, void *aElem2)
{
    myData *sElem1 = (myData *)aElem1;
    myData *sElem2 = (myData *)aElem2;

    if (aElem1 == aElem2) 
    {
        return MY_HEAP_EQUAL;
    }
    else
    {
        if (sElem1->mValue > sElem2->mValue)
        {
            return MY_HEAP_GREATER;
        }
        else if (sElem1->mValue < sElem2->mValue)
        {
            return MY_HEAP_LESS;
        }
        else
        {
            return MY_HEAP_EQUAL;
        }
    }
}

static int32_t myDumpfunc(void *aElement)
{
    (void)printf("%d\n", ((myData *)aElement)->mValue);

    return 0;
}

int32_t main(void)
{
    myHeap  *sHeap = NULL;
    myData  *sData;
    int32_t  sValue;

    if (myHeapCreate(&sHeap, myCmpFunc, MY_HEAP_TYPE_MIN) < 0)
    {
        abort();
    }
    else
    {
    }

    while (1)
    {
        (void)printf("value = ");
        scanf("%d", &sValue);

        if (sValue == 9999)
        {
            break;
        }
        else
        {
            sData = myDataCreate(sValue);

            if (sData == NULL)
            {
                abort();
            }
            else
            {
                myHeapPushObject(sHeap, sData);
            }
        }
    }

    myHeapIterate(sHeap, myDumpfunc);

    (void)printf("popping!!\n");

    while ((sData = myHeapPopObject(sHeap)) != NULL)
    {
        (void)printf("%d\n", sData->mValue);
        myDataDestroy(sData);
    }

    myHeapDestroy(sHeap);

    return 0;
}

