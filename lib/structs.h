/**
 * @file functions.h
 * @author a24869
 * @brief Ficheiro para chamar as structs 
 * 
 * @date 2025-03-22
 * 
 * 
 */

#ifndef structs_h
#define structs_h

typedef struct Antenna{
    int x, y;
    char frequency;
    struct Antenna* link;
}Antenna;

typedef struct AntennaFile {
    int x, y;
    char frequency;
} AntennaFile;

#endif