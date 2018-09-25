/*
18 вариант ИУ7-35б
Задача №1

Смоделировать операцию деления действительного числа на
целое число длиной до 30 десятичных цифр.
*/

#include <stdio.h>
#include <stdlib.h>

#define N 33
#define N_MAX 30
#define FLAG -8928342
#define ZER_FL 101010

#include "main.h"

int main()
{
    int *m_mant = NULL, *m_int = NULL, *m_res = NULL;

    int sign_m = 1, sign_int = 1;// -1 - negative, +1 - positive
    int size_m = 0, size_int = 0;
    int exponent = 0;

    int flag;

    m_mant = calloc(N, sizeof(int));
    m_int = calloc(N, sizeof(int));
    m_res = calloc(N, sizeof(int));

    printf("DON'T input unminingfull digits\n");

    flag = input_float(m_mant, &size_m, &sign_m, &exponent);
    if (flag < 0)
        return flag;

    flag = input_int(m_int, &size_int, &sign_int, &exponent);
    if (flag < 0)
        return flag;

    if (zero_array(m_mant, N))
    {
        printf("\nResult is: 0.0e0");
        return 0;
    }


    int diff = size_m - size_int;
    if (diff > 1)
    {
        move_digits(m_int, N, -1*(diff - 1));
        exponent += diff - 1;
    }

    clean(m_res, N);
    division(m_mant, m_int, m_res, N, &exponent);
    exponent += 1;

    if (exponent > 99999)
    {
        printf("\n%dResulting power is greater than 99999",exponent);
        return -9;
    }
    else if (exponent < -99999)
    {
        printf("\nResulting power is lower than -99999");
        return -9;
    }

    output_res(m_res, N, exponent, sign_m * sign_int);

    free(m_mant);
    free(m_int);
    free(m_res);

    return 0;
}

// Output result
void output_res(int *arr, int size, int exp, int sign)
{
    int meaning_dig = 0; //amount of digits to show

    for (int i = 0; i < size; i++)
        if (arr[i] != 0)
            meaning_dig = i+1;

    printf("\nResult is: ");
    if (sign == -1)
        printf("-0.");
    else if(sign == 1)
        printf("+0.");

    for (int i = 0; i < meaning_dig; i++)
        printf("%d", arr[i]);
    printf("e%d", exp);
}

// Input float
int input_float(int *m_m, int *size, int *sign, int *exponent)
{
    char b;
    int flag = 0;
    int dot = N+1;
    int flag_sign = 0;

    *size = 0;
    *exponent = FLAG;

    printf("\nInput float:\n");
    printf("You should always enter e/E.\n");
    printf("Correct input: -1e0, 0.5e-7, +.5e1\n\n");
    printf("1        10        20       30e1   5\n");
    printf("|--------|---------|---------|-|---|\n");
    while ((scanf("%c", &b) && (b != EOF) && (b != '\n') && (b != 'E') && (b != 'e')))
    {

        // Check correctness
        if ((*size != 0 || flag_sign) && (b == '+' || b == '-'))
        {
            printf("\nWrong input!");
            return -1;
        }
        else if (b == '-')
        {
            *sign = -1;
            flag_sign = 1;
        }
        else if (b == '+')
        {
            *sign = 1;
            flag_sign = 1;
        }
        else if ((b <= '9') && (b >= '0'))
            m_m[(*size)++] = b - 48;
        else if (b == '.' && dot == N+1)
            dot = *size;
        else
        {
            printf("\nWrong input");
            return -1;
        }
    }

    // if nothing inputed
    if (*size == 0)
    {
        printf("Empty input!");
        return -9;
    }

    if (*size > 30)
    {
        printf("Too many digits");
        return -10;
    }

    // if dot wasn't inputed
    if (dot == N+1)
    {
        dot = *size;
    }

    // Input power
    if ((b == 'E') || (b == 'e'))
    {
        flag = scanf("%d", exponent);
        if (!flag)
            return -7;
    }

    if (*exponent > 99999 || *exponent < -99999) // NOTE error scanfing exponent
    {
        printf("Exponent should lie within [-99999, 99999]");
        return -9;
    }

    while (((b = getchar()) != EOF) && (b != '\n'))
    {
        printf("Something wrong with exponent!");
        return -10;
    }
    normalize_float(m_m, size, dot, exponent);
    return 0;
}

