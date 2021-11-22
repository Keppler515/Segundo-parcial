/*
 * Arcade.h
 *
 *  Created on: 21 nov. 2021
 *      Author: maxis
 */
#include "LinkedList.h"

#ifndef ARCADE_H_
#define ARCADE_H_

typedef struct
{
	char nacionalidad[128];
	char tipo[128];
	int jugadores;
	int fichasMax;
	char nombreJuego[128];
	int idArcade;
	char nombreSalon[128];
}Arcade;


Arcade* arcade_new();
Arcade* arcade_newParametros(char* idArcadeStr,char* nacStr,char* tipoStr,char* jugadoresStr,char* fichasStr,char* salonStr,char* juegoStr);
void arcade_delete(Arcade* this);

int arcade_setIdArcade(Arcade* this,int idArcade);
int arcade_getIdArcade(Arcade* this,int* idArcade);

int arcade_setNombreJuego(Arcade* this,char* nombreJuego);
int arcade_getNombreJuego(Arcade* this,char* nombreJuego);

int arcade_setNac(Arcade* this,char* nacionalidad);
int arcade_getNac(Arcade* this,char* nacionalidad);

int arcade_setTipo(Arcade* this,char* tipoAudio);
int arcade_getTipo(Arcade* this,char* tipoAudio);

int arcade_setJugadores(Arcade* this,int cantidadJugadores);
int arcade_getJugadores(Arcade* this,int* cantidadJugadores);

int arcade_setFichas(Arcade* this,int maxFichas);
int arcade_getFichas(Arcade* this,int* maxFichas);

int arcade_setNombreSalon(Arcade* this,char* nombreSalon);
int arcade_getNombreSalon(Arcade* this,char* nombreSalon);

int arcade_setIdSalon(Arcade* this,int idSalon);
int arcade_getIdSalon(Arcade* this,int* idSalon);

int arcade_generadorID(LinkedList*);

int arcade_comparaJuegos(void* item1, void* item2);
int arcade_comparaPaises(void* juego1, void* juego2);
int arcade_comparaIdArcade(void* item1, void* item2);

int arcade_aumentaFichas(void* arcade);
int arcade_multiPLayer(void* juego);

int arcade_idMax(LinkedList* this);

int arcade_imprimirJuegos(char* path , LinkedList* this);

#endif /* ARCADE_H_ */
