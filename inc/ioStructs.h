#ifndef IO_STRUCTS_H
#define IO_STRUCTS_H

typedef struct {
    int** matrix;
    int size;
    char path[2];
} InputData;

typedef struct {
    char* answer;
} OutputData;

#endif