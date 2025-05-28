#include <stdio.h>
#include <stdlib.h>
#include "dataframe.h"
#include "column.h"

CDataframe * createDataframe();
void addColumn(Cdataframe * df, COLUMN * col);
void printDataframe(Cdataframe * df);
void addRow(Cdataframe * df, int * value);