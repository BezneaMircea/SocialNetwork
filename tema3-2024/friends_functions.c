/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */

#include "structuri.h"
#include "users.h"
#include "friends.h"
#include "utils.h"

/**
 * @brief Functia creeaza o legatura intre doi utilizatori,
 * 2 muchii intr-un graf neorientat
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
 * @brief Functia sterge o legatura intre doi utilizatori,
 * 2 muchii intr-un graf neorientat
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
		printf("There is no way to get from %s to %s\n", name1, name2);
	else
		printf("The distance between %s - %s is %d\n",
			   name1, name2, dist[id_name2]);

	q_free(queue);
	free(queue);
	free(vizitat);
	free(dist);
}

/**
 * @brief Functia afiseaza cel mai popular utilizator
 * dintre un utilizator si prietenii sai
 * @param graph: Graful
 * @param user: Numele utilizatorului
 */
void most_popular(list_graph_t *graph, char *user) {
	int id = get_user_id(user);

	// numar de conexiuni ale utilizatorului
	int user_connections = graph->neighbors[id]->size;

	// vom cauta maximul de conexiuni ale unui vecin
	// la final comparam vecinul cu cele mai multe conexiuni cui user-ul
	// si vedem cine este mai popular
	int popular_connections = 0;
	int popular_friend_id = 0;

	ll_node_t *friend = graph->neighbors[id]->head;
	while (friend) {
		int friend_id = *(int *)friend->data;
		// cate conexiuni are vecinul lui user
		int friend_connections = graph->neighbors[friend_id]->size;

		if (popular_connections < friend_connections) {
			popular_connections = friend_connections;
			popular_friend_id = friend_id;
		} else if (popular_connections == friend_connections) {
			// In caz de egalitate pentru prieteni
			// se va considera primul dupa id
			if (popular_friend_id > friend_id) {
				popular_connections = friend_connections;
				popular_friend_id = friend_id;
			}
		}

		friend = friend->next;
	}

	if (user_connections < popular_connections) {
		char *popular_name = get_user_name(popular_friend_id);
		printf("%s is the most popular friend of %s\n", popular_name, user);
	} else {
		printf("%s is the most popular\n", user);
	}
}
