#include "history.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static hist_node *head = NULL;
static hist_node *tail = NULL;

hist_node *get_history_head(void)
{
    return head;
}

hist_node *get_history_tail(void)
{
    return tail;
}

int history_add(string_t *string_t_ptr)
{
    hist_node *new = malloc(sizeof(hist_node));
    if (new == NULL)
    {
        fprintf(stderr, "Error alocating memory in history_add");
        fflush(stderr);
        return -1;
    }

    new->str_data = string_t_ptr;

    // if initial node
    if (head == NULL)
    {
        new->index = 0;
        new->next = NULL;
        new->previous = NULL;
        head = new;
        tail = new;
    }
    else
    {
        new->index = tail->index++;
        tail->next = new;
        new->previous = tail;
        new->next = NULL;
        tail = new;
    }
    new = NULL;
    return 0;
}

void history_cleanup(void)
{
    // no history, do nothing
    if ((head == NULL) && tail == NULL)
    {
        return;
    }

    // base case, one node remaining
    if (head == tail)
    {
        free(head);
        head = NULL;
        tail = NULL;
        return;
    }

    head = head->next;
    free(head->previous);
    head->previous = NULL;
    history_cleanup();
}
