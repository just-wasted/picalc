#include "eval.h"
#include "ui.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

char *add(float num_1, float num_2);
char *subtract(float num_1, float num_2);
char *multiply(float num_1, float num_2);
char *divide(float num_1, float num_2);
char *float_to_str(float num);
int count_digits(long long num);

int tokenize_str(char *str, str_tokens_t *list)
{
    int items_read =
        sscanf(str, "%f%c%f", &list->num_1, &list->operator, &list->num_2);

    if (items_read != 3)
    {
        return -1;
    }

    printf("\n");
    printf("num_1: %f\n", list->num_1);
    printf("operator: %c\n", list->operator);
    printf("num_2: %f\n", list->num_2);

    return 0;
}

int eval_token(str_tokens_t *tk_list)
{
    char *str;
    switch (tk_list->operator)
    {
    case '+':
        str = add(tk_list->num_1, tk_list->num_2);
        ui_store_eval(str);
        free(str);
        break;

    case '-':
        str = subtract(tk_list->num_1, tk_list->num_2);
        ui_store_eval(str);
        free(str);
        break;

    case '*':
        str = multiply(tk_list->num_1, tk_list->num_2);
        ui_store_eval(str);
        free(str);
        break;

    case '/':
        str = divide(tk_list->num_1, tk_list->num_2);
        ui_store_eval(str);
        free(str);
        break;
    }

    ui_print_eval();
    str = NULL;
    return 0;
}

char *add(float num_1, float num_2)
{
    float val = num_1 + num_2;

    return float_to_str(val);
}

char *subtract(float num_1, float num_2)
{
    float val = num_1 - num_2;

    return float_to_str(val);
}

char *multiply(float num_1, float num_2)
{
    float val = num_1 * num_2;

    return float_to_str(val);
}

char *divide(float num_1, float num_2)
{
    float val = num_1 / num_2;

    return float_to_str(val);
}

char *float_to_str(float num)
{
    // count digits before decimal point
    int nr_digits = count_digits((long long)num);
    char *val_str = NULL;

    // check if number contains decimals
    if (fmodf(num, 1) != 0)
    {
        // nr_digits: add 5 for precision,1 for the decimal point
        val_str = malloc(sizeof(char) * (nr_digits + 6));
        snprintf(val_str, nr_digits, "%f.5", num);
        printf("assuming decimals!\n");
        fflush(stderr);
    }
    else
    {
        val_str = malloc(sizeof(char) * nr_digits);
        snprintf(val_str, nr_digits, "%lld", (long long)num);
    }

    return val_str;
}

int count_digits(long long num)
{
    int remainder = 1;

    // initialize count with 2:
    // 1 for /0
    // 1 for missing count++ from remainder == 0
    int count = 2;

    while (remainder != 0)
    {
        remainder = num % 10;
        num /= 10;
        count++;
    }
    return count;
}
