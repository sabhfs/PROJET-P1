#include <stdio.h>
#include <stdlib.h>
#include "dataframe.h"
#include "column.h"
#include "column 2.0.h"
#include "sort.h"

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

        case 4: {
            Column col;
            col.size = 5;
            col.column_type = INT;
            col.data = malloc(sizeof(void*) * col.size);
            Column_Type *v0 = malloc(sizeof(int)); *v0 = (Column_Type)42;
            Column_Type *v1 = malloc(sizeof(int)); *v1 = (Column_Type)5;
            Column_Type *v2 = malloc(sizeof(int)); *v2 = (Column_Type)17;
            Column_Type *v3 = malloc(sizeof(int)); *v3 = (Column_Type)23;
            Column_Type *v4 = malloc(sizeof(int)); *v4 = (Column_Type)5;
            col.data[0] = v0;
            col.data[1] = v1;
            col.data[2] = v2;
            col.data[3] = v3;
            col.data[4] = v4;

            printf("--- Avant tri ---\n");
            for (unsigned int i = 0; i < col.size; i++) {
                printf("[%d] %d\n", i, *((int*)col.data[i]));
            }

            printf("\n--- Tri croissant ---\n");
            sort(&col, ASC);
            print_col_sorted(&col, ASC);
            erase_index(&col);

            printf("\n--- Tri décroissant ---\n");
            sort(&col, DESC);
            print_col_sorted(&col, DESC);
            erase_index(&col);

            printf("\nCheck index = %d\n", check_index(&col));
            erase_index(&col);
            printf("Index effacé.\n");
            for (unsigned int i = 0; i < col.size; i++) {
                free(col.data[i]);
            }

            int value_to_find = 17;
            int found = search_value_in_column(&col, &value_to_find);
            printf("\nRecherche de %d : %s\n", value_to_find, found == 1 ? "trouvée" : "non trouvée");

            free(col.data);
            break;
        }

        default: {
            printf("Erreur\n");
        }
    }

    return 0;
}
