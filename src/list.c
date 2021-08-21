#include <stdlib.h>
#include <stdio.h>

#include "../includes/list.h"

list_t create()
{
    return(list_t)NULL;
}

int is_empty(list_t list)
{
    return (list == NULL);
}

int length(list_t list)
{
    if (is_empty(list)) {
        return 0;
    } else
        return 1 + length(list->next);
}

// for error checking, check if returns NULL
void add_back(list_t * self, double elem)
{
    list_node_t *node;

    if (is_empty(*self)) {
        node = malloc(sizeof(list_node_t));
        node->data = elem;
        node->next = (list_node_t*) NULL;
        (*self) = (list_t) node;
    } else {
        add_back(&((*self)->next),elem);
    }
}


// precondition LIST NOT EMPTY / NULL
double remove_e(list_t *list)
{
    list_t aux;
    double data;

    data = (*list)->data;
    aux = (*list);
    (*list) = (list_t)(*list)->next;
    free(aux);
    return data;
}

void show_list(list_t *head)
{
    list_t temp = *head;
    printf("list is:\n");
    while (temp != NULL) {
        printf("%.2f - > ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
void print_list(FILE *fp, list_t *head)
{
    list_t temp = *head;
    fprintf(fp, "list is:\n");
    while (temp != NULL) {
        fprintf(fp, "%.2f - > ", temp->data);
        temp = temp->next;
    }
    fprintf(fp, "NULL\n");
}


void list_free(list_t *list)
{
    int i;
    int len = length(*list);
    list_t aux = NULL;

    if (len != 0) {
        for (i = 0; i < len; i++) {
            aux = (*list)->next;
            free(*list);
            (*list) = aux;
        }
    }
}

