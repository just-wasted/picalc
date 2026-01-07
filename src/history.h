#pragma once

#include "srledit.h"

/*
doubly linked list node for history entries
*/
typedef struct hist_node
{
    unsigned index;
    string_t *str_data;
    struct hist_node *previous;
    struct hist_node *next;

} hist_node;

hist_node *get_history_head(void);

hist_node *get_history_tail(void);

int history_add(string_t *string_t_ptr);

void history_cleanup(void);
