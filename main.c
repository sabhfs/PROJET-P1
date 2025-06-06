#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dataframe.h"
#include "column.h"

int main() {
    COLUMN * col = createColumn("Age");
    insert_value(col, 25);
    insert_value(col, 18);
    insert_value(col, 19);

    print_column(col);

    delete_column(col);
    return 0;
}