#ifndef LIST_H
#define LIST_H

#include <stdio.h>


typedef struct list_node {
    double data;
    struct list_node *next;
} list_node_t;

typedef list_node_t *list_t;

list_t create();

int is_empty(list_t list);

int length(list_t list);

void add_back(list_t * self, double elem);

double remove_e(list_t *list);

void show_list(list_t *list);

void print_list(FILE *fp, list_t *list);

void list_free(list_t *list);

#endif