// Input integer
int input_int(int *m_i, int *size, int *sign, int *exponent)
{
    int flag = 0;
    int zero_flag = 1; // 1 - zero inputed
    char b;

    *size = 0;

    printf("\nInput integer:\n");
    printf("Correct input: +77, -35, 0003\n");
    printf("1        10        20       30\n");
    printf("|--------|---------|---------|\n");

    while (((b = getchar()) != EOF) && (b != '\n'))
    {
        // Check correctness
        if (*size != 0 && (b == '+' || b == '-'))
        {
            printf("\nWrong input!", *size, b);
            flag = -1;
        }
        else if (b == '-')
            *sign = -1;
        else if (b == '+')
            *sign = 1;
        else if ((b <= '9') && (b >= '0'))
        {
            m_i[(*size)++] = b - 48;
            if (b != '0')
                zero_flag = 0;
        }
        else
        {
            printf("\nWrong input");
            return -1;
        }
    }

    // Check size of
    if (*size > 30)
    {
        printf("Too many digits");
        return -2;
    }
    if (*size == 0)
    {
        printf("Nothing inputed!");
        return -2;
    }

    if (zero_flag)
    {
        printf("Can't divide by zero.");
        return -3;
    }

    if (!flag)
        normalize_int(m_i, size);

    return flag;
}

int count_zero(int *arr, int size)
{
    int zero = 0;

    for(int i = 0; i < size; i++)
    {
        if (arr[i] != 0)
        {
            zero = i;
            break;
        }
    }
    return zero;
}

void normalize_int(int *arr, int *size)
{
    int zero = count_zero(arr, *size);
    move_digits(arr, N, N - *size);
    *size -= zero;
}

void normalize_float(int *arr, int *size, int dot, int *exponent)
{
    int zero = 0;

    for(int i = 0; i < *size; i++)
    {
        if (arr[i] != 0)
        {
            zero = i;
            break;
        }
    }

    *exponent -= *size - dot;
    move_digits(arr, N, N - *size);
    *size -= zero;
}

// -1 left, +1 right
void move_digits(int *arr, int size, int poryadok)
{
    if (poryadok <= -1)
    {
        poryadok *= -1;
        for (int i = 0; i < size - poryadok; i++)
            arr[i] = arr[i+poryadok];
        for (int i = size - poryadok; i < size; i++)
            arr[i] = 0;
    }
    else if (poryadok >= 1)
    {
        for (int i = size - 1; i >= poryadok; i--)
            arr[i] = arr[i-poryadok];
        for (int i = poryadok - 1; i >= 0; i--)
            arr[i] = 0;
    }
}

// Checks if arr_float / arr_int > 10
void check_ten(int *arr_float, int *arr_int, int size, int *exp)
{
    int count = 0;
    int equal;

    while (comparison(arr_float, arr_int, size) == 1 && count < 10)
        count++;

    if (count == 10)
    {
        move_digits(arr_int, size, -1);
        (*exp)++;
    }

}


// division of 2 arrays of digits
void division(int *arr_float, int *arr_int, int *result, int size, int *exp)
{
    int current_pos = 0;
    int equal, counter, flag, flag_zero;
    int last_digit = FLAG;
    int beggining_flag = 1; // used to

    check_ten(arr_float, arr_int, size, exp);

    flag_zero = 1;
    while (current_pos < N_MAX + 1)
    {
        equal = comparison(arr_float, arr_int, size);

        // if two arrays are equal
        if (equal == 0)
        {
            result[current_pos] = 1;
            break;
        }
        // if first one is greater
        else if (equal == 1)
        {
            flag_zero = 0;
            counter = 0;
            // while arr_float bigger than arr_int
            while ((flag = comparison(arr_float, arr_int, size)) != -1)
            {
                if (flag == 0)
                {
                    counter++;
                    break;
                }

                subtract(arr_float, arr_int, size);
                counter++;
            }

            if (current_pos == N_MAX) // if overflov happened
            {
                rounding(result, N_MAX, counter);
                break;
            }
            else
            {
                result[current_pos] = counter;
                current_pos++;
                beggining_flag = 0;
                if (flag == 0)
                    break;
            }
        }
        // if first one is smaller
        else
        {
            if (flag_zero)
            {
                if (beggining_flag)
                {
                    //printf(" +");
                    (*exp)--;
                }
                else
                {
                    result[current_pos] = 0;
                    current_pos++;
                }
            }
            flag_zero = 1;
            move_digits(arr_float, size, -1);
        }
    }
}


// Rounds up number by last digit
void rounding(int *arr, int size, int last_digit)
{
    if (last_digit >= 5)
    {
        arr[size-1]++;
        for (int i = size - 1; i >= 0; i--)
        {
            if (arr[i] == 10)
            {
                arr[i] -= 10;
                arr[i-1]++;
            }
            else
                break;
        }
    }
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


// will subtract two arrays
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


void print_array(const int *array, int array_size)
{
    printf("\n");
    for (int i = 0; i < array_size; i++)
    {
        printf("%d ", array[i]);
    }

}


void clean(int *array, int size)
{
    for (int i = 0; i < size; i++)
        array[i] = 0;
}

int zero_array(int *array, int size)
{
    for (int i = 0; i < size; i++)
        if (array[i] != 0)
            return 0;
    return 1;
}

//123456789012345678901234567899
// 9999...e0 / 2
// дробный порядок 2e2.5
//999999999999999999999999999999.e99999
//333333333333333333333333333333333e0
