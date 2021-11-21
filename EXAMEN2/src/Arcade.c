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


//********************//

Arcade* arcade_new()
{
	return (Arcade*) malloc(sizeof(Arcade));
}

//********************//

Arcade* arcade_newParametros(char* idArcadeStr,char* nacStr,char* tipoStr,char* jugadoresStr,char* fichasStr,char* salonStr,char* juegoStr)
{
	Arcade* thisAux;
	int idArcadeAux;
	int tipoAux;
	int fichasAux;
	int jugadoresAux;

	thisAux = (Arcade*) malloc(sizeof(Arcade));

	if(esNumerica(idArcadeStr)==0 && /*esNumerica(tipoStr)==0 && */esNumerica(jugadoresStr)==0 && esNumerica(fichasStr)==0)
	{
		idArcadeAux = atoi(idArcadeStr);
		tipoAux = atoi(tipoStr);
		fichasAux = atoi(fichasStr);
		jugadoresAux = atoi(jugadoresStr);

		arcade_setNac(thisAux, nacStr);
		arcade_setIdArcade(thisAux, idArcadeAux);
		arcade_setTipo(thisAux, tipoAux);
		arcade_setJugadores(thisAux, jugadoresAux);
		arcade_setFichas(thisAux, fichasAux);
		arcade_setNombreJuego(thisAux, juegoStr);
		arcade_setNombreSalon(thisAux, salonStr);
	}

	return thisAux;
}

//********************//

void arcade_delete(Arcade* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

//********************//

int arcade_setNombreJuego(Arcade* this,char* nombre)
{
	strncpy(this->nombreJuego,nombre,sizeof(this->nombreJuego));

	return 0;
}

//********************//

int arcade_setNombreSalon(Arcade* this,char* nombreSalon)
{
	strncpy(this->nombreSalon,nombreSalon,sizeof(this->nombreSalon));

	return 0;
}

//********************//

int arcade_setNac(Arcade* this,char* nacionalidad)
{
	strncpy(this->nacionalidad,nacionalidad,sizeof(this->nacionalidad));

	return 0;
}

//********************//

int arcade_setTipo(Arcade* this,int tipoAudio)
{
	this->tipo = tipoAudio;

	return 0;
}

//********************//

int arcade_setJugadores(Arcade* this,int cantidadJugadores)
{
	this->jugadores = cantidadJugadores;

	return 0;
}

//************//

int arcade_setFichas(Arcade* this,int maxFichas)
{
	this->fichasMax = maxFichas;

	return 0;
}

//********************//

int arcade_setIdArcade(Arcade* this,int idArcade)
{
	this->idArcade = idArcade;

	return 0;
}

//********************//

int arcade_setIdSalon(Arcade* this,int idSalon)
{
	this->idArcade = idSalon;

	return 0;
}

//*******GETTERS*************//

int arcade_getNombreJuego(Arcade* this,char* nombreJuego)
{
	//strncpy(nombre,this->nombre,sizeof(128));
	strcpy(nombreJuego,this->nombreJuego);

	return 0;
}

//********************//

int arcade_getNombreSalon(Arcade* this,char* nombreSalon)
{
	//strncpy(nombre,this->nombre,sizeof(128));
	strcpy(nombreSalon,this->nombreSalon);

	return 0;
}

//********************//

int arcade_getIdArcade(Arcade* this,int* idArcade)
{
	*idArcade = this->idArcade;

	return 0;
}

//********************//

int arcade_getNac(Arcade* this,char* nacionalidad)
{
	//strncpy(nombre,this->nombre,sizeof(128));
	strcpy(nacionalidad,this->nacionalidad);

	return 0;
}

//********************//

int arcade_getTipo(Arcade* this,int* tipoAudio)
{
	*tipoAudio = this->tipo;

	return 0;
}

//********************//

int arcade_getJugadores(Arcade* this,int* cantidadJugadores)
{
	*cantidadJugadores = this->jugadores;

	return 0;
}

//********************//

int arcade_getFichas(Arcade* this,int* maxFichas)
{
	*maxFichas = this->fichasMax;

	return 0;
}



//********************//


int arcade_comparaJuegos(void* juego1, void* juego2)
{
	int retorno = 0;

	Arcade* aAuxA = (Arcade*) juego1;
	Arcade* aAuxB = (Arcade*) juego2;
	char nombreAuxA[128];
	char nombreAuxB[128];

	if(arcade_getNombreJuego(aAuxA, nombreAuxA)==0 && arcade_getNombreJuego(aAuxB, nombreAuxB)==0)
	{
		retorno = strcmp(nombreAuxA,nombreAuxB);
	}


	return retorno;
}

//********************//


int arcade_comparaPaises(void* juego1, void* juego2)
{
	int retorno = 0;

	Arcade* aAuxA = (Arcade*) juego1;
	Arcade* aAuxB = (Arcade*) juego2;
	char nombreAuxA[128];
	char nombreAuxB[128];

	if(arcade_getNac(aAuxA, nombreAuxA)==0 && arcade_getNac(aAuxB, nombreAuxB)==0)
	{
		retorno = strcmp(nombreAuxA,nombreAuxB);
	}


	return retorno;
}

//********************//


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

int arcade_generadorID(LinkedList* this)
{
	static int contador;
	contador = arcade_idMax(this);
	return contador;
}

//********************//


int arcade_aumentaFichas(void* arcade)
{
	int retorno = -1;
	int fichas;
	Arcade* aAux;

		aAux = (Arcade*)arcade;
		arcade_getFichas(aAux, &fichas);
		fichas = fichas*2;
		arcade_setFichas(aAux, fichas);


	return retorno;
}

//********************//

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
			 idAux = aAux->idArcade;

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


