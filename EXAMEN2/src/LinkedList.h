/*
 * LinkedList.h
 *
 *  Created on: 21 nov. 2021
 *      Author: maxis
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

struct Node
{
    void* pElement;
    struct Node* pNextNode;
}typedef Node;

struct LinkedList
{
    Node* pFirstNode;
    int size;
}typedef LinkedList;

#endif /* LINKEDLIST_H_ */



//Publicas
LinkedList* ll_newLinkedList(void);//CREA UNA NUEVA LISTA DE PUNTEROS
int ll_len(LinkedList* this);//DEVUELVE EL LARGO DE LA LISTA
Node* test_getNode(LinkedList* this, int nodeIndex);
int test_addNode(LinkedList* this, int nodeIndex,void* pElement);
int ll_add(LinkedList* this, void* pElement);//AGREGA UN NUEVO ELEMENTO(EMPLOYEE) A LA LISTA
void* ll_get(LinkedList* this, int index);//ACCEDE A UN INDICE DE LA LISTA
int ll_set(LinkedList* this, int index,void* pElement);//SETEA ALGUN VALOR EN UN ELEMENTO DE LA LISTA
int ll_remove(LinkedList* this,int index);//REMUEVE UN ELEMENTO INDICADO DE LA LISTA
int ll_clear(LinkedList* this);//LIMPIA LA LISTA(CONVIENE USARLO EN UN AUX)
int ll_deleteLinkedList(LinkedList* this);//ELIMINA LA LINKEDLIST
int ll_indexOf(LinkedList* this, void* pElement);
int ll_isEmpty(LinkedList* this);
int ll_push(LinkedList* this, int index, void* pElement);
void* ll_pop(LinkedList* this,int index);
int ll_contains(LinkedList* this, void* pElement);
int ll_containsAll(LinkedList* this,LinkedList* this2);
LinkedList* ll_subList(LinkedList* this,int from,int to);
LinkedList* ll_clone(LinkedList* this);
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order);//ORDENA LOS ELEMENTOS DE LA LISTA
int ll_map(LinkedList* this, int(*pFunc)(void*));
LinkedList* ll_filter(LinkedList* this, int(*pFunc)(void*));
