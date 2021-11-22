/*
 * parser.c
 *
 *  Created on: 21 nov. 2021
 *      Author: maxis
 */


#include <stdio.h>
#include <stdlib.h>
#include "Arcade.h"
#include "LinkedList.h"

#define CHAR_LEN	64

/** \brief Parsea los datos de los arcades desde el archivo arcades.csv (modo texto).
 *
 * \param path char*
 * \param pListaArcades LinkedList*
 * \return int
 *
 */
int parser_ArcadeFromText(FILE* pFile , LinkedList* pListaArcades)
{
	int retorno = -1;
	Arcade* aAux;
	char idAux[CHAR_LEN];
	char nacionAux[CHAR_LEN];
	char tipoAux[CHAR_LEN];
	char jugadoresAux[CHAR_LEN];
	char fichasAux[CHAR_LEN];
	char salonAux[CHAR_LEN];
	char juegoAux[CHAR_LEN];

	if(pFile!=NULL && pListaArcades!=NULL)
	{
		//Paso el formato que se va a encontrar en el archivo
		//Lo corro una vez para saltear la cabecera
  		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,salonAux,juegoAux);
		do
		{
			//Si pudo leer la cantidad indicada OK
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,salonAux,juegoAux)==7)
			{
				//Creo un arcade nuevo y le paso por parametros los datos que lei del archivo
				aAux = arcade_newParametros(idAux, nacionAux, tipoAux, jugadoresAux, fichasAux, salonAux, juegoAux);
				if(aAux!=NULL)
				{
					//Si pudo crear el nuevo arcade lo agrego a la LL
					ll_add(pListaArcades, aAux);
					retorno = 0;
				}
			}
			else
			{
				arcade_delete(aAux); //Si alguna linea tiene error elimino el auxiliar y libero la memoria
				break;
			}
		}while(feof(pFile)==0); //feof es siempre 0 mientras no llegue al final del archivo
	}


    return retorno;
}

/** \brief Parsea los datos de los arcades desde el archivo arcades.csv (modo binario).
 *
 * \param path char*
 * \param pListaArcades LinkedList*
 * \return int
 *
 */
int parser_ArcadeFromBinary(FILE* pFile , LinkedList* pListaArcades)
{
	int retorno = -1;
	Arcade* aAux;

	if(pFile!=NULL && pListaArcades!=NULL)
	{
		do
		{
			aAux = arcade_new();
			if(fread(aAux,sizeof(Arcade),1,pFile)==1)
			{
				ll_add(pListaArcades, aAux);
				retorno = 0;
			}
			else
			{
				arcade_delete(aAux);
				break;
			}
		}while(feof(pFile)==0);
	}


    return retorno;
}


