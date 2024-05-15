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
	int *dist = calloc(graph->nodes, sizeof(int));

	for (int i = 0; i < graph->nodes; i++)
		dist[i] = -1;

	queue_t *queue = q_create(sizeof(int), graph->nodes);
	q_enqueue(queue, &id_name1);
	vizitat[id_name1] = 1;
	dist[id_name1] = 0;

	while (!q_is_empty(queue)) {
		int nodtop = *(int *)q_front(queue);
		q_dequeue(queue);
		ll_node_t *current_node = graph->neighbors[nodtop]->head;
		while (current_node) {
			int vecin = *(int *)current_node->data;
            if (vizitat[vecin] == 0) {
                vizitat[vecin] = 1;
                dist[vecin] = dist[nodtop] + 1;
                q_enqueue(queue, &vecin);
            }
            current_node = current_node->next;
		}
	}

	if (dist[id_name2] == -1)
		printf("There is no way to get from %s - %s\n", name1, name2);
	else
		printf("The distance between %s - %s is %d\n", name1, name2, dist[id_name2]);
	
	free(vizitat);
	free(dist);
}
