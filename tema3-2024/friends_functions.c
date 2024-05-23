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
void add_friend(list_graph_t *graph) {
	char *name1 = strtok(NULL, "\n ");
	char *name2 = strtok(NULL, "\n ");

	int id_name1 = get_user_id(name1);
	int id_name2 = get_user_id(name2);

	/* Graf neorientat */
	lg_add_edge(graph, id_name1, id_name2);

	printf("Added connection %s - %s\n", name1, name2);
}

/**
 * @brief Functia sterge o legatura intre doi utilizatori,
 * 2 muchii intr-un graf neorientat
 * @param name1: Numele primului utilizator
 * @param name2: Numele celui de-al doilea utilizator
 */
void remove_friend(list_graph_t *graph) {
	char *name1 = strtok(NULL, "\n ");
	char *name2 = strtok(NULL, "\n ");

	int id_name1 = get_user_id(name1);
	int id_name2 = get_user_id(name2);

	/* Graf neorientat */
	lg_remove_edge(graph, id_name1, id_name2);

	printf("Removed connection %s - %s\n", name1, name2);
}

/**
 * @brief Functia afiseaza toti prietenii prietenilor,
 * care nu sunt deja prieteni cu user
 * @param graph: Graful
 * @param user: Numele utilizatorului
*/
void suggestions_friend(list_graph_t *graph) {
	char *user = strtok(NULL, "\n ");

	int id = get_user_id(user);

	/* Lista de prieteni a utilizatorului */
	linked_list_t *user_friends = graph->neighbors[id];

	/* Variabila ma va ajuta la afisare, deoarece difera mesajul
	 * daca nu am sugestii */
	int nr_suggestions = 0;

	/* Vector de frecventa in care, daca elementul de pe pozitia i este
	 * 1, inseamna ca userul care are ID-ul = i satisface conditiile pentru
	 * suggestions */
	int *suggestions = calloc(MAX_PEOPLE, sizeof(int));

	ll_node_t *friend = user_friends->head;

	/* Trec prin toti prietenii utilizatorului */
	while (friend) {
		int friend_id = *(int *)friend->data;

		linked_list_t *list_friends_of_friend = graph->neighbors[friend_id];

		ll_node_t *friend_of_friend = list_friends_of_friend->head;

		/* Trec prin toti prietenii prietenului utilizatorului */
		while (friend_of_friend) {
			int friend_of_friend_id = *(int *)friend_of_friend->data;

			/* Daca dau de un user care nu este prieten cu utilizatorul dat ca
			 * input si nu este nici utilizatorul propriu-zis, atunci il setez
			 * pe 1 in vectorul de frecventa pt a fi afisat la final */
			if (friend_of_friend_id != id &&
				!lg_has_edge(graph, id, friend_of_friend_id)) {
				suggestions[friend_of_friend_id] = 1;
				nr_suggestions++;
			}

			friend_of_friend = friend_of_friend->next;
		}

		friend = friend->next;
	}

	if (nr_suggestions == 0) {
		printf("There are no suggestions for %s\n", user);
	} else {
		printf("Suggestions for %s:\n", user);

		for (int i = 0; i < MAX_PEOPLE; i++) {
			if (suggestions[i] != 0)
				printf("%s\n", get_user_name(i));
		}
	}
	free(suggestions);
}

/**
 * @brief Functia afiseaza prietenii comuni ai doi utilizatori
 * @param name1: Numele primului utilizator
 * @param name2: Numele celui de-al doilea utilizator
*/
void common_friends(list_graph_t *graph) {
	char *name1 = strtok(NULL, "\n ");
	char *name2 = strtok(NULL, "\n ");

	int id_name1 = get_user_id(name1);
	int id_name2 = get_user_id(name2);

	/* Acest vector este un vector de frecventa. Atunci cand dau de un user
	 * ca prieten ori de la name1 ori de la name2 ma duc pe pozitia ID in vector
	 * si cresc elementul respectiv. Daca la final acest element este 2 inseamna
	 * ca ambii useri au ca prieten acel utilizator */
	int *common_friends = calloc(MAX_PEOPLE, sizeof(int));
	int nr_common = 0;

	/* Ma duc pe lista cu prietenii celui de-al doilea utilizator */
	linked_list_t *list_user = graph->neighbors[id_name1];
	ll_node_t *friend = list_user->head;

	/* Parcurgerea prietenilor primului utilizator si abdatarea vectorului 
	 * de prieteni comuni */
	while (friend) {
		int friend_id = *(int *)friend->data;
		common_friends[friend_id]++;
		if (common_friends[friend_id] == 2)
			nr_common++;
		friend = friend->next;
	}

	/* Ma duc pe lista cu prietenii celui de-al doilea utilizator */
	list_user = graph->neighbors[id_name2];
	friend = list_user->head;

	/* Parcurgerea prietenilor celui de-al doilea utilizator si abdatarea
	 * vectorului de prieteni comuni */
	while (friend) {
		int friend_id = *(int *)friend->data;
		common_friends[friend_id]++;
		if (common_friends[friend_id] == 2)
			nr_common++;
		friend = friend->next;
	}

	if (nr_common == 0) {
		printf("No common friends for %s and %s\n", name1, name2);
	} else {
		printf("The common friends between %s and %s are:\n", name1, name2);
		for (int i = 0; i < MAX_PEOPLE; i++)
			if (common_friends[i] == 2)
				printf("%s\n", get_user_name(i));
	}

	free(common_friends);
}

/**
 * @brief Functia afiseaza distanta dintre doi utilizatori
 * @param name1: Numele primului utilizator
 * @param name2: Numele celui de-al doilea utilizator
*/
void distance_friend(list_graph_t *graph) {
	char *name1 = strtok(NULL, "\n ");
	char *name2 = strtok(NULL, "\n ");

	int id_name1 = get_user_id(name1);
	int id_name2 = get_user_id(name2);
	
	/* BFS incepand din nodul primului utilizator */
	int *vizitat = calloc(MAX_PEOPLE, sizeof(int));
	int *dist = calloc(MAX_PEOPLE, sizeof(int));

	for (int i = 0; i < graph->nodes; i++)
		dist[i] = -1;

	queue_t *queue = q_create(sizeof(int), MAX_QUEUE_SIZE);
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
				/* Distanta pana la vecin */
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
void most_popular(list_graph_t *graph) {
	char *user = strtok(NULL, "\n ");
	int id = get_user_id(user);

	/* Numar de conexiuni ale utilizatorului */
	int user_connections = graph->neighbors[id]->size;

	/* Vom cauta maximul de conexiuni ale unui vecin
	 *  la final comparam vecinul cu cele mai multe conexiuni cu user-ul
	 *  si vedem cine este mai popular */
	int popular_connections = 0;
	int popular_friend_id = 0;

	ll_node_t *friend = graph->neighbors[id]->head;
	while (friend) {
		int friend_id = *(int *)friend->data;
		/* Cate conexiuni are vecinul lui user */
		int friend_connections = graph->neighbors[friend_id]->size;

		if (popular_connections < friend_connections) {
			popular_connections = friend_connections;
			popular_friend_id = friend_id;
		} else if (popular_connections == friend_connections) {
			/* In caz de egalitate pentru prieteni
			 *  se va considera primul dupa id */
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

/**
 * @brief Functia afiseaza numarul de prieteni ai unui utilizator
 * @param graph: Graful
 */
void how_many_friends(list_graph_t *graph) {
	char *name = strtok(NULL, "\n ");
	int id = get_user_id(name);
	printf("%s has %d friends\n", name, graph->neighbors[id]->size);
}
