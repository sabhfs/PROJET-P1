#ifndef COLUMN_H
#define COLUMN_H

typedef struct {
    char * title;
    int max_size;
    int size;
    int * values;
} COLUMN;

COLUMN * createColumn(char * title);
int insert_value(COLUMN * col, int value);
void delete_column(COLUMN * col);
void pint_column(COLUMN * col);

#endif //COLUMN_H
