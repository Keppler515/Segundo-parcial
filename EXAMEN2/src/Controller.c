/*
 * Controller.c
 *
 *  Created on: 21 nov. 2021
 *      Author: maxis
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arcade.h"
#include "LinkedList.h"
#include "utn_biblioteca.h"
#include "parser.h"

/** \brief Carga los datos de los arcades desde el archivo arcades.csv (modo texto).
 *
 * \param path char* recibe el nombre del archivo
 * \param pListaArcades LinkedList* puntero a la lista
 * \return int 0 OK / -1 Mal
 *
 */
int controller_loadFile(char* path , LinkedList* pListaArcades)
{
	int retorno = -1;
	FILE* pArch;

	if(path!=NULL && pListaArcades!=NULL)
	{
		if((pArch = fopen(path,"r"))!=NULL)
		{
			if(parser_ArcadeFromText(pArch, pListaArcades)==0)
			{
				fclose(pArch);
				retorno = 0;
				puts("Archivo cargado correctamente\n");
			}
		}
		else
		{
			puts("El archivo no puede ser cargado o no existe\n");
		}
	}

    return retorno;
}

/** \brief Carga los datos de los arcades desde el archivo arcades.csv (modo binario).
 *
 * \param path char* recibe el nombre del archivo
 * \param pListaArcades LinkedList* puntero a la lista
 * \return int 0 OK / -1 Mal
 *
 */

int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = -1;
	FILE* pArch;

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		if((pArch = fopen(path,"rb"))!=NULL)
		{
			if(parser_ArcadeFromBinary(pArch, pArrayListEmployee)==0)
			{
				fclose(pArch);
				retorno = 0;
			}
		}
		else
		{
			puts("El archivo no puede ser cargado o no existe\n");
		}
	}
    return retorno;
}



/** \brief Alta de arcades
 *
 * \param pListaArcades LinkedList* puntero a la lista de direcciones
 * \return int 1 OK / -1 Mal
 *
 */
int controller_addArcade(LinkedList* pListaArcades)
{
	int retorno = -1;
	char nombreSalonAux[128];
	char nacionAux[128];
	char nombreJuegoAux[128];
	int idArcadeAux;
	int tipoAux;
	int fichasAux;
	int jugadoresAux;
	Arcade* thisAux = NULL;


	if(pListaArcades!=NULL)
	{
		thisAux = arcade_new();

		if(	utn_getTextAlfanumerico(nacionAux, 128, "Nacionalidad: ", "ERROR\n")==0 &&
			utn_getNumero(&tipoAux, "1) MONO\n2) ESTEREO\n", "ERROR\n")==0 &&
			utn_getNumero(&jugadoresAux, "Cantidad de jugadores: ", "ERROR\n")==0 &&
			utn_getNumero(&fichasAux, "Maximo de fichas: ", "ERROR\n")==0 &&
			utn_getTextAlfanumerico(nombreSalonAux, 128, "Salon: ", "ERROR\n")==0 &&
			utn_getTextAlfanumerico(nombreJuegoAux, 128, "Juego: ", "ERROR\n")==0)
		{
			idArcadeAux = arcade_generadorID(pListaArcades)+1;

			arcade_setNac(thisAux, nacionAux);
			arcade_setTipo(thisAux, tipoAux);
			arcade_setJugadores(thisAux, jugadoresAux);
			arcade_setFichas(thisAux, fichasAux);
			arcade_setNombreSalon(thisAux, nombreSalonAux);
			arcade_setNombreJuego(thisAux, nombreJuegoAux);
			arcade_setIdArcade(thisAux, idArcadeAux);

			if(ll_add(pListaArcades, thisAux)==0)
			{
				printf("ID: %d\n",idArcadeAux);
				puts("Arcade ingresado correctamente\n");
			}

			retorno = 0;
		}
	}

    return retorno;


}

/** \brief Modificar datos del arcade
 *
 * \param pListaArcades LinkedList* puntero a la lista de direcciones
 * \return int 1 OK / -1 Mal
 *
 */
