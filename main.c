/**
 * @file main.c
 * @author a24869
 * @brief Ficheiro principal para a gestão e manipulação de antenas.
 * 
 * Este programa lida com a inserção, remoção e manipulação de antenas, aplicando efeitos 
 * e armazenando os resultados num ficheiro. O código foi desenvolvido para gerir antenas
 * através de uma lista ligada e manipular as suas coordenadas numa matriz.
 * 
 * As funções principais do programa incluem:
 * - Ler o ficheiro.txt que contém a matriz com as antenas.
 * - Inserir antenas em posições específicas.
 * - Remover antenas específicas.
 * - Mostrar a lista ligada
 * - Aplicar um efeito nefasto sobre as antenas.
 * - Guardar e ler a lista ligada em formato binário
 * 
 * @date 2025-03-22
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lib/functions.h"

int main() { 
    Antenna* head = NULL;

    head = readAntennaMatrixFile("antennasFile.txt");
    if (head == NULL) {
        printf("Antenna list is empty after reading from text file.\n");
    }

    head = insertAntenna(head, 3, 4, 'A');
    head = insertAntenna(head, 15, 5, 'C');
    head = deleteAntenna(head, 15, 5, 'C');
    
    showAntennaList(head);
    head = applyNefastoEffect(head);

    if (writeAntennaBinary("antennas.bin", head)) {
        printf("Antenna list successfully saved to antennas.bin\n");
    } else {
        printf("Error saving antenna list to binary file.\n");
    }

    freeAntennaList(head);
    head = NULL;

    head = readAntennaBinary("antennas.bin");
    if (head == NULL) {
        printf("Error reading antenna list from binary file.\n");
    } else {
        printf("Antenna list successfully loaded from binary file.\n");
        showAntennaList(head);
    }

    freeAntennaList(head);
    return 0;
}

