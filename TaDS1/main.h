#ifndef MAIN_H
#define MAIN_H



int input_float(int *m_m, int *size, int *sign, int *exponent);
void normalize_float(int *arr, int size, int dot, int *exponent);

int input_int(int *m_i, int *size, int *sign, int *exponent);
void normalize(int *arr, int size, int dot, int *exponent);
void rounding(int *arr, int size, int last_digit);
void clean(int *array, int size);

void check_ten(int *arr_float, int *arr_int, int size);
int scan_numbers(int *massiv, int *sign);
void print_array(const int *array, int size);
void move_digits(int *arr_, int size, int poryadok);
int comparison(int *a, int *b, int size);
void subtract(int *a, int *b, int size);
void division(int *arr_float, int *arr_int, int *result, int size, int *exp);

#endif // MAIN_H