int controller_editArcade(LinkedList* pListaArcades)
{
	int i;
	int idAux;
	int idAuxBuscado;
	char nombreJuegoAux[128];
	char nombreSalonAux[128];
	char nacionAux[128];
	int tipoAux;
	int opcionAux;
	int fichasAux;
	int jugadoresAux;
	int retorno = -1;
	int flagExiste = 0;
	Arcade* aux;

	if(pListaArcades!=NULL)
	{
		if(utn_getNumero(&idAuxBuscado, "ID a editar: ", "Err. edit")==0)
		{
			for(i=0;i<ll_len(pListaArcades);i++)
			{
				aux = ll_get(pListaArcades, i);

				arcade_getIdArcade(aux, &idAux);

				if(idAux == idAuxBuscado)
				{
					flagExiste = 1;

					arcade_getFichas(aux, &fichasAux);
					arcade_getJugadores(aux, &jugadoresAux);
					arcade_getNac(aux, nacionAux);
					arcade_getNombreJuego(aux, nombreJuegoAux);
					arcade_getNombreSalon(aux, nombreSalonAux);
					arcade_getTipo(aux, &tipoAux);

					printf(	"\nID: %d\n"
							"Nacionalidad: %s\n"
							"Tipo de sonido: %d\n"
							"Cantidad de jugadores: %d\n"
							"Maxima cantidad de fichas: %d\n"
							"Nombre del salon: %s\n"
							"Nombre del juego: %s\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,nombreSalonAux,nombreJuegoAux);
					break;
				}
			}
		}

		if(flagExiste==1)
		{
			do
			{
				if(utn_getNumero(&opcionAux,"\nDato a modificar:\n"
											"1) Cantidad de jugadores\n"
											"2) Juego\n"
											"3) Cancelar\n", "ERROR\n")==0)
				{
					switch(opcionAux)
					{
						case 1:
							utn_getNumero(&jugadoresAux, "Agregue nueva cantidad de jugadores: ", "ERROR\n");
							arcade_setJugadores(aux, jugadoresAux);
							puts("\nDatos modificados correctamente\n");
							break;

						case 2:
							puts("\nIMPRIMIR LOS JUEGOS\n");
							utn_getTextAlfanumerico(nombreJuegoAux, 128, "Nuevo juego: ", "ERROR\n");
							arcade_setNombreJuego(aux, nombreJuegoAux);
							puts("\nDatos modificados correctamente\n");
							break;

						case 3:
							puts("\nCancelado\n");
							break;
					}
				}
			}while(opcionAux!=1 && opcionAux!=2 && opcionAux!=3);
		retorno = 0;
		}
		else
			puts("\nID inexistente o eliminado\n");

}
    return retorno;
}

/** \brief Baja de arcade
 *
 * \param pListaArcades LinkedList* puntero a la lista de direcciones
 * \return int 1 OK / -1 Mal
 *
 */
int controller_removeArcade(LinkedList* pListaArcades)
{
	int i;
	int idAux;
	int idAuxBuscado;
	char nombreJuegoAux[128];
	char nombreSalonAux[128];
	char nacionAux[128];
	int tipoAux;
	int opcionAux;
	int fichasAux;
	int jugadoresAux;
	int retorno = -1;
	int flagExiste = 0;
	int indexAux;
	Arcade* aux;

	if(pListaArcades!=NULL)
	{
		if(utn_getNumero(&idAuxBuscado, "ID a eliminar: ", "Err")==0)
		{
			for(i=0;i<ll_len(pListaArcades);i++)
			{
				aux = ll_get(pListaArcades, i);

				arcade_getIdArcade(aux, &idAux);

				if(idAuxBuscado == idAux)
				{
					indexAux = i;
					flagExiste = 1;
					arcade_getFichas(aux, &fichasAux);
					arcade_getJugadores(aux, &jugadoresAux);
					arcade_getNac(aux, nacionAux);
					arcade_getNombreJuego(aux, nombreJuegoAux);
					arcade_getNombreSalon(aux, nombreSalonAux);
					arcade_getTipo(aux, &tipoAux);

					printf(	"\nID: %d\n"
							"Nacionalidad: %s\n"
							"Tipo de sonido: %d\n"
							"Cantidad de jugadores: %d\n"
							"Maxima cantidad de fichas: %d\n"
							"Nombre del salon: %s\n"
							"Nombre del juego: %s\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,nombreSalonAux,nombreJuegoAux);
					break;
				}
			}

			if(flagExiste==1)
			{
				do
				{
					if(utn_getNumero(&opcionAux,"\n¿Eliminar?\n"
												"1) Confirma\n"
												"2) Cancela\n", "ERROR\n")==0)
					{
						switch(opcionAux)
						{
						case 1:
							arcade_delete(aux);
							ll_remove(pListaArcades, indexAux);
							retorno = 0;
							puts("Datos eliminados correctamente\n");
							break;

						case 2:
							puts("Cancelado\n");
							break;
						}
					}
					break;
				}while(opcionAux!=1||opcionAux!=2);
			}
			else
				puts("\nID inexistente o eliminado\n");
		}
	}

	return retorno;
}

/** \brief Listar arcades
 *
 * \param pListaArcades LinkedList* puntero a la lista de direcciones
 * \return int 1 OK / -1 Mal
 *
 */
int controller_ListArcade(LinkedList* pListaArcades)
{
	int i;
	int idAux;
	char nombreJuegoAux[128];
	char nombreSalonAux[128];
	char nacionAux[128];
	int tipoAux;
	int fichasAux;
	int jugadoresAux;
	int retorno = -1;
	Arcade* aAux;

	if(pListaArcades!=NULL)
	{
		printf("ID, NACIONALIDAD, TIPO_SONIDO, CANT_JUG, FICHAS_MAX, SALON, JUEGO\n\n");
		for(i=0;i<ll_len(pListaArcades);i++)
		{
			aAux = ll_get(pListaArcades, i);
			arcade_getIdArcade(aAux, &idAux);
			arcade_getFichas(aAux, &fichasAux);
			arcade_getJugadores(aAux, &jugadoresAux);
			arcade_getNac(aAux, nacionAux);
			arcade_getNombreJuego(aAux, nombreJuegoAux);
			arcade_getNombreSalon(aAux, nombreSalonAux);
			arcade_getTipo(aAux, &tipoAux);

			printf(	"%d, %s, %d, %d, %d, %s, %s\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,nombreSalonAux,nombreJuegoAux);

		}
		printf("\n");
		retorno = 0;
	}
    return retorno;
}


/** \brief Ordenar arcades
 *
 * \param pListaArcades LinkedList* puntero a la lista de direcciones
 * \return int 1 OK / -1 Mal
 *
 */
int controller_sortArcade(LinkedList* pListaArcades)
{
	int retorno = -1;
	int opcion;

	if(pListaArcades!=NULL)
	{
		do
		{
			if(utn_getNumero(&opcion, 	"ORDENAR POR:\n"
										"1- Nombre de juego.\n"
										"2- ID arcade.\n"
										"3- Pais.\n", "ERROR.\n")==0 && opcion>=1 && opcion<4)
			{
				switch(opcion)
				{
					case 1:
					{
						//NOTA: OPCION DESC TARDA MUUUUCHO. NO SE SI FUNCIONA
						puts("\nOrdenando...\n");
						ll_sort(pListaArcades, arcade_comparaJuegos, 1);
						puts("Lista ordenada\n");
						retorno = 0;
						break;
					}
					break;

					case 2:
					{
						puts("\nOrdenando...\n");
						ll_sort(pListaArcades, arcade_comparaIdArcade, 1);
						puts("Lista ordenada\n");
						retorno = 0;
						break;
					}
					break;

					case 3:
						puts("\nOrdenando...\n");
						ll_sort(pListaArcades, arcade_comparaPaises, 1);
						puts("Lista ordenada\n");
						retorno = 0;
						break;
				}
				break;
			}
			else
			{
				puts("Opcion invalida\n");
			}
		}while(opcion!=0 || opcion!=1);
	}

    return retorno;
}

/** \brief Guarda los datos de los arcades en el archivo arcades.csv (modo texto).
 *
 * \param path char* nombre del archivo y extension
 * \param pArrayListEmployee LinkedList* puntero a lista de direcciones
 * \return int
 *
 */
int controller_saveAsText(char* path , LinkedList* pListaArcades)
{
	int retorno = -1;
	int i;
	int idAux;
	int fichasAux;
	int jugadoresAux;
	char nacionAux[128];
	char nombreJuegoAux[128];
	char nombreSalonAux[128];
	int tipoAux;
	Arcade* aAux;
	FILE* pArch = fopen(path,"w");

	if(path!=NULL && pArch!=NULL)
	{

		ll_sort(pListaArcades, arcade_comparaIdArcade, 1); //Ordeno los juegos

		fprintf(pArch,"ID,NACIONALIDAD,TIPO_SONIDO,CANT_JUGADORES,FICHAS_MAX,SALON,JUEGO\n");

		for(i=0;i<ll_len(pListaArcades);i++)
		{
			aAux = ll_get(pListaArcades, i);

			arcade_getIdArcade(aAux, &idAux);
			arcade_getFichas(aAux, &fichasAux);
			arcade_getJugadores(aAux, &jugadoresAux);
			arcade_getNac(aAux, nacionAux);
			arcade_getNombreJuego(aAux, nombreJuegoAux);
			arcade_getNombreSalon(aAux, nombreSalonAux);
			arcade_getTipo(aAux, &tipoAux);

			fprintf(pArch,"%d,%s,%d,%d,%d,%s,%s\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,nombreSalonAux,nombreJuegoAux);

		}

		fclose(pArch);
		retorno = 0;
	}

    return retorno;
}

/** \brief Genera un archivo de texto con la lista de juegos existentes
 *
 * \param path char* nombre del archivo y extension que se genera
 * \param pArrayListEmployee LinkedList* puntero a lista de direcciones
 * \return int
 *
 */
int controller_saveGamesText(char* path , LinkedList* pListaArcades)
{
	int retorno = -1;
	int i;
	char nombreAux[128];
	Arcade* aAux;
	Arcade* aAux2;
	FILE* pArch = fopen(path,"w");

	if(path!=NULL && pArch!=NULL)
	{

		ll_sort(pListaArcades, arcade_comparaJuegos, 1); //Ordeno los juegos


		fprintf(pArch,"LISTA DE JUEGOS\n");

		for(i=0;i<ll_len(pListaArcades)-1;i++)
		{
			aAux = ll_get(pListaArcades, i);
			aAux2 = ll_get(pListaArcades, i+1);
			if(strcmp(aAux->nombreJuego,aAux2->nombreJuego)!=0)
			{
				arcade_getNombreJuego(aAux, nombreAux);
				fprintf(pArch,"%s\n",nombreAux);
			}
		}
    	puts("archivo generado");
		fclose(pArch);
		retorno = 0;
	}

    return retorno;
}

/** \brief Genera un archivo con la lista de juegos multiplayer
 *
 * \param path char* nombre del archivo y extension que se genera
 * \param pArrayListEmployee LinkedList* puntero a lista de direcciones
 * \return int
 *
 */

int controller_saveMultiplayer(char* path , LinkedList* pListaArcades)
{
	int retorno = -1;
	int i;
	char nombreJuegoAux[128];
	char nombreSalonAux[128];
	int tipoAux;
	int jugadoresAux;
	int idAux;
	int fichasAux;
	char nacionAux[128];
	Arcade* aAux;
	FILE* pArch = fopen(path,"w");
	LinkedList* lAux;

	if(path!=NULL && pArch!=NULL)
	{

		ll_sort(pListaArcades, arcade_comparaJuegos, 1);
		lAux = ll_filter(pListaArcades, arcade_multiPLayer);

		fprintf(pArch,"ID,NACIONALIDAD,TIPO_SONIDO,CANT_JUGADORES,FICHAS_MAX,SALON,JUEGO\n");

		for(i=0;i<ll_len(lAux);i++)
		{
			aAux = ll_get(lAux, i);

			arcade_getIdArcade(aAux, &idAux);
			arcade_getFichas(aAux, &fichasAux);
			arcade_getJugadores(aAux, &jugadoresAux);
			arcade_getNac(aAux, nacionAux);
			arcade_getNombreJuego(aAux, nombreJuegoAux);
			arcade_getNombreSalon(aAux, nombreSalonAux);
			arcade_getTipo(aAux, &tipoAux);

			fprintf(pArch,"%d,%s,%d,%d,%d,%s,%s\n",idAux,nacionAux,tipoAux,jugadoresAux,fichasAux,nombreSalonAux,nombreJuegoAux);

		}
		puts("Archivo generado");
		fclose(pArch);
		retorno = 0;
	}

    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 *//*
int controller_saveAsBinary(char* path , LinkedList* pListaArcades)
{
	int retorno = -1;
	int i;
	Employee* aux;
	FILE* pArch = fopen(path,"wb");

	if(path!=NULL && pArch!=NULL)
	{
		for(i=0;i<ll_len(pListaArcades);i++)
		{
			aux = ll_get(pListaArcades, i);

			fwrite(&aux,sizeof(Employee),1,pArch);
		}

		fclose(pArch);
		retorno = 0;
	}

	return retorno;
}*/

/** \brief Muestra el menu de opciones del inicio
 *
 * \param int* opcion devuelve por referencia la opcion indicada
 * \return void
 *
 */

void controller_menu(int* opcion)
{
	utn_getNumero(opcion,"/****************************************************\n"
						 "Menu:\n"
						 "1. Leer arcades desde archivo arcades.csv\n"
						 "2. Incorporar arcade\n"
						 "3. Modificar arcade\n"
						 "4. Eliminar arcade\n"
						 "5. Imprimir arcades\n"
						 "6. Generar archivo txt con juegos\n"
						 "7. Generar un archivo con arcades multijugador\n"
						 "8. Actualizar cantidad de fichas\n"
						 "9. Salir\n"
						 "*****************************************************/\n", "ERROR\n");

}

/** \brief Aumenta la cantidad de fichas
 *
 * \param pArrayListEmployee LinkedList* puntero a lista de direcciones
 *
 * \return int 0 OK / -1 Mal
 *
 */

int controller_aumentarFichas(LinkedList* this)
{
	int retorno = -1;

	if(this!=NULL)
	{
		if(ll_map(this, arcade_aumentaFichas)==0)
		{
			retorno = 0;
			puts("La cantidad de fichas se duplico\n");
		}
	}
	return retorno;
}


