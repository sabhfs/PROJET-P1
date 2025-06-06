#include <stdio.h>
#include <stdlib.h>
#include "dataframe.h"

Dataframe * createDataframe() {
    Dataframe * df = (Dataframe *)malloc(sizeof(Dataframe));
    df->columns = NULL;
    df->column_count = 0;
    df->row_count = 0;
    return df;
}

void addColumn(Dataframe * df, COLUMN * col) {
    df->columns = realloc(df->columns, sizeof(COLUMN) * (df->column_count + 1));
    df->columns[df->column_count] = col;
    df->column_count++;
}

void addRow(Dataframe * df, int * value) {
    for (int i = 0; i < df->column_count; i++) {
        insert_value(df->columns[i], value[i]);
    }
    df->row_count++;
}

void printDataframe(Dataframe * df) {
    for (int i = 0; i < df->column_count; i++) {
        printf("%s \t", df->columns[i]->title);
    }
    printf("\n");

    for (int row = 0; row < df->row_count; row++) {
        for (int col=0; col < df->column_count; col++) {
            printf("%d    \t", df->columns[col]->values[row]);
        }
        printf("\n");
    }
}

void deleteDataframe(Dataframe * df) {
    if (df == NULL) return;
     if (df-> columns != NULL && df-> row_count > 0) {
         for (int i = 0; i < df->column_count; i++) {
             if (df-> columns[i]) delete_column(df->columns[i]);
         }
         free(df->columns);
     }
    free(df);
}