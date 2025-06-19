#ifndef SORT_H
#define SORT_H

#include "column 2.0.h"

#define ASC 0
#define DESC 1

int compare_column_values(Column *col, unsigned long long i, unsigned long long j, int sort_dir);
void swap(int *a, int *b);
int partition(Column *col, int *index, int left, int right, int sort_dir);
void quicksort_index(Column *col, int *index, int left, int right, int sort_dir);
void sort(Column *col, int sort_dir);
void print_col_sorted(Column *col, int sort_dir);
void erase_index(Column *col);
int check_index(Column * col);
void update_index(Column * col);
int search_value_in_column(Column * col, void * value);

#endif //SORT_H
