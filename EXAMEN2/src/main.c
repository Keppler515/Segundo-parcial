/*
 ============================================================================
 Name        : EXAMEN2.c
 Author      : Maximiliano Sosa
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

/****************************************************
    Menu:
     1. Leer arcades desde archivo arcades.csv (SI POR DEFECTO)
     2. Incorporar arcade
     3. Modificar arcade
     4. Eliminar arcade
     5. Imprimir arcades
     6. Generar archivo txt con juegos
     7. Generar un archivo con arcades multijugador
     8. Actualizar cantidad de fichas
     9. Salir
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "Controller.h"
#include "Arcade.h"
#include "parser.h"
#include "utn_biblioteca.h"

#define	MONO	1;
#define	ESTEREO	2;

int main()
{
	setbuf(stdout,NULL);

	    int option;

	    LinkedList* pListaArcades = ll_newLinkedList();

	    if(controller_loadFile("arcades.csv", pListaArcades)==0)
	    	puts("ARCHIVO OK");

	    do{

	    	controller_menu(&option);
	    	printf("\n");

	        switch(option)
	        {
	        case 2:
	        	if(controller_addArcade(pListaArcades)==0)
	        		controller_saveAsText("arcades.csv", pListaArcades);
	        	break;

	        case 3:
	        	if(controller_ListArcade(pListaArcades)==0)
	          		if(controller_editArcade(pListaArcades)==0)
	        			controller_saveAsText("arcades.csv", pListaArcades);
	        	break;

	        case 4:
	        	if(controller_ListArcade(pListaArcades)==0)
					if(controller_removeArcade(pListaArcades)==0)
						controller_saveAsText("arcades.csv", pListaArcades);
	        	break;

	        case 5:
	        	if(controller_sortArcade(pListaArcades)==0)
	        		controller_ListArcade(pListaArcades);
	        	break;

	        case 6:
	        	controller_saveGamesText("lista_juegos.txt", pListaArcades);
	        	break;

	        case 7:
	        	controller_saveMultiplayer("lista_multiplayer.csv", pListaArcades);
	        	break;

	        case 8:
	        	controller_aumentarFichas(pListaArcades);
	        	break;
	        }
	    }while(option != 9);


	    puts("Terminado");

	    return 0;

}



