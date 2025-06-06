#ifndef COLUMN_H
#define COLUMN_H

#define REALLOC_SIZE 256

typedef struct {
    char * title;
    int max_size;
    int size;
    int * values;
} COLUMN;

COLUMN * createColumn(char * title);
int insert_value(COLUMN * col, int value);
void delete_column(COLUMN * col);
void print_column(COLUMN * col);

#endif //COLUMN_H
