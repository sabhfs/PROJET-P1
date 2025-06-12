#include <stdio.h>

#include "dataframe.h"
#include "column.h"


int main() {
    int exo;
    exo = 0;
    printf("Quelle fonction voulez-vous tester ? \n");
    scanf("%d", &exo);

    switch (exo) {

        // test column
        case 1: {
            COLUMN * col = createColumn("Age");
            insert_value(col, 25);
            insert_value(col, 18);
            insert_value(col, 19);

            print_column(col);

            delete_column(col);
            break;
        }

        // test dataframe
        case 2: {
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
            break;
        }

        default: {
            printf("Erreur\n");
        }
    }

    return 0;
}
