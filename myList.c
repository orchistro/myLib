#include "myList.h"

static void myListInsertAfter(myListNode *aAnchorNode, myListNode *aNewNode)
{
    aAnchorNode->mNext->mPrev = aNewNode;
    aNewNode->mNext           = aAnchorNode->mNext;
    aNewNode->mPrev           = aAnchorNode;
    aAnchorNode->mNext        = aNewNode;
}

static void myListInsertBefore(myListNode *aAnchorNode, myListNode *aNewNode)
{
    aAnchorNode->mPrev->mNext = aNewNode;
    aNewNode->mPrev           = aAnchorNode->mPrev;
    aAnchorNode->mPrev        = aNewNode;
    aNewNode->mNext           = aAnchorNode;
}

void myListAppendNode(myList *aList, myListNode *aNewNode)
{
    myListInsertBefore(aList, aNewNode);
}

void myListPrependNode(myList *aList, myListNode *aNewNode)
{
    myListInsertAfter(aList, aNewNode);
}

bool_t myListIsEmpty(myList *aList)
{
    return (aList->mPrev == aList) && (aList->mNext == aList);
}

void myListInitNode(myListNode *aNode, void *aObject)
{
    aNode->mPrev   = aNode;
    aNode->mNext   = aNode;
    aNode->mObject = aObject;
}

void myListInit(myList *aList)
{
    aList->mPrev   = aList;
    aList->mNext   = aList;
    aList->mObject = NULL;
}

