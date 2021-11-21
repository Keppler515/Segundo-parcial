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
	char idAux[32];
	char nacionAux[128];
	char tipoAux[32];
	char jugadoresAux[32];
	char fichasAux[32];
	char salonAux[32];
	char juegoAux[128];

	if(pFile!=NULL)
	{
  		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,salonAux,juegoAux); //SALTEO LA PRIMER LINEA
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,salonAux,juegoAux)==7)
			{
				aAux = arcade_newParametros(idAux, nacionAux, tipoAux, jugadoresAux, fichasAux, salonAux, juegoAux);
				if(aAux!=NULL)
				{
					ll_add(pListaArcades, aAux);
					retorno = 0;
				}
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

/** \brief Parsea los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_ArcadeFromBinary(FILE* pFile , LinkedList* pListaArcades)
{
	int retorno = -1;
	Arcade* aAux;

	if(pFile!=NULL)
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


