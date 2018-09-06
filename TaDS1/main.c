#include <stdio.h>

#define N 30
#define N_TEMP 50
//#define BLANK 3

int scan_numbers(int *massiv, int *sign);
void print_array(const int *array, int size);
void move_digits(int *arr_, int size, int poryadok);
int comparison(int *a, int *b, int size);
void subtract(int *a, int *b, int size);
void division(int *arr_float, int *arr_int, int *result, int size);

int main()
{
    int m_int[N], m_mantissa[N], m_result[N] = {0,};
    int sign_int, sign_mantissa = 0;
    int size_int, size_mantissa;
    int exponent;

    printf("Input:\n");
    size_mantissa = scan_numbers(m_mantissa, &sign_mantissa);
    printf("Input:\n");
    size_int = scan_numbers(m_int, &sign_int);
    // ввод экспоненты


    division(m_mantissa, m_int, m_result, 5);
    return 0;
}

// -1 left, +1 right
void move_digits(int *arr, int size, int poryadok)
{
    if (poryadok <= -1)
    {
        for (int i = poryadok; i < size; i++)
            arr[i+poryadok] = arr[i];
        for (int i = size + poryadok; i < size; i++)
            arr[i] = 0;
    }
    else if (poryadok >= 1)
    {
        for (int i = size - poryadok; i >= 0; i--)
            arr[i+poryadok] = arr[i];
        for (int i = poryadok - 1; i >= 0; i--)
            arr[i] = 0;
    }
}


void division(int *arr_float, int *arr_int, int *result, int size)
{
    int current_pos = 0;
    int bigger, counter, flag;

    for (int i = 0; i < size; i++)// i<size??? нужны доп слоты!
    {
        bigger = comparison(arr_float, arr_int, size);
        if (bigger == 0)
        {
            printf("Equal.");
            result[current_pos] = 1;
            //break;
        }
        else if (bigger == 1)
        {
            printf("Bigger");
            counter = 0;
            while (flag = comparison(arr_float, arr_int, size)!= -1)
            {
                if (flag == 0)
                    break;

                subtract(arr_float, arr_int, size);
                print_array(arr_float, size);
                counter++;
            }
            result[current_pos] = counter;
            current_pos++;
            if (flag == 0)
                break;
        }
        else // если высший разряд меньше высшего??
        {
            printf("Less.");
            result[current_pos] = 0;
            current_pos++;
            move_digits(arr_float, size, -1);
        }
    }
    print_array(result, size);
}

// compares 2 arrays of digits
int comparison(int *a, int *b, int size)
{
    int res = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] > b[i])
        {
            res = 1;
            break;
        }
        else if (a[i] < b[i])
        {
            res = -1;
            break;
        }
    }
    return res;
}

// first - second, (first >= second)
void subtract(int *a, int *b, int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        if (a[i] >= b[i])
            a[i] -= b[i];
        else
        {
            a[i] += 10 - b[i];
            a[i-1]--;
        }
    }
}


int scan_numbers(int *massiv, int *sign) //добавить поддержку точки в мантисе
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
