#pragma once

typedef struct str_tokens_t
{
    float num_1;
    float num_2;
    char operator;
} str_tokens_t;

int tokenize_str(char *str, str_tokens_t *list);

int eval_token(str_tokens_t *tk_list);
