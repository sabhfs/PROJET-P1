#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "column.h"

typedef struct {
    COLUMN ** colums;
    int column_count;
    int row_count;
} Dataframe;

Dataframe * createDataframe();
void addColumn(Dataframe * df, COLUMN * col);
void printDataframe(Dataframe * df);
void addRow(Dataframe * df, int * value);

#endif //DATAFRAME_H
