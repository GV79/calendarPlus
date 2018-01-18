/***************************************************************************************
CIS2750 F2017
Assignment 0
Gia Vinh Lam
0925571

Ths function contains the implementation of an  abstract linked list with an iterator.
Details regarding functions can be found in the header file LinkedListAPI.h

CIS2520 (Fangju Wang) - Looked at my linked list code to refresh my knowledge.
Permission to use this code was granted by my current cis2750 professor Denis Nitikenko

Compiles with -std=c11 -Wall and -pedantic tags.
****************************************************************************************/

#include "LinkedListAPI.h"

List initializeList(char* (*printFunction)(void* toBePrinted),void (*deleteFunction)(void* toBeDeleted),int (*compareFunction)(const void* first,const void* second))
{
    List list;
    list.head = NULL;
    list.tail = NULL;
    list.length = 0;
    list.deleteData = deleteFunction;
    list.compare = compareFunction;
    list.printData = printFunction;
    return list;
}

Node * initializeNode(void * data)
{
    Node * node = malloc(sizeof(Node));
    if (node == NULL)
    {
        exit(0);
    }

    if (node == NULL || data == NULL)
    {
        return NULL;
    }
    else
    {
        node->data = data;
        node->previous = NULL;
        node->next = NULL;
        return node;
    }
}


void insertFront(List * list, void * toBeAdded)
{
    if (toBeAdded == NULL || list == NULL)
    {
        return;
    }

    Node * newNode = initializeNode(toBeAdded);
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->head->previous = newNode;
        newNode->next = list->head;
        newNode->previous = NULL;
        list->head = newNode;
    }
    list->length++;
    return;
}



void insertBack(List * list, void * toBeAdded)
{
    if (toBeAdded == NULL || list == NULL)
    {
        return;
    }

    Node * newNode = initializeNode(toBeAdded);
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        newNode->previous = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
        list->tail->next = NULL;
    }
    list->length++;
    return;
}

void clearList(List * list)
{
    if (list != NULL)
    {
            Node * temp = list->head;
            Node * tempTwo = NULL;
            list->head = NULL;
            list->tail = NULL;
            list->length = 0;
            while (temp != NULL)
            {
                tempTwo = temp->next;
                list->deleteData(temp->data);
                free(temp);	
                temp = tempTwo;
            }
    }
    return;
}

void insertSorted(List* list, void* toBeAdded)
{
    if (toBeAdded == NULL || list == NULL)
    {
        return;
    }

    Node * newNode = initializeNode(toBeAdded);
    if (newNode == NULL)
    {
        return;
    }
    list->length++;
    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
        return;
    }
    while (list->head != NULL)
    {
        if (list->compare(list->head->data, toBeAdded) <= 0)
        {
            if (list->head == list->tail)
            {
                list->head->next = newNode;
                newNode->previous = list->head;
                newNode->next = NULL;
                list->tail = newNode;

                while (list->head->previous != NULL)
                {
                    list->head = list->head->previous;
                }
                return;
            }

            if (list->compare(list->head->next->data, toBeAdded) >= 0)
            {
                newNode->next = list->head->next;
                newNode->previous = list->head;
                list->head->next->previous = newNode;
                list->head->next = newNode;
                while (list->head->previous != NULL)
                {
                    list->head = list->head->previous;
                }
                return;
            }
        }
        else
        {
            list->head->previous = newNode;
            newNode->previous = NULL;
            newNode->next = list->head;
            list->head = newNode;
            return;
        }
        list->head = list->head->next;
    }
    return;
}

void* deleteDataFromList(List* list, void* toBeDeleted)
{
    if (list == NULL || toBeDeleted == NULL)
    {
        return NULL;
    }
    else
    {
    	void * dataDeleted = toBeDeleted;
    	Node * temp = list->head;
        while (list->head != NULL)
        {
            if (list->compare(list->head->data, toBeDeleted) == 0)
            {
                if (list->head->previous == NULL && list->head->next == NULL)
                {
                    free(temp);
                    list->head = NULL;
                    list->tail = NULL;
                    list->length = 0;
                    return NULL;
                }

                if (list->length > 0)
                {
                    list->length--;
                }

                if (list->head->previous == NULL)
                {
                    list->head->next->previous = NULL;
                    temp = list->head;
                    list->head = list->head->next;
                    dataDeleted = temp->data;
                    free(temp);
                    return dataDeleted;
                }
                else if (list->head->next == NULL)
                {
                    list->head->previous->next = NULL;
                    list->tail = list->head->previous;
                    temp = list->head;
                    while (list->head->previous != NULL)
                    {
                        list->head = list->head->previous;
                    }
                    dataDeleted = temp->data;
                    free(temp);
                    return dataDeleted;
                }
                else
                {
                    temp = list->head;
                    list->head->previous->next = list->head->next;
                    list->head->next->previous = list->head->previous;
                    while (list->head->previous != NULL)
                    {
                        list->head = list->head->previous;
                    }
                    dataDeleted = temp->data;
                    free(temp);
                    return dataDeleted;
                }
            }
            list->head = list->head->next;
        }
        list->head = temp;
        return NULL;
    }
}

void * getFromFront(List list)
{
    if (list.head == NULL)
    {
        return NULL;
    }
    return list.head->data;
}


void * getFromBack(List list)
{
    if (list.tail == NULL)
    {
        return NULL;
    }
    return list.tail->data;
}

char * toString(List list)
{
    List temp = list;
    char * pointer;
    int amount = 0;
    if (list.head != NULL)
    {
        while (temp.head != NULL)
        {
            pointer = list.printData(temp.head->data);
            amount = amount + strlen(pointer)+3;
            free(pointer);
            temp.head = temp.head->next;
        }
	char * listData = calloc(amount, sizeof(char));
        while (list.head != NULL)
        {

            pointer = list.printData(list.head->data);
            listData = strcat(listData, pointer);
            free(pointer);
            listData = strcat(listData, " ");
            list.head = list.head->next;
        }
        return listData;
    }
    return NULL;
}

ListIterator createIterator(List list)
{
    ListIterator iter;

    if (list.head != NULL )
    {
        iter.current = list.head;
    }
    return iter;
}

void * nextElement(ListIterator * iter)
{
    void * storage;
    if (iter->current != NULL)
    {
        storage = iter->current->data;
        iter->current = iter->current->next;
        return storage;
    }
    return NULL;
}

// try doing List list without mallocing or initializing and pass it in maybe
int getLength(List list) /// how to check if it exists??
{
    return list.length;
}

void* findElement(List list, bool (*customCompare)(const void* first,const void* second), const void* searchRecord)
{
    while (list.head != NULL)
    {
        if (customCompare(list.head->data, searchRecord))
        {
            return list.head->data;
        }
        list.head = list.head->next;
    }
    return NULL;
}

