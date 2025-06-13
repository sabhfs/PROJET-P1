#include <stdio.h>
#include <stdlib.h>
#include "column.h"
#include <string.h>


COLUMN * createColumn(const char * title) {
    COLUMN* col = malloc(sizeof(COLUMN));
    if (col == NULL) return NULL;

    col->title = malloc(strlen(title) + 1);
    if (col->title == NULL) return NULL;
    strcpy(col->title, title);

    col->values = malloc(sizeof(int) * REALLOC_SIZE);
    if (col->values == NULL) {
        free(col->title);
        free(col);
        return NULL;
    }

    col->max_size = REALLOC_SIZE;
    col->size = 0;

    return col;
}

int insertValue(COLUMN * col, int value) {
    if (col==NULL) return 0;
    if (col->size >= col->max_size) {
        int new_max_size = col->max_size + REALLOC_SIZE;
        int* temp = realloc(col->values, sizeof(int) * new_max_size);
        if (temp == 0) return 0;

        col->values = temp;
        col->max_size = new_max_size;
    }

    col->values[col->size++] = value;
    return 1;
}

void deleteColumn(COLUMN * col) {
    if (col == NULL) return;
    free(col->title);
    free(col->values);
    free(col);
}

void printColumn(const COLUMN * col) {
    printf("Colonne: %s \n", col->title);
    for (int i = 0; i < col->size; i++) {
        printf("[%d] %d \n", i, col->values[i]);
    }
}