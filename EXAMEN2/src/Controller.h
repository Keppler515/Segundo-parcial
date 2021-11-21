/*
 * Controller.h
 *
 *  Created on: 21 nov. 2021
 *      Author: maxis
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_


int controller_loadFile(char* path , LinkedList* pListaArcades);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addArcade(LinkedList* pListaArcades);
int controller_editArcade(LinkedList* pListaArcades);
int controller_removeArcade(LinkedList* pListaArcades);
int controller_ListArcade(LinkedList* pListaArcades);
int controller_sortArcade(LinkedList* pListaArcades);
int controller_saveAsText(char* path , LinkedList* pListaArcades);
int controller_saveAsBinary(char* path , LinkedList* pListaArcades);
void controller_menu(int* opcion);
int controller_saveGamesText(char* path , LinkedList* pListaArcades);
int controller_saveMultiplayer(char* path , LinkedList* pListaArcades);
int controller_aumentarFichas(LinkedList* this);


#endif /* CONTROLLER_H_ */
