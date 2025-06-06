#include <stdio.h>
#include <stdlib.h>
#include "column.h"

#include <string.h>


COLUMN * createColumn(char * title) {
    COLUMN * col = (COLUMN *) malloc(sizeof(COLUMN));
    if (col == NULL) return NULL;
    col->title = (char *) malloc(strlen(title) + 1);
    strcpy(col->title, title);
    col->values = NULL;
    col->max_size = 0;
    col->size = 0;
    return col;
}

int insert_value(COLUMN * col, int value) {
    if (col==NULL) return 0;
    if (col->max_size == 0) {
        col->values = (int *) malloc(sizeof(int) * REALLOC_SIZE);
        if (col->values == NULL) return 0;
        col->max_size = REALLOC_SIZE;
    }
    else if (col->size >= col->max_size) {
        int * temp = realloc(col->values, sizeof(int) * (col->max_size + REALLOC_SIZE));
        if (temp == NULL) return 0;
        col->values = temp;
        col->max_size += REALLOC_SIZE;
    }
    col->values[col->size++] = value;
    return 1;
}

void delete_column(COLUMN * col) {
    if (col == NULL) return;
    free(col->title);
    free(col->values);
    free(col);
}

void print_column(COLUMN * col) {
    if (col== NULL) return;
    printf("Colonne: %s \n", col->title);
    for (int i = 0; i < col->size; i++) {
        printf("[%d] %d \n", i, col->values[i]);
    }
}