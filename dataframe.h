#ifndef DATAFRAME_H
#define DATAFRAME_H

typedef struct {
    COLUMN ** colums;
    int column_count;
    int row_count;
} Cdataframe;

CDataframe * createDataframe();
void addColumn(Cdataframe * df, COLUMN * col);
void printDataframe(Cdataframe * df);
void addRow(Cdataframe * df, )
void addRow(Cdataframe * df, int * value);

#endif //DATAFRAME_H
