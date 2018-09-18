/*
18 вариант ИУ7-35б
Задача №1

Смоделировать операцию деления действительного числа на
целое число длиной до 30 десятичных цифр.
*/

#include <stdio.h>

#define N 33
#define FLAG -8928342

#include "main.h"

int main()
{
    int m_mant[N] = {0,};
    int m_int[N] = {0,};
    int m_res[N] = {0,};

    int sign_m, sign_int, sign_res = 1;// -1 - negative, +1 - positive
    int size_m, size_int = 0;
    int exponent = 0;

    int flag;

    flag = input_float(m_mant, &size_m, &sign_m, &exponent);
    if (flag < 0)
        return flag;
    flag = input_int(m_int, &size_int, &sign_int, &exponent);
    if (flag < 0)
        return flag;

    //printf("Exp1: %d", exponent);
    print_array(m_mant, N);
    print_array(m_int, N);
    puts("\n");

    int diff = size_m - size_int;
    if (diff > 1)
    {
        printf("Exp2: %d ", exponent);
        move_digits(m_int, N, -1*(diff - 1));
        //exponent += diff - 1;// NOTE exponent!?
        printf("Exp3: %d ", exponent);
    }

    clean(m_res, N);
    division(m_mant, m_int, m_res, N, &exponent);
    printf("Exp4: %d ", exponent);
    //printf("\n%d", exponent);
    print_array(m_res, N);
    //sign_res = sign_m * sign_int;
    return 0;
}

// Input float
int input_float(int *m_m, int *size, int *sign, int *exponent)
{
    char b;
    int flag = 0;
    int dot = N+1;

    *size = 0;
    *exponent = FLAG;

    printf("\nInput float:\n");
    while ((scanf("%c", &b) && (b != EOF) && (b != '\n') && (b != 'E') && (b != 'e')))
    {

        // Check correctness
        if (*size != 0 && (b == '+' || b == '-'))
        {
            printf("\nWrong input! %d %c", *size, b);
            flag = -1;
        }
        else if (b == '-')
            *sign = -1;
        else if (b == '+')
            *sign = 1;
        else if ((b <= '9') && (b >= '0'))
            m_m[(*size)++] = b - 48;
        else if (b == '.' && dot == N+1)
            dot = *size;
        else
        {
            printf("\nWrong input");
            flag = -1;
        }
    }
    printf("%d", dot);

    // Input power
    printf("\n");
    if ((b == 'E') || (b == 'e'))
    {
        flag = scanf("%d", exponent);
        if (!flag)
            return -7;
    }

    if (*exponent > 99999 || *exponent < -99999)
    {
        printf("Exponent should lie within [-99999, 99999]");
        return -9;
    }

    while (((b = getchar()) != EOF) && (b != '\n'));
    normalize(m_m, *size, dot, exponent);
    return 0;
}

void normalize_float(int *arr, int size, int dot, int *exponent)
{
    int n_dot;
    for (; n_dot < size, arr[n_dot] == 0; n_dot++); // &&?

    move_digits(arr, size, -n_dot);
    *exponent -= n_dot - dot; //?
}

// Input integer
int input_int(int *m_i, int *size, int *sign, int *exponent)
{
    int flag = 0;
    char b;

    *size = 0;

    printf("\nInput integer:\n");

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
            m_i[(*size)++] = b - 48;
        else
        {
            printf("\nWrong input");
            flag = -1;
        }
    }

    // Check size of
    if (*size > 30)
    {
        printf("Too many digits");
        flag = -2;
    }
    if (*size == 0)
    {
        printf("Nothing inputed!");
        flag = -2;
    }

    if (!flag)
        normalize(m_i, *size, 0, exponent);

    return flag;
}

void normalize(int *arr, int size, int dot, int *exponent)
{
    printf("%d", *exponent);
    if (dot == 1 && arr[0] == 0)
        *exponent -= 1;
    move_digits(arr, N, N-size);
    *exponent += dot;
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

// Checks if arr_float / arr_int > 10
void check_ten(int *arr_float, int *arr_int, int size)
{
    int count = 0;
    int equal;

    while (comparison(arr_float, arr_int, size) == 1 && count < 10)
        count++;

   if (count == 10)
       move_digits(arr_int, size, -1);// NOTE exponent!?

}


// division of 2 arrays of digits
void division(int *arr_float, int *arr_int, int *result, int size, int *exp)
{
    int current_pos = 0;
    int equal, counter, flag, flag_zero;
    int last_digit = FLAG;
    int beggining_flag = 1; // used to

    check_ten(arr_float, arr_int, size);

    flag_zero = 1;
    while (current_pos < size + 1)
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

            if (current_pos == size) // if overflov happened
            {
                rounding(result, size, counter);
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
                    (*exp)--;
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
                arr[i] == 0;
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


//999999999999999999999999999999
//123456789012345678901234567899
