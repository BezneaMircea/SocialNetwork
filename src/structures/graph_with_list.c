/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */

#include "structuri.h"

/**
 * @brief Initializeaza graful cu numarul de noduri primit ca parametru si aloca
 *        memorie pentru lista de adiacenta a grafului.
 * @param nodes: Nr de noduri din graf
 * @return Returneaza graful neorientat
 */
list_graph_t *lg_create(int nodes) {
	list_graph_t *graph = malloc(sizeof(list_graph_t));
	DIE(!graph, "Eroare la alocare\n");

	graph->nodes = nodes;
	graph->neighbors = malloc(nodes * sizeof(linked_list_t *));
	DIE(!graph->neighbors, "Eroare la alocare\n");

	for (int i = 0; i < nodes; i++)
		graph->neighbors[i] = ll_create(sizeof(int));

	return graph;
}

/** @param graph: Graful NEORIENTAT
 *  @param src: Nodul 1
 *  @param dest: Nodul 2
 *  @brief Functia creeaza o muchie de la src la dest si de la dest la src
 */
void lg_add_edge(list_graph_t *graph, int src, int dest) {
	if (!graph)
		return;

	ll_add_nth_node(graph->neighbors[src], 0, &dest);
	ll_add_nth_node(graph->neighbors[dest], 0, &src);
}

/** @brief Verifica daca exista muchie intre doua noduri
 *  @return Returneaza 1 daca exista muchie intre cele
 *          doua noduri, 0 in caz contrar. -1 pentru eroare
 *  @param graph: Graful
 *  @param src: Nodul 1
 *  @param dest: Nodul 2
 */
int lg_has_edge(list_graph_t *graph, int src, int dest) {
	if (!graph)
		return -1;

	linked_list_t *list = graph->neighbors[src];
	ll_node_t *nod = list->head;

	for (unsigned int i = 0; i < list->size; i++) {
		if (*(int *)nod->data == dest)
			return 1;
		nod = nod->next;
	}

	return 0;
}

/** @brief Elimina muchia dintre nodurile primite ca parametri
 *  @param graph: Graful
 *  @param src: Nodul 1
 *  @param dest: Nodul 2
 */
void lg_remove_edge(list_graph_t *graph, int src, int dest) {
	if (!graph)
		return;

	linked_list_t *list = graph->neighbors[src];
	ll_node_t *nod = list->head;
	for (unsigned int i = 0; i < list->size; i++) {
		if (*(int *)nod->data == dest) {
			ll_node_t *to_remove = ll_remove_nth_node(list, i);
			free(to_remove->data);
			free(to_remove);
			break;
		}
		nod = nod->next;
	}

	list = graph->neighbors[dest];
	nod = list->head;
	for (unsigned int i = 0; i < list->size; i++) {
		if (*(int *)nod->data == src) {
			ll_node_t *to_remove = ll_remove_nth_node(list, i);
			free(to_remove->data);
			free(to_remove);
			break;
		}
		nod = nod->next;
	}
}

/** @brief Elibereaza memoria folosita de lista de adiacenta a grafului
 *  @param graph: Graful
 */
void lg_free(list_graph_t *graph) {
	if (!graph)
		return;

	for (int i = 0; i < graph->nodes; i++)
		ll_free(&graph->neighbors[i]);

	free(graph->neighbors);
}

/** @brief Printeaza lista de adiacenta a grafului
 *  @param graph: Graful
 */
void lg_print_graph(list_graph_t *graph) {
	for (int i = 0; i < graph->nodes; i++) {
		printf("%d: ", i);
		ll_print_int(graph->neighbors[i]);
	}
}

/** @brief Elibereaza TOATA memoria folosita
 *  @param graph: adresa grafului a carui memorie dorim sa o eliberam.
 *				  La final facem ca acesta sa pointeze spre NULL
 */
void purge_graph(list_graph_t **graph) {
	list_graph_t *graph_to_free = *graph;

	lg_free(graph_to_free);
	free(graph_to_free);

	*graph = NULL;
}
