#ifndef COLUMN_H
#define COLUMN_H

#define REALLOC_SIZE 256

typedef struct {
    char * title;
    int max_size;
    int size;
    int * values;
} COLUMN;

COLUMN * createColumn(const char * title);
int insertValue(COLUMN * col, int value);
void deleteColumn(COLUMN * col);
void printColumn(const COLUMN * col);

#endif
