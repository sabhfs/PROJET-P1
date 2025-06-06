#ifndef DATAFRAME_H
#define DATAFRAME_H

#include "column.h"

typedef struct {
    COLUMN ** columns;
    int column_count;
    int row_count;
} Dataframe;

Dataframe * createDataframe();
void addColumn(Dataframe * df, COLUMN * col);
void printDataframe(Dataframe * df);
void addRow(Dataframe * df, int * value);
void deleteDataframe(Dataframe * df);

#endif //DATAFRAME_H
