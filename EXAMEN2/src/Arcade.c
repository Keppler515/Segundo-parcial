/*
 * Arcade.c
 *
 *  Created on: 21 nov. 2021
 *      Author: maxis
 */



#include "utn_biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arcade.h"
#include "LinkedList.h"

#define CHAR_LEN	64

//********************//

/** \brief	Crea un nuevo espacio de memoria para un elemento arcade
 *
 * \return 	Retorna un nuevo elemento
 *
 */

Arcade* arcade_new()
{
	return (Arcade*) malloc(sizeof(Arcade));
}

//********************//

/** \brief	Crea un nuevo espacio de memoria para un elemento arcade y le asigna valores
 * \ param	char* recibe todos los parametros como array de char
 *
 * \ return	Devuelve un nuevo elemento arcade con los datos cargados
 *
 */

Arcade* arcade_newParametros(char* idArcadeStr,char* nacStr,char* tipoStr,char* jugadoresStr,char* fichasStr,char* salonStr,char* juegoStr)
{
	Arcade* thisAux;
	int idArcadeAux;
	int fichasAux;
	int jugadoresAux;

	thisAux = (Arcade*) malloc(sizeof(Arcade));

	//Valido los campos numericos
	if(esNumerica(idArcadeStr)==0 && esNumerica(jugadoresStr)==0 && esNumerica(fichasStr)==0)
	{
		//Guardo el valor del tipo int
		idArcadeAux = atoi(idArcadeStr);
		fichasAux = atoi(fichasStr);
		jugadoresAux = atoi(jugadoresStr);

		//Asigno cada campo
		arcade_setNac(thisAux, nacStr);
		arcade_setIdArcade(thisAux, idArcadeAux);
		arcade_setTipo(thisAux, tipoStr);
		arcade_setJugadores(thisAux, jugadoresAux);
		arcade_setFichas(thisAux, fichasAux);
		arcade_setNombreJuego(thisAux, juegoStr);
		arcade_setNombreSalon(thisAux, salonStr);
	}

	return thisAux;
}

//********************//

/** \brief	Elimina un elemento arcade y libera el espacio de memoria
 * \ param	Arcade* puntero al arcade
 *
 * \ return	void
 *
 */

