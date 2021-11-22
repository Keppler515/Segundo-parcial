/*
 * LinkedList.c
 *
 *  Created on: 21 nov. 2021
 *      Author: maxis
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"

#define CHAR_LEN	64

//PRIVADAS
static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
	LinkedList* this = NULL;
	this = (LinkedList*)malloc(sizeof(LinkedList)); //Asigno espacio dinamico a la lista

	if(this != NULL)
	{
		this->size = 0; //Inicio la lista con tamaño 0
		this->pFirstNode = NULL; //La cabecera apunta a NULL
	}
	return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = this->size; //Retorno el valor de size que deberia ser igual a la cantidad de nodos
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* nAux = NULL;
	int i;

	if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))
	{
		nAux = this->pFirstNode; //Asigno el valor del primer nodo
		//i<nodeIndex me ubica en el nodo anterior al pasado por parametro, que es el que tiene la direccion que necesito
		for(i=0;i<nodeIndex;i++)
		{	//En cada vuelta guardo los nodos consecutivos hasta que termino apuntando al que quiero devolver
			nAux = nAux->pNextNode;
		}
	}
    return nAux;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* nAux;
    Node* nAuxAnt;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<=this->size)
    {
    	nAux = (Node*)malloc(sizeof(Node)); //Creo el espacio para un nuevo nodo

		if(nAux!=NULL)
		{
			nAux->pElement = pElement; //Guardo el elemento en el nodo

			//Primera posicion
			if(nodeIndex==0)
			{
				//Copio la informacion de this->pFirstNode en nAux->pNextNode
				nAux->pNextNode = this->pFirstNode; //Los dos apuntan al mismo nodo
				this->pFirstNode = nAux; //Hago que la cabecera apunte al nodo nuevo
				this->size++; //Incremento el valor de size
			}

			//Ultima posicion
			else if(nodeIndex==this->size)
			{
				nAuxAnt = getNode(this, nodeIndex-1); //Obtengo el nodo
				nAux->pNextNode = NULL; //El nuevo nodo apunta a NULL
				nAuxAnt->pNextNode = nAux; // El nodo que apuntaba a NULL ahora apunta al nuevo nodo
				this->size++;
			}
			//Los del medio
			else
			{
				nAuxAnt = getNode(this, nodeIndex-1); //Obtengo el nodo anterior
				nAux->pNextNode = nAuxAnt->pNextNode; //El nodo nuevo apunta al mismo pNextNode que obtuve
				nAuxAnt->pNextNode = nAux; //Ahora el nodo que original apunta al nuevo
				this->size++;
			}

			returnAux = 0;
		}
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	//Agrega un nodo en la lista con el elemento ingresado
    	returnAux = addNode(this, this->size, pElement);
    }

    return returnAux;
}

/** \brief Devuelve un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int nodeIndex)
{
    void* returnAux = NULL;
    Node* nAux; //Creo un nodo auxiliar para poder acceder a los campos

    if(this!=NULL && nodeIndex >=0 && nodeIndex<this->size)
    {
    	nAux = getNode(this, nodeIndex); //Guardo el nodo recibido en una variable
    	if(nAux!=NULL)
    	{
    		returnAux = nAux->pElement; //Guardo el elemento y lo devuelvo
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* nAux;

    if(this!=NULL && nodeIndex >=0 && nodeIndex<=this->size)
    {
    	nAux = getNode(this, nodeIndex); //Guardo el nodo que apunta al elemento que quiero modificar
    	if(nAux!=NULL)
    	{
    		nAux->pElement = pElement; //El nodo apunta al nuevo elemento
    		returnAux = 0;
    	}
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int nodeIndex)
{
    int returnAux = -1;
       Node* nAux = NULL;
       Node* nAuxAnt = NULL;

	if(this!=NULL && nodeIndex>=0 && nodeIndex<=this->size)
	{

		nAux = getNode(this, nodeIndex); //Obtengo el nodo
		if(nAux!=NULL)
		{
			//Primera posicion
			if(nodeIndex==0)
			{
				this->pFirstNode = nAux->pNextNode; //Guardo en la cabecera la direccion del siguiente nodo
				free(nAux); //Libero el espacio del nodo eliminado
				this->size--; //Decremento el valor de size
			}

			//Ultima posicion
			else if(nodeIndex==this->size)
			{
				nAuxAnt = getNode(this, nodeIndex-1); //Obtengo el nodo anterior
				nAuxAnt->pNextNode = NULL; //Ahora el anterior pasa a ser el ultimo y apunta a NULL
				free(nAux); //Libero el espacio del nodo eliminado
				this->size--;
			}
			//Los del medio
			else
			{
				nAuxAnt = getNode(this, nodeIndex-1); //Obtengo el nodo anterior
				nAuxAnt->pNextNode = nAux->pNextNode; //El nodo anterior apunta al mismo pNextNode que el nodo a eliminar
				free(nAux); //Libero el espacio del nodo eliminado
				this->size--;
			}

			returnAux = 0;
		}
	}


    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;

    if(this!=NULL)
    {
    	for(i=0;i<this->size;i++)
    	{
    		ll_remove(this, i); //Recorro la lista y elimino cada nodo
    	}
    	returnAux = 0;
    }


    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
		ll_clear(this); //Llamo a la funcion para eliminar cada nodo
		free(this); //Libero el espacio creado con malloc
		returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
    Node* aux;

    if(this!=NULL)
    {
    	for(i=0;i<this->size;i++) //Recorro la lista
    	{
    		aux = getNode(this, i); //En cada vuelta guardo el nodo que hay en la posicion i...
    		if(aux->pElement == pElement)	//Y comparo los punteros a los elementos. Si son iguales...
    		{
				returnAux = i;	//El valor de retorno es la posicion del elemento
				break;

    		}
    	}
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this!=NULL)
    {
    	if(this->size == 0) //Si size == 0 la lista esta vacia
    	{
			returnAux = 1;
    	}
		else
			returnAux = 0;
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int nodeIndex, void* pElement)
{
    int returnAux = -1;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<=this->size)
    {
    	addNode(this, nodeIndex, pElement); //Agreo un nodo en la posicion nodeIndex
    	returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int nodeIndex)
{
    void* returnAux = NULL;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<this->size)
    {
    	returnAux = ll_get(this, nodeIndex);
    	ll_remove(this, nodeIndex);
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int aux;

    if(this!=NULL)
    {
    	//ll_indexOf devuelve el indice si el elemento se encuentra en la lista
    	aux = ll_indexOf(this, pElement);

    	if(aux >= 0) //Si el indice es >=0 existe
    	{
    		returnAux = 1;
    	}
    	else //Si el indice es <0 no existe
    	{
    		returnAux = 0;
    	}
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
    int aux;
    Node* aux2;

    if(this!=NULL && this2!=NULL)
    {
    	aux2 = this2->pFirstNode; //Guardo el primer nodo de la lista 2 para cotejarlo con la lista 1
    	for(i=0;i<this2->size;i++)
    	{
    		aux = ll_contains(this, aux2->pElement); //Si esta en la lista guardo un valor >0

    		//Si aunque sea un solo elemento NO está en la lista devuelvo 0 y salgo del for
    		if(aux == 0)
    		{
    			returnAux = 0;
    			break;
    		}
    		else if(aux == 1)
    		{
				//Modifico el nodo por el siguiente para tomar el siguiente elemento y ssigo iterando
				aux2 = aux2->pNextNode;
    		}
    	}
    	returnAux = aux;
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    Node* clon;

    if(this!=NULL && from >=0 && from<=ll_len(this) && to>from  && to<=ll_len(this))
    {
    	cloneArray = ll_newLinkedList(); //Creo una nueva LL
    	if(cloneArray!=NULL)
    	{
			for(i=from;i<to;i++) //Desde from hasta to
			{
				clon = ll_get(this, i); //Obtengo los elementos
				if(clon!=NULL)
				ll_add(cloneArray, clon); //Los copio en la LL nueva
			}
    	}
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this!=NULL)
    {
		cloneArray = ll_newLinkedList(); //Creo una nueva LL
		cloneArray = this; //La igualo a la original
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param this LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int i;
    int flag;
    void* aux1;
    void* aux2;
    void* buffer;
    int criterio;

    if(this!=NULL && pFunc!=NULL && (order == 0 || order == 1))
    {
    	do
    	{
    		flag = 0;

    		for(i=0;i<ll_len(this)-1;i++)
    		{
    			//Guardo los elementos 1 y 2
    			aux1 = ll_get(this, i);
    			aux2 = ll_get(this, i+1);
    			criterio = pFunc(aux1,aux2); //Guardo el valor de retorno de la funcion criterio

    			if(order == 1)	//Orden ascendente
    			{
    				if(criterio == 1)
    				{
						flag = 1;
						buffer = aux1;
						aux1 = aux2;
						aux2 = buffer;
					}
    				//Escribo los valores ordenados
					ll_set(this, i, aux1);
					ll_set(this, i+1, aux2);
    			}

    			 if(order == 0) //Orden descendente
    			{
    				if(criterio == -1)
    				{
						flag = 1;
						buffer = aux2;
						aux2 = aux1;
						aux1 = buffer;
    				}
				//Escribo los valores ordenados
				ll_set(this, i, aux2);
				ll_set(this, i+1, aux1);
    			}
    		}

    	}while(flag);
	returnAux = 0;
    }

    return returnAux;
}


//******************************//

