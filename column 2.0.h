#ifndef COLUMN_2_0_H
#define COLUMN_2_0_H


typedef enum {
    NULLVAL = 1, UINT, INT, USHORT, SHORT, ULONG,
    LONG, UCHAR, CHAR, FLOAT, DOUBLE, STRING, OBJECT
} Enum_Type;


typedef union {
    unsigned int uint_value;
    signed int int_value;
    unsigned short ushort_value;
    signed short short_value;
    unsigned long long int ulong_int;
    signed long long int long_int;
    unsigned char uchar_value;
    signed char char_value;
    float float_value;
    double double_value;
    char * string_value;
    void * object_value;
} Column_Type;


typedef struct {
    char * column_name;
    unsigned int size;
    unsigned int max_size;
    Enum_Type column_type;
    Column_Type ** data;
    unsigned long long int * index;
    char valid_index;
    unsigned int index_size;
    char sort_dir;
} Column;

Column * create_column(Enum_Type type);
int insert_value(Column * col, void * value);
void delete_column(Column *col);
void print_value(Column * col, unsigned long long int i, char * str, int size);
void print_column(const Column *col);
void info_column(Column * col);

#endif