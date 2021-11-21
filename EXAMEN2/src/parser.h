/*
 * parser.h
 *
 *  Created on: 21 nov. 2021
 *      Author: maxis
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_ArcadeFromText(FILE* pFile , LinkedList* pListaArcades);
int parser_ArcadeFromBinary(FILE* pFile , LinkedList* pListaArcades);

#endif /* PARSER_H_ */
