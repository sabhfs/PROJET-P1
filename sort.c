#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int compare_column_values(Column *col, unsigned long long i, unsigned long long j, int sort_dir) {
    if (!col || !col->data || !col->data[i] || !col->data[j]) return 0;
    int cmp = 0;
    switch (col->column_type) {
        case INT:
            cmp = *((int*)col->data[i]) - *((int*)col->data[j]);
            break;
        case UINT:
            cmp = *((unsigned int*)col->data[i]) > *((unsigned int*)col->data[j]) ? 1 : *((unsigned int*)col->data[i]) < *((unsigned int*)col->data[j]) ? -1 : 0;
            break;
        case CHAR:
            cmp = *((char*)col->data[i]) - *((char*)col->data[j]);
            break;
        case UCHAR:
            cmp = *((unsigned char*)col->data[i]) > *((unsigned char*)col->data[j]) ? 1 : *((unsigned char*)col->data[i]) < *((unsigned char*)col->data[j]) ? -1 : 0;
            break;
        case SHORT:
            cmp = *((short*)col->data[i]) - *((short*)col->data[j]);
            break;
        case USHORT:
            cmp = *((unsigned short*)col->data[i]) > *((unsigned short*)col->data[j]) ? 1 : *((unsigned short*)col->data[i]) < *((unsigned short*)col->data[j]) ? -1 : 0;
            break;
        case LONG:
            cmp = *((long*)col->data[i]) > *((long*)col->data[j]) ? 1 : *((long*)col->data[i]) < *((long*)col->data[j]) ? -1 : 0;
            break;
        case ULONG:
            cmp = *((unsigned long*)col->data[i]) > *((unsigned long*)col->data[j]) ? 1 : *((unsigned long*)col->data[i]) < *((unsigned long*)col->data[j]) ? -1 : 0;
            break;
        case FLOAT: {
            float a = *((float*)col->data[i]);
            float b = *((float*)col->data[j]);
            cmp = (a > b) ? 1 : (a < b) ? -1 : 0;
            break;
        }
        case DOUBLE: {
            double a = *((double*)col->data[i]);
            double b = *((double*)col->data[j]);
            cmp = (a > b) ? 1 : (a < b) ? -1 : 0;
            break;
        }
        case STRING:
            cmp = strcmp((char*)col->data[i], (char*)col->data[j]);
            break;
        default:
            cmp = 0;
            break;
    }
    return (sort_dir == ASC) ? cmp : -cmp;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(Column *col, int *index, int left, int right, int sort_dir) {
    int pivot = index[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        int cmp = compare_column_values(col, index[j], pivot, sort_dir);
        if (cmp <= 0) {
            i++;
            swap(&index[i], &index[j]);
        }
    }
    swap(&index[i + 1], &index[right]);
    return i + 1;
}



void quicksort_index(Column *col, int *index, int left, int right, int sort_dir) {
    if (left < right) {
        int pi = partition(col, index, left, right, sort_dir);
        quicksort_index(col, index, left, pi - 1, sort_dir);
        quicksort_index(col, index, pi + 1, right, sort_dir);
    }
}



void sort(Column *col, int sort_dir) {
    if (!col || col->size == 0) return;
    if (col->index) free(col->index);
    col->index = malloc(sizeof(int) * col->size);
    if (!col->index) return;
    for (unsigned long long i = 0; i < col->size; i++) {
        col->index[i] = i;
        quicksort_index(col, col->index, 0, col->size - 1, sort_dir);
        col->index_size = col->size;
        col->valid_index = 1;
        col->sort_dir = sort_dir;
    }
}


void print_col_sorted(Column *col, int sort_dir) {
    if (!col || !col->index || col->index_size == 0) {
        printf("No index to print.\n");
        return;
    }

    for (int i = 0; i < col->index_size; i++) {
        int idx = (sort_dir == ASC) ? col->index[i] : col->index[col->index_size - 1 - i];
        char buffer[100];
        print_value(col, idx, buffer, sizeof(buffer));
        printf("[%d] %s\n", idx, buffer);
    }
}

void erase_index(Column *col) {
    if (col == NULL) return;
    if (col->index != NULL) {
        free(col->index);
        col->index = NULL;
    }
    col->index_size = 0;
    col->valid_index = 0;
}

int check_index(Column *col) {
    if (col == NULL || col->index == NULL) return -1;
    return col->valid_index ? 1 : 0;
}

void update_index(Column *col) {
    if (col == NULL) return;
    sort(col, col->sort_dir);
}

int search_value_in_column(Column *col, void *value) {
    if (col == NULL || value == NULL) return -1;
    if (col->index == NULL || col->valid_index == 0) return -1;
    int left = 0;
    int right = col->size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        int found = compare_column_values(col, col->index[mid], col->index[mid], ASC);
        int v = *(int*)value;
        switch (col->column_type) {
            case INT:
                found = col->data[col->index[mid]]->int_value - v;
                break;
            case UINT:
                found = (int)(col->data[col->index[mid]]->uint_value - (unsigned int)v);
                break;
            case CHAR:
                found = col->data[col->index[mid]]->char_value - (char)v;
                break;
            case UCHAR:
                found = col->data[col->index[mid]]->uchar_value - (unsigned char)v;
                break;
            case SHORT:
                found = col->data[col->index[mid]]->short_value - (short)v;
                break;
            case USHORT:
                found = col->data[col->index[mid]]->ushort_value - (unsigned short)v;
                break;
            case LONG:
                found = (col->data[col->index[mid]]->long_int > (long)v) - (col->data[col->index[mid]]->long_int < (long)v);
                break;
            case ULONG:
                found = (col->data[col->index[mid]]->ulong_int > (unsigned long)v) - (col->data[col->index[mid]]->ulong_int < (unsigned long)v);
                break;
            case FLOAT:
                found = (col->data[col->index[mid]]->float_value > *(float*)value) - (col->data[col->index[mid]]->float_value < *(float*)value);
                break;
            case DOUBLE:
                found = (col->data[col->index[mid]]->double_value > *(double*)value) - (col->data[col->index[mid]]->double_value < *(double*)value);
                break;
            case STRING:
                found = strcmp(col->data[col->index[mid]]->string_value, (char*)value);
                break;
            default:
                return -1;
        }
        if (found == 0) return 1;
        else if (found < 0) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}