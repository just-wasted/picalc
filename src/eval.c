#include "eval.h"
#include "lcd.h"
#include <stdio.h>

// token_types
// #define OPERATOR 0
// #define NUMBER 1

// typedef struct str_token
// {
//     char *start;
//     char *end;
//     int token_type;
//     struct str_tokens *next;
// } str_token;

// str_token *init_list(void);
// void append_list(str_token *list);

void add(long num_1, long num_2);
void sub(long num_1, long num_2);
void mul(long num_1, long num_2);
void div(long num_1, long num_2);
int count_digits(long num);

int tokenize_str(char *str, str_tokens_t *list)
{
    // str_token *token_list = malloc(sizeof(str_token));
    // token_list->next = NULL;

    // str_token *head = token_list;
    // str_token *cursor = token_list;
    // int i = 0;
    // char chr = str[0];
    // int in_token = 0;
    //
    // while (chr != '\0')
    // {
    //     i++;
    //     chr = str[i];
    // }

    int items_read =
        sscanf(str, "%ld%c%ld", &list->num_1, &list->operator, &list->num_2);

    if (items_read != 3)
    {
        return -1;
    }

    printf("\n");
    printf("num_1: %ld\n", list->num_1);
    printf("operator: %c\n", list->operator);
    printf("num_2: %ld\n", list->num_2);

    return 0;
}

int eval_token(str_tokens_t *tk_list)
{
    switch (tk_list->operator)
    {
    case '+':
        add(tk_list->num_1, tk_list->num_2);
        break;

    case '-':
        sub(tk_list->num_1, tk_list->num_2);
        break;

    case '*':
        mul(tk_list->num_1, tk_list->num_2);
        break;

    case '/':
        div(tk_list->num_1, tk_list->num_2);
        break;
    }
    return 0;
}

void add(long num_1, long num_2)
{
    long val = num_1 + num_2;

    int len = count_digits(val) + 3;
    char val_str[len];
    snprintf(val_str, len, "= %ld", val);
    printf("string: %s\n", val_str);
    printf("nr digits: %d\n", len);
    fflush(stdout);
    lcd_write_str(val_str);
}

void sub(long num_1, long num_2)
{
    long val = num_1 - num_2;

    int len = count_digits(val) + 3;
    char val_str[len];
    snprintf(val_str, len, "= %ld", val);

    lcd_write_str(val_str);
}

void mul(long num_1, long num_2)
{
    long val = num_1 * num_2;

    int len = count_digits(val) + 3;
    char val_str[len];
    snprintf(val_str, len, "= %ld", val);

    lcd_write_str(val_str);
}

void div(long num_1, long num_2)
{
    float val = (float)num_1 / (float)num_2;

    int len = count_digits((long)val) + 6;
    char val_str[len];

    snprintf(val_str, len, "= %f.3", val);

    lcd_write_str(val_str);
}

int count_digits(long num)
{
    int remainder = 1;
    int count = 1;

    while (remainder != 0)
    {
        remainder = num % 10;
        num /= 10;
        count++;
    }
    return count;
}
