#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataframe.h"
#include "column.h"

// test colonne
int main() {
    COLUMN * col = createColumn("Age");
    insert_value(col, 25);
    insert_value(col, 18);
    insert_value(col, 19);

    print_column(col);

    delete_column(col);

    Dataframe * df = createDataframe();
    COLUMN * col1 = createColumn("Age");
    COLUMN * col2 = createColumn("Score");

    addColumn(df, col1);
    addColumn(df, col2);

    int row1[] = {20, 88};
    int row2[] = {25, 75};
    int row3[] = {30, 90};

    addRow(df, row1);
    addRow(df, row2);
    addRow(df, row3);

    printDataframe(df);
    deleteDataframe(df);

    return 0;
}