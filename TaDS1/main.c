#include <stdio.h>

#define N 30
#define N_TEMP 50

int scan_numbers(int *massiv, int *sign);
void print_array(const int *array, int size);
// функция сложения массивов
// функция деления чила на число, возвращающая массив


void division(int a, int b)
{
    ;
}

int main()
{
    int m_int[N], m_mantissa[N], m_exponent[5];// = {0,};
    int sign_int, sign_mantissa, sign_exponent = 0;
    int size_int, size_mantissa, size_exponent;

    printf("Input integer:\n");
    size_int = scan_numbers(m_int, &sign_int);
    printf("Input mantissa:\n");
    size_mantissa = scan_numbers(m_mantissa, &sign_mantissa);
    printf("Input exponent:\n");
    size_exponent = scan_numbers(m_exponent, &sign_exponent);

    print_array(m_int, size_int);
    print_array(m_mantissa, size_mantissa);
    print_array(m_exponent, size_exponent);

    return 0;
}

int scan_numbers(int *massiv, int *sign)
{
    int count = 0;
    *sign = 0;
    char b;

    while (((b = getchar()) != EOF) && (b != '\n'))
    {
        if (count != 0 && (b == '+' || b == '-'))
            return -1;
        else if (b == '-')
            *sign = 1;
        else if (b == '+')
            *sign = 0;
        else if (((b - 48) <= 9) && (b - 48) >= 0)
        {
            massiv[count] = b - 48;
            count++;
        }
        else
            return -1;
    }
    return count;
}


void print_array(const int *array, int array_size)
{
    printf("\n");
    for (int i = 0; i < array_size; i++)
    {
        printf("%d ", array[i]);
    }

}
