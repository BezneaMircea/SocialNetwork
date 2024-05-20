/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 */

#ifndef STRUCTURI_H
#define STRUCTURI_H

/// Implementari pentru: Coada, Stiva, Graf NEORIENTAT cu liste,
/// lista simplu inlantuita, lista dublu inlantuita circulara
#include "utils.h"

///
///
/// Simple linked list
///
///
typedef struct ll_node_t
{
	void *data;
	struct ll_node_t *next;
} ll_node_t;

typedef struct linked_list_t
{
	ll_node_t *head;
	unsigned int data_size;
	unsigned int size;
} linked_list_t;

linked_list_t *ll_create(unsigned int data_size);
void ll_add_nth_node(linked_list_t *list, unsigned int n, const void *new_data);
ll_node_t *ll_remove_nth_node(linked_list_t *list, unsigned int n);
unsigned int ll_get_size(linked_list_t *list);
void ll_print_int(linked_list_t *list);
void ll_free(linked_list_t **pp_list);

///
///
/// Double linked list
///
///
typedef struct dll_node dll_node;
struct dll_node {
	void *data;
	dll_node *prev, *next;
};

typedef struct dll_list dll_list;
struct dll_list {
	dll_node *head;
	int data_size;
	int size;
};

void dll_free(dll_list **pp_list, void (*elem_free)(void *));
void dll_print_string_list(dll_list *list);
void dll_print_int_list(dll_list *list);
void dll_add_nth_node(dll_list *list, int n, void *new_data);
void remove_a_node(dll_node *node_to_remove, dll_list *list);
dll_node *dll_remove_nth_node_from_end(dll_list *list);
dll_node *dll_remove_nth_node(dll_list *list, int n);
dll_list *dll_create(int data_size);

///
///
/// queue
///
///
typedef struct queue_t queue_t;
struct queue_t
{
	/* Dimensiunea maxima a cozii */
	unsigned int max_size;
	/* Dimensiunea cozii */
	unsigned int size;
	/* Dimensiunea in octeti a tipului de date stocat in coada */
	unsigned int data_size;
	/* Indexul de la care se vor efectua operatiile de front si dequeue */
	unsigned int read_idx;
	/* Indexul de la care se vor efectua operatiile de enqueue */
	unsigned int write_idx;
	/* Bufferul ce stocheaza elementele cozii */
	void **buff;
};

queue_t *q_create(unsigned int data_size, unsigned int max_size);
unsigned int q_get_size(queue_t *q);
unsigned int q_is_empty(queue_t *q);
void *q_front(queue_t *q);
int q_dequeue(queue_t *q);
int q_enqueue(queue_t *q, void *new_data);
void q_clear(queue_t *q);
void q_free(queue_t *q);

///
///
/// Stack
///
///
typedef struct stack_t stack_t;
struct stack_t {
	linked_list_t *list;
};

void clear_stack(stack_t *stack);
void purge_stack(stack_t **stack);
void push_stack(stack_t *stack, void *new_data);
void pop_stack(stack_t *stack);
void *peek_stack(stack_t *stack);
int is_empty_stack(stack_t *stack);
int get_size_stack(stack_t *stack);
stack_t *init_stack(unsigned int data_size);

///
///
/// Graf Neorientat cu liste
///
///
/** @param neighbors: Vector de pointeri spre listele de vecini
 *  @param nodes: Nr de noduri din graf
 */
typedef struct {
	int nodes;
	linked_list_t **neighbors;
} list_graph_t;

void purge_graph(list_graph_t **graph);
void lg_print_graph(list_graph_t *graph);
void lg_free(list_graph_t *graph);
void lg_remove_edge(list_graph_t *graph, int src, int dest);
int lg_has_edge(list_graph_t *graph, int src, int dest);
void lg_add_edge(list_graph_t *graph, int src, int dest);
list_graph_t *lg_create(int nodes);


///
///
/// Generic Tree
///
///
typedef struct g_tree_node g_tree_node;
struct g_tree_node
{
    void *data;
    g_tree_node **children;
    int nr_children;
};

typedef struct g_tree g_tree;
struct g_tree
{
    g_tree_node *root;
    unsigned int data_size;
    unsigned int max_children_nr;
    int (*compare)(void *, void *);
    void (*free_data)(void *);
};

g_tree *g_tree_create(unsigned int data_size, int (*compare)(void *, void *),
                      unsigned int max_children_nr, void (*free_data)(void *));
void g_tree_insert(g_tree *tree, void *data);
g_tree_node *remove_g_subtree(g_tree *tree, g_tree_node *node_to_remove);
void purge_g_tree(g_tree **tree);
void clear_tree(g_tree_node *node, void (*free_data)(void *));
g_tree_node *get_node(g_tree_node *node, g_tree_node *node_to_add,
					  int (*compare)(void *, void *));
void print_sub_tree(g_tree_node *node);

#endif
