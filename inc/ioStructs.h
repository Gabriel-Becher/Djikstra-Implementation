#ifndef IO_STRUCTS_H
#define IO_STRUCTS_H

typedef struct {
    int** matrix;
    int size;
    char* path;
} InputData;

typedef struct {
    char* path;
    int length;
    int cost;
} OutputData;

#endif