#ifndef MAIN_H
#define MAIN_H



int input_float(int *m_m, int *size, int *sign, int *exponent);
int input_int(int *m_i, int *size, int *sign, int *exponent);
void normalize_int(int *arr, int *size);
void normalize_float(int *arr, int *size, int dot, int *exponent);

void output_res(int *arr, int size, int exp, int sign);

int count_zero(int *arr, int size);
void move_digits(int *arr_, int size, int poryadok);
void check_ten(int *arr_float, int *arr_int, int size, int *exp);

int comparison(int *a, int *b, int size);
void subtract(int *a, int *b, int size);
void division(int *arr_float, int *arr_int, int *result, int size, int *exp);
void rounding(int *arr, int size, int last_digit);


void clean(int *array, int size);
int zero_array(int *array, int size);
void print_array(const int *array, int size);

#endif // MAIN_H
