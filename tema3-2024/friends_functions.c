/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */

#include "structuri.h"
#include "users.h"
#include "friends.h"
#include "utils.h"


/**
 * @brief Functia creeaza o legatura intre doi utilizatori, 2 muchii intr-un graf neorientat
 * @param name1: Numele primului utilizator
 * @param name2: Numele celui de-al doilea utilizator
 */
void add_friend(list_graph_t *graph, char *name1, char *name2) {
	int id_name1 = get_user_id(name1);
	int id_name2 = get_user_id(name2);

	// graf neorientat
	lg_add_edge(graph, id_name1, id_name2);

	printf("Added connection %s - %s\n", name1, name2);
}

/**
 * @brief Functia sterge o legatura intre doi utilizatori, 2 muchii intr-un graf neorientat
 * @param name1: Numele primului utilizator
 * @param name2: Numele celui de-al doilea utilizator
 */
void remove_friend(list_graph_t *graph, char *name1, char *name2) {
	int id_name1 = get_user_id(name1);
	int id_name2 = get_user_id(name2);

	// graf neorientat
	lg_remove_edge(graph, id_name1, id_name2);

	printf("Removed connection %s - %s\n", name1, name2);
}

/**
 * @brief Functia afiseaza distanta dintre doi utilizatori
 * @param name1: Numele primului utilizator
 * @param name2: Numele celui de-al doilea utilizator
*/
void distance_friend(list_graph_t *graph, char *name1, char *name2) {
	int id_name1 = get_user_id(name1);
	int id_name2 = get_user_id(name2);

	int *vizitat = calloc(graph->nodes, sizeof(int));
	int *dist = calloc(graph->nodes);

	queue_t *queue = q_create(sizeof(int), graph->nodes);
	q_enqueue(queue, &id_name1);
	vizitat[id_name1] = 1;


	while (!q_is_empty(queue)) {
		//int current_node = *(int *)q_front(queue);
		q_dequeue(queue);

	}
	free(vizitat);

}