/** \brief 	Toma cada uno de los elementos de la lista, y se lo pasa a la funcion
 * 			para que haga algo con ese elemento (ej : leer un campo y cambiar el valor)
 *
 * \param 	this LinkedList* puntero a la lista
 * \param	pFunc puntero a funcion
 * \return	0 OK / -1 Mal
 */

int ll_map(LinkedList* this, int(*pFunc)(void*))
{
	int retorno = -1;
	void* pAux;

	//Verificar nulidad
	if(this!=NULL && pFunc!=NULL)
	{
		//Recorrer lista
		for(int i=0;i<=ll_len(this);i++)
		{
			//Tomo el elemento
			pAux = ll_get(this, i);

			if(pAux!=NULL)
			{
				//Mapeo
				pFunc(pAux);
			}

		}
		retorno = 0;
	}

	return retorno;
}


//******************************//

/** \brief	Crea otra linkedlist con los filtros indicados.
 *
 * \param 	this LinkedList* puntero a la lista
 * \param	pFunc puntero a funcion criterio
 * \return	Nueva lista con los filtros indicados
 */

LinkedList* ll_filter(LinkedList* this, int(*pFunc)(void*))
{
	//int retorno = -1;
	int criterio;
	void* pAux;
	LinkedList* listaFiltrada;

	if(this!=NULL && pFunc!=NULL)
	{
		listaFiltrada = ll_newLinkedList(); //Creo una nueva lista

		//Recorro mi lista
		for(int i=0;i<ll_len(this);i++)
		{
			//Tomo el elemento
			pAux = ll_get(this, i);

			//Filtro
			criterio = pFunc(pAux);

			//Si criterio == 1 agrego el elemento a la lista nueva
			if(criterio == 1)
			{
				ll_add(listaFiltrada, pAux);
			}
		}
	}

	return listaFiltrada;
}