void arcade_delete(Arcade* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

//********************//

/** \brief	Asigna valores al campo nombre del juego
 * \ param	char* recibe el nombre del juego
 *
 * \ return	0 OK / -1 si arcade o nombre es NULL
 *
 */

int arcade_setNombreJuego(Arcade* this,char* nombre)
{
	int retorno = -1;
	if(this!=NULL && nombre!=NULL)
	{
		strncpy(this->nombreJuego,nombre,sizeof(this->nombreJuego));
		retorno = 0;
	}
	return retorno;
}

//********************//

/** \brief	Asigna valores al campo nombre del salon
 * \ param	char* recibe el nombre del salon
 *
 * \ return	0 OK / -1 si arcade o nombre es NULL
 *
 */

int arcade_setNombreSalon(Arcade* this,char* nombreSalon)
{
	int retorno = -1;
	if(this!=NULL && nombreSalon!=NULL)
	{
		strncpy(this->nombreSalon,nombreSalon,sizeof(this->nombreSalon));
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Asigna valores al campo nacionalidad del juego
 * \ param	char* recibe el nombre del pais
 *
 * \ return	0 OK / -1 si arcade o nacionalidad es NULL
 *
 */

int arcade_setNac(Arcade* this,char* nacionalidad)
{
	int retorno = -1;
	if(this!=NULL && nacionalidad!=NULL)
	{
		strncpy(this->nacionalidad,nacionalidad,sizeof(this->nacionalidad));
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Asigna valores al campo tipo de audio
 * \ param	char* recibe el tipo de audio
 *
 * \ return	0 OK / -1 si arcade o tipo es NULL
 *
 */

int arcade_setTipo(Arcade* this,char* tipoAudio)
{
	int retorno = -1;
	if(this!=NULL && tipoAudio!=NULL)
	{
		strcpy(this->tipo,tipoAudio);
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Asigna valores al campo cantidad de jugadores
 * \ param	int recibe la cantidad
 *
 * \ return	0 OK / -1 si arcade es NULL
 *
 */

int arcade_setJugadores(Arcade* this,int cantidadJugadores)
{
	int retorno = -1;
	if(this!=NULL)
	{
		this->jugadores = cantidadJugadores;
		retorno = 0;
	}

	return retorno;
}

//************//

/** \brief	Asigna valores al campo cantidad maxima de fichas
 * \ param	int recibe la cantidad
 *
 * \ return	0 OK / -1 si arcade es NULL
 *
 */

int arcade_setFichas(Arcade* this,int maxFichas)
{
	int retorno = -1;
	if(this!=NULL)
	{
		this->fichasMax = maxFichas;
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Asigna valores al campo ID arcade
 * \ param	int recibe el ID
 *
 * \ return	0 OK / -1 si arcade es NULL
 *
 */

int arcade_setIdArcade(Arcade* this,int idArcade)
{
	int retorno = -1;
	if(this!=NULL)
	{
		this->idArcade = idArcade;
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Asigna valores al campo ID salon
 * \ param	int recibe el ID
 *
 * \ return	0 OK / -1 si arcade es NULL
 *
 */

int arcade_setIdSalon(Arcade* this,int idSalon)
{
	int retorno = -1;
	if(this!=NULL)
	{
		this->idArcade = idSalon;
		retorno = 0;
	}

	return retorno;
}

//*******GETTERS*************//

/** \brief	Devuelve por referencia el valor del campo nombre del juego de la lista
 *
 * \ param	Arcade* this puntero a la lista
 * \ param	char* devuelve el nombre
 *
 * \ return	0 OK / -1 si arcade es NULL o char* es NULL
 *
 */

int arcade_getNombreJuego(Arcade* this,char* nombreJuego)
{
	int retorno = -1;
	if(this!=NULL && nombreJuego!=NULL)
	{
	//strncpy(nombre,this->nombre,sizeof(128));
		strcpy(nombreJuego,this->nombreJuego);
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Devuelve por referencia el valor del campo nombre del salon de la lista
 *
 * \ param	Arcade* this puntero a la lista
 * \ param	char* devuelve el nombre
 *
 * \ return	0 OK / -1 si arcade es NULL o char* es NULL
 *
 */

int arcade_getNombreSalon(Arcade* this,char* nombreSalon)
{
	int retorno = -1;
	if(this!=NULL && nombreSalon!=NULL)
	{
		//strncpy(nombre,this->nombre,sizeof(128));
		strcpy(nombreSalon,this->nombreSalon);
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Devuelve por referencia el valor del campo ID arcade de la lista
 *
 * \ param	Arcade* this puntero a la lista
 * \ param	int* Devuelve el valor
 *
 * \ return	0 OK / -1 si arcade es NULL
 *
 */

int arcade_getIdArcade(Arcade* this,int* idArcade)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*idArcade = this->idArcade;
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Devuelve por referencia el valor del campo nacionalidad de la lista
 *
 * \ param	Arcade* this puntero a la lista
 * \ param	char* devuelve el pais
 *
 * \ return	0 OK / -1 si arcade es NULL o char* es NULL
 *
 */

int arcade_getNac(Arcade* this,char* nacionalidad)
{
	int retorno = -1;
	if(this!=NULL && nacionalidad!=NULL)
	{
		//strncpy(nacionalidad,this->nacionalidad,sizeof(this->nacionalidad));
		strcpy(nacionalidad,this->nacionalidad);
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Devuelve por referencia el valor del campo tipo de audio de la lista
 *
 * \ param	Arcade* this puntero a la lista
 * \ param	char* devuelve el tipo de aucio
 *
 * \ return	0 OK / -1 si arcade es NULL o char* es NULL
 *
 */

int arcade_getTipo(Arcade* this,char* tipoAudio)
{
	int retorno = -1;
	if(this!=NULL && tipoAudio!=NULL)
	{
		//strncpy(tipoAudio,this->tipo,sizeof(this->tipo));
		strcpy(tipoAudio,this->tipo);
		retorno = 0;
	}
	return retorno;
}

//********************//

/** \brief	Devuelve por referencia el valor del campo cantidad de jugadores de la lista
 *
 * \ param	Arcade* this puntero a la lista
 * \ param	int* Devuelve el valor
 *
 * \ return	0 OK / -1 si arcade es NULL
 *
 */

int arcade_getJugadores(Arcade* this,int* cantidadJugadores)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*cantidadJugadores = this->jugadores;
		retorno = 0;
	}

	return retorno;
}

//********************//

/** \brief	Devuelve por referencia el valor del campo maximo de fichas de la lista
 *
 * \ param	Arcade* this puntero a la lista
 * \ param	int* Devuelve el valor
 *
 * \ return	0 OK / -1 si arcade es NULL
 *
 */

int arcade_getFichas(Arcade* this,int* maxFichas)
{
	int retorno = -1;
	if(this!=NULL)
	{
		*maxFichas = this->fichasMax;
		retorno = 0;
	}

	return retorno;
}


//********************//

/** \brief	Funcion criterio. Compara nombre de juegos
 *
 * \ param	void* arcade 1
 * \ param	void* arcade 2
 *
 * \ return	0 si son iguales / -1 si son distintos
 *
 */

int arcade_comparaJuegos(void* juego1, void* juego2)
{
	int retorno = 0;

	Arcade* aAuxA = (Arcade*) juego1;
	Arcade* aAuxB = (Arcade*) juego2;
	char nombreAuxA[CHAR_LEN];
	char nombreAuxB[CHAR_LEN];

	if(arcade_getNombreJuego(aAuxA, nombreAuxA)==0 && arcade_getNombreJuego(aAuxB, nombreAuxB)==0)
	{
		retorno = strcmp(nombreAuxA,nombreAuxB);
	}


	return retorno;
}

//********************//

/** \brief	Funcion criterio. Compara nombre de paises
 *
 * \ param	void* arcade 1
 * \ param	void* arcade 2
 *
 * \ return	0 si son iguales / 1 si A>B / -1 B>A
 *
 */

int arcade_comparaPaises(void* juego1, void* juego2)
{
	int retorno = 0;

	Arcade* aAuxA = (Arcade*) juego1;
	Arcade* aAuxB = (Arcade*) juego2;
	char nombreAuxA[CHAR_LEN];
	char nombreAuxB[CHAR_LEN];

	if(arcade_getNac(aAuxA, nombreAuxA)==0 && arcade_getNac(aAuxB, nombreAuxB)==0)
	{
		retorno = strcmp(nombreAuxA,nombreAuxB);
	}


	return retorno;
}

//********************//

/** \brief	Funcion criterio. Compara ID de arcade
 *
 * \ param	void* arcade 1
 * \ param	void* arcade 2
 *
 * \ return	0 si son iguales / 1 si A>B / -1 si B>A
 *
 */

int arcade_comparaIdArcade(void* item1, void* item2)
{
	int retorno = 0;

	Arcade* aAuxA = (Arcade*) item1;
	Arcade* aAuxB = (Arcade*) item2;
	int idAuxA = aAuxA->idArcade;
	int idAuxB = aAuxB->idArcade;

	if(arcade_getIdArcade(aAuxA, &idAuxA)==0 && arcade_getIdArcade(aAuxB, &idAuxB)==0)
	{
		if(idAuxA>idAuxB)
			retorno = 1;
		else
			retorno = -1;
	}


	return retorno;
}


//********************//

/** \brief	Genera un nuevo ID a partir del ID mas alto registrado
 *
 * \ param	LinkedList* puntero a la lista de arcades
 *
 * \ return	ID nuevo
 *
 */

int arcade_generadorID(LinkedList* this)
{
	static int contador;
	contador = arcade_idMax(this);
	return contador;
}

//********************//

/** \brief	Funcion utilizada en ll_map para duplicar la cantidad maxima de fichas
 *
 * \ param	void* arcade
 *
 * \ return	 0 OK / -1 si no pudo guardar el valor
 *
 */

int arcade_aumentaFichas(void* arcade)
{
	int retorno = -1;
	int fichas;
	Arcade* aAux;

		aAux = (Arcade*)arcade;
		arcade_getFichas(aAux, &fichas);
		fichas = fichas*2;
		if(arcade_setFichas(aAux, fichas)==0)
			retorno = 0;

	return retorno;
}

//********************//

/** \brief	Funcion criterio. Multiplayer
 *
 * \ param	void* arcade 1
 *
 * \ return	1 si el arcade es >1 jugador / -1 si es <2
 *
 */


int arcade_multiPLayer(void* juego)
{
	int retorno = -1;
	int aux;
	Arcade* aAux;

	aAux = (Arcade*)juego;
	arcade_getJugadores(aAux, &aux);

	if(aux>1)
	{
		retorno = 1;
	}

	return retorno;
}

//********************//

/** \brief	Devuelve el ID mas alto de los elementos la lista de arcades
 *
 * \ param	LinkedList* puntero a la lista
 *
 * \ return	ID mas alto
 *
 */


int arcade_idMax(LinkedList* this)
{
	int retorno = -1;
	int i;
	int idMax = 0;
	int idAux = 0;
	Arcade* aAux;

	if(this!=NULL)
	{
		ll_sort(this, arcade_comparaIdArcade, 1);

		for(i=0;i<ll_len(this);i++)
		{
			 aAux = ll_get(this, i);
			 //idAux = aAux->idArcade;
			 arcade_getIdArcade(aAux, &idAux);

			 if(idAux>idMax)
			 {
				 idMax = idAux;
			 }
		}
		retorno = idMax;
	}
	return retorno;
}


//********************//

/** \brief	Imprime por pantalla la lista de los juegos que hay en la lista
 *
 * \ param	char* nombre del archivo que contiene la lista de juegos
 * \ param	LinkedList* puntero a la lista
 *
 * \ return	0 si OK / -1 si hubo un error
 *
 */


int arcade_imprimirJuegos(char* path , LinkedList* this)
{
	int retorno = -1;
	int i;
	char nombreAux[CHAR_LEN];
	Arcade* aAux;
	Arcade* aAux2;
	FILE* pArch = fopen(path,"r");

	if(path!=NULL && pArch!=NULL && this!=NULL)
	{

		ll_sort(this, arcade_comparaJuegos, 1); //Ordeno los juegos por nombre


		printf("\nLISTA DE JUEGOS\n");

		for(i=0;i<ll_len(this)-1;i++)
		{
			aAux = ll_get(this, i);
			aAux2 = ll_get(this, i+1);
			if(strcmp(aAux->nombreJuego,aAux2->nombreJuego)!=0)
			{
				arcade_getNombreJuego(aAux, nombreAux);
				printf("%s\n",nombreAux);
			}
		}
		fclose(pArch);
		retorno = 0;
	}

    return retorno;
}



