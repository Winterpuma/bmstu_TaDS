#include <stdio.h>

#define N 30
#define N_TEMP 50

int scan_numbers(int *massiv, int *sign);
void print_array(const int *array, int size);
void add(int *first, int *second, int size);
void divide_integers(int a, int b, int *result, int accuracy);

int main()
{
    int m_int[N], m_mantissa[N], m_exponent[N_TEMP];//5];// = {0,};
    int sign_int, sign_mantissa, sign_exponent = 0;
    int size_int, size_mantissa, size_exponent;
    /*
    printf("Input integer:\n");
    size_int = scan_numbers(m_int, &sign_int);
    printf("Input mantissa:\n");
    size_mantissa = scan_numbers(m_mantissa, &sign_mantissa);
    printf("Input exponent:\n");
    size_exponent = scan_numbers(m_exponent, &sign_exponent);

    //add(m_int, m_mantissa, 6);*/
    divide_integers(1, 9, m_exponent, N_TEMP);

    return 0;
}

void divide_integers(int a, int b, int *result, int accuracy)
{
    int res, left;

    for (int i = 0; i < accuracy; i++)
        result[i] = 0;

    for (int rank = 2; rank <= accuracy; rank++)
    {
        if (a == 0)
            break;
        else if (a > b)
        {
            res = 0;
            left = 0;
            for(int j = a - b; j >= 0; j -= b)
            {
                res++;
                a = j;
            }
            result[rank] = res;
        }
        a *= 10;
    }
    print_array(result, 50);
}

// this function adds up 2 arrays
void add(int *first, int *second, int size)
{
    int tmp;
    print_array(first, size);
    print_array(second, size);

    for (int i = size - 1; i >= 2; i--)
    {
        tmp = first[i] + second[i];

        if (tmp < 10)
            first[i] = tmp;
        else
        {
            first[i] = tmp - 10;
            if (first[i-1] != 9)//а существует ли место под i-1 вообще?
                first[i-1] += 1;
            else
            {
                first[i-1] == 0;
                first[i-2] += 1;
            }
        }
    }
    printf("\nresult:\n");
    print_array(first, size);
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
        printf("%d", array[i]);
    }

}
