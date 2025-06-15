#include <stdio.h>
#include <stdlib.h>
#include "column 2.0.h"
#include <string.h>

Column * create_column(Enum_Type type) {
    Column *col = malloc(sizeof(Column));
    if (!col) return NULL;

    col->column_name = NULL;
    col->size = 0;
    col->max_size = 0;
    col->column_type = type;
    col->data = NULL;

    col->index = NULL;
    col->index_size = 0;
    col->valid_index = 0;
    col->sort_dir = 0;
    return col;
}

int insert_value(Column *col, void *value) {
    if (!col) return 0;

    if (col->max_size == 0) {
        col->max_size = 10;
        col->data = malloc(sizeof(Column_Type*) * col->max_size);
        if (!col->data) return 0;
    } else if (col->size >= col->max_size) {
        unsigned int new_size = col->max_size * 2;
        Column_Type **tmp = realloc(col->data, sizeof(Column_Type*) * new_size);
        if (!tmp) return 0;
        col->data = tmp;
        col->max_size = new_size;
    }

    if (value == NULL) {
        col->data[col->size] = NULL;
        col->size++;
        return 1;
    }

    col->data[col->size] = malloc(sizeof(Column_Type));
    if (!col->data[col->size]) return 0;

    switch (col->column_type) {
        case INT:
            *((int*)&(col->data[col->size]->int_value)) = *((int*)value);
            break;
        case UINT:
            *((unsigned int*)&(col->data[col->size]->uint_value)) = *((unsigned int*)value);
            break;
        case CHAR:
            *((char*)&(col->data[col->size]->char_value)) = *((char*)value);
            break;
        case UCHAR:
            *((unsigned char*)&(col->data[col->size]->uchar_value)) = *((unsigned char*)value);
            break;
        case SHORT:
            *((short*)&(col->data[col->size]->short_value)) = *((short*)value);
            break;
        case USHORT:
            *((unsigned short*)&(col->data[col->size]->ushort_value)) = *((unsigned short*)value);
            break;
        case LONG:
            *((long long int*)&(col->data[col->size]->long_int)) = *((long long int*)value);
            break;
        case ULONG:
            *((unsigned long long int*)&(col->data[col->size]->ulong_int)) = *((unsigned long long int*)value);
            break;
        case FLOAT:
            *((float*)&(col->data[col->size]->float_value)) = *((float*)value);
            break;
        case DOUBLE:
            *((double*)&(col->data[col->size]->double_value)) = *((double*)value);
            break;
        case STRING: {
            char *str_src = (char*)value;
            col->data[col->size]->string_value = malloc(strlen(str_src) + 1);
            if (!col->data[col->size]->string_value) return 0;
            strcpy(col->data[col->size]->string_value, str_src);
            break;
        }
        case OBJECT:
            col->data[col->size]->object_value = value;
            break;
        default:
            free(col->data[col->size]);
            return 0;
    }

    col->size++;
    return 1;
}

void delete_column(Column *col) {
    if (!col) return;

    if (col->data) {
        for (unsigned int i = 0; i < col->size; i++) {
            if (col->data[i]) {
                if (col->column_type == STRING && col->data[i]->string_value) {
                    free(col->data[i]->string_value);
                }
                free(col->data[i]);
            }
        }
        free(col->data);
    }

    if (col->column_name) free(col->column_name);
    if (col->index) free(col->index);

    free(col);
}

void print_value(Column* col, unsigned long long int i, char* str, int size) {
    if (!col || !str || i >= col->size || !col->data || !col->data[i]) {
        snprintf(str, size, "NULL");
        return;
    }

    switch (col->column_type) {
        case INT:
            snprintf(str, size, "%d", col->data[i]->int_value);
            break;
        case UINT:
            snprintf(str, size, "%u", col->data[i]->uint_value);
            break;
        case CHAR:
            snprintf(str, size, "%c", col->data[i]->char_value);
            break;
        case UCHAR:
            snprintf(str, size, "%c", col->data[i]->uchar_value);
            break;
        case SHORT:
            snprintf(str, size, "%hd", col->data[i]->short_value);
            break;
        case USHORT:
            snprintf(str, size, "%hu", col->data[i]->ushort_value);
            break;
        case LONG:
            snprintf(str, size, "%lld", col->data[i]->long_int);
            break;
        case ULONG:
            snprintf(str, size, "%llu", col->data[i]->ulong_int);
            break;
        case FLOAT:
            snprintf(str, size, "%f", col->data[i]->float_value);
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", col->data[i]->double_value);
            break;
        case STRING:
            snprintf(str, size, "%s", col->data[i]->string_value);
            break;
        case OBJECT:
            snprintf(str, size, "<object>");
            break;
        default:
            snprintf(str, size, "?");
            break;
    }
}

void print_column(const Column *col) {
    if (!col) return;

    char buffer[100];
    for (unsigned int i = 0; i < col->size; i++) {
        print_value(col, i, buffer, sizeof(buffer));
        printf("[%u] %s\n", i, buffer);
    }
}

void info_column(Column *col) {
    if (!col) return;
    int null_count = 0;
    for (unsigned int i = 0; i < col->size; i++) {
        if (!col->data || col->data[i] == NULL) {
            null_count++;
        }
    }
    const char* type_names[] = {
        "", "UINT", "INT", "USHORT", "SHORT", "ULONG", "LONG",
        "UCHAR", "CHAR", "FLOAT", "DOUBLE", "STRING", "OBJECT"
    };
    printf("Type : %s\n", type_names[col->column_type]);
    printf("Taille : %u\n", col->size);
    printf("Nulls : %d\n", null_count);
}
