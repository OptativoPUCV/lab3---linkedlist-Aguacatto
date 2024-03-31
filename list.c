#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
  List* list=(List*) malloc (sizeof(List));
   list->head = NULL;
   list->tail = NULL;
   list->current = NULL;
   return list;
}

void * firstList(List * list) 
{
  if(list->head == NULL) return NULL;
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list)
{
  if(list->current == NULL) return NULL;
  if(list->current->next==NULL)
  {
    list->current = NULL;
    return NULL;
  }
  list->current=list->current->next;
  return list->current->data;
}

void * lastList(List * list)
{
  if(list->tail == NULL) return NULL;
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) 
{
  if(list->current == NULL) return NULL;
  if(list->current->prev == NULL)
  {
    list->current = NULL;
    return NULL;
  }
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data)
{
  Node* newNode=createNode(data);
  if(list->head) list->head->prev = newNode;
  newNode->next=list->head;
  list->head = newNode;
  if(list->tail == NULL) list->tail=newNode;
}

void pushBack(List * list, void * data)
{
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data)
{
  Node* newNode=createNode(data);
  if(list->head == NULL)
  {
    list->head = newNode;
    list->tail = newNode;
    list->current = newNode;
  }
  else
  {
  if(list->current->next) list->current->next->prev = newNode;
  newNode->next = list->current->next;
  newNode->prev = list->current;
  list->current->next = newNode;
  if(list->tail == list->current) list->tail = newNode;
  }
}

void * popFront(List * list) 
{
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list)
{
  list->current = list->tail;
  return popCurrent(list);
}

void * popCurrent(List * list) 
{
  
  if(list->current == NULL) return NULL;
  void * data = list->current->data;
  if(list->current->prev) list->current->prev->next = list->current->next;
  if(list->current->next) list->current->next->prev = list->current->prev;
  if(list->head == list->current) list->head = list->current->next;
  if(list->tail == list->current) list->tail = list->current->prev;
  free(list->current);
  return data;
}

void cleanList(List * list)
{
  while (list->head != NULL)
  {
    popFront(list);
  }
}