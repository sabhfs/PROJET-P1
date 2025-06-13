#include <stdio.h>
#include "dataframe.h"
#include "column.h"
#include "column 2.0.h"


int main() {
    int exo;
    exo = 0;
    printf("Quelle fonction voulez-vous tester ? \n");
    scanf("%d", &exo);

    switch (exo) {

        // test column
        case 1: {
            COLUMN * col = createColumn("Age");
            insertValue(col, 25);
            insertValue(col, 18);
            insertValue(col, 19);

            printColumn(col);

            deleteColumn(col);
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
        case 3: {
            // Création d'une colonne de type INT
            Column *col = create_column(INT);
            if (!col) {
                printf("Erreur lors de la creation de la colonne.\n");
                return 1;
            }

            // Insertion de valeurs
            int a = 10, b = 20, c = 30;
            insert_value(col, &a);
            insert_value(col, NULL); // valeur NULL
            insert_value(col, &b);
            insert_value(col, &c);

            // Affichage des valeurs avec print_col (5.5)
            printf("Affichage de la colonne :\n");
            print_column(col);

            // Affichage d'une seule valeur avec print_value (5.4)
            char buffer[50];
            print_value(col, 2, buffer, sizeof(buffer));
            printf("\nValeur a l'index 2 : %s\n", buffer);

            // Informations sur la colonne (5.6)
            printf("\nInformations sur la colonne :\n");
            info_column(col);

            // Suppression de la colonne (5.3)
            delete_column(col);

            break;
        }

        default: {
            printf("Erreur\n");
        }
    }

    return 0;
}
