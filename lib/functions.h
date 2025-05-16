/**
 * @file functions.h
 * @author a24869
 * @brief Ficheiro para chamar as funções
 * 
 * @date 2025-03-22
 * 
 * 
 */
#ifndef functions_h
#define functions_h

#include "structs.h"
#include <stdbool.h>

void freeAntennaList(Antenna* head);

Antenna* insertAntenna(Antenna* head, int x, int y, char freq);

Antenna* deleteAntenna(Antenna* head, int x, int y, char frequency);

Antenna* applyNefastoEffect(Antenna* head);

void showAntennaList(Antenna* head);

Antenna* readAntennaMatrixFile(const char* filename);

bool writeAntennaBinary(char* filename, Antenna* head);

Antenna* readAntennaBinary(char* filename);

#endif