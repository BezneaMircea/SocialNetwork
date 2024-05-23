/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */

#include "feed.h"

/** @brief Aceasta functie face parsarea comenzii feed si o executa
 *  @param tree_vector: Vectorul de copaci (postari)
 *  @param graph: Graful de prieteni
 */
void feed(g_tree **tree_vector, list_graph_t *graph) {
	char *name = strtok(NULL, "\n ");
	unsigned int user_id = get_user_id(name);

	int feed_size = atoi(strtok(NULL, "\n "));

	for (int i = MAX_POSTS_NR - 1; i >= 0 && feed_size; i--)
		/* Iteram in ordinea inversa in care au fost facute postarile*/
		if (tree_vector[i]) {
			/* Daca a fost facuta postarea curenta*/
			unsigned int pers_id;
			pers_id = ((tree_data *)tree_vector[i]->root->data)->user_id;
			if (pers_id == user_id || lg_has_edge(graph, pers_id, user_id)) {
				/* Daca cel care a facut postarea este prieten cu persoana cu
				 * numele name */
				char *pers_name = get_user_name(pers_id);
				printf("%s: %s\n", pers_name,
					   ((tree_data *)tree_vector[i]->root->data)->post_name);
				feed_size--;
			}
		}
}

/** @brief Functia face parsarea comenzii view profile si afiseaza
 *		   rezultatul corespunzator
 *  @param tree_vector: Vectorul de copaci (postari)
 */
void view_profile(g_tree **tree_vector) {
	char *name = strtok(NULL, "\n ");
	unsigned int user_id = get_user_id(name);

	for (int i = 0; i < MAX_POSTS_NR; i++) {
		/* Iteram in ordine prin vectorul de postari */
		g_tree *cur_tree = tree_vector[i];
		if (!cur_tree)
			continue;
		/* Daca postarea nu a fost facuta mergem mai departe */

		if (((tree_data *)cur_tree->root->data)->user_id == user_id) {
			/* Daca postarea a fost facuta de utilizatorul din input */
			printf("Posted: %s\n",
				   ((tree_data *)cur_tree->root->data)->post_name);
		}

		for (int i = 0; i < cur_tree->root->nr_children; i++) {
			unsigned int cur_id;
			cur_id = ((tree_data *)cur_tree->root->children[i]->data)->user_id;
			if (cur_id == user_id) {
				/* Daca repostul a fost facut de utilizatorul din input */
				printf("Reposted: %s\n",
					   ((tree_data *)cur_tree->root->data)->post_name);
			}
		}
	}
}

/** @brief Functia face parsarea si executa functionalitatea "Friends that
 *		   reposted"
 *  @param tree_vector: Vectorul de copaci (postari)
 *  @param graph: Graful de prieteni
 */
void friends_repost(g_tree **tree_vector, list_graph_t *graph) {
	char *name = strtok(NULL, "\n ");
	unsigned int user_id = get_user_id(name);

	int post_id = atoi(strtok(NULL, "\n "));

	g_tree *post = tree_vector[post_id];

	for (int i = 0; i < post->root->nr_children; i++) {
		/* Iteram prin reposturi */
		unsigned int pers_id;
		pers_id = ((tree_data *)post->root->children[i]->data)->user_id;
		char *pers_name = get_user_name(pers_id);
		if (lg_has_edge(graph, user_id, pers_id))
			printf("%s\n", pers_name);
			/* Daca este prieten cu utilizatorul primit afisam corespunzator */
	}
}

typedef struct {
	int nr_connect;
	unsigned int id;
} id_connections;

typedef struct {
	int size;
	id_connections *data;
} group_vector;

static void swap_group_data(id_connections *a, id_connections *b) {
	id_connections aux = *a;
	*a = *b;
	*b = aux;
}

/** @brief Functia face parsarea si executa functionalitatea "Clica"
 *  @param graph: Graful de prieteni
 */
void clique(list_graph_t *graph) {
	char *name = strtok(NULL, "\n ");
	unsigned int user_id = get_user_id(name);

	int nr_friends = graph->neighbors[user_id]->size;

	group_vector *group = malloc(sizeof(group_vector));
	group->data = calloc(nr_friends + 1, sizeof(id_connections));

	group->size = nr_friends + 1;
	/* Vector de frecventa in care, daca elementul de pe pozitia i este
	 * 1, inseamna ca userul care are ID-ul = i este vecinul lui user
	 * il punem si pe user setat pe 1 ca si el face parte din grup */

	int k = 0;
	for (unsigned int i = 0; i < MAX_PEOPLE; i++) {
		if (lg_has_edge(graph, user_id, i) == 1 || i == user_id) {
			group->data[k].id = i;

			/* Numarul de conexiuni */
			group->data[k].nr_connect = 0;
			k++;
		}
	}

	for (int i = 0; i < nr_friends + 1; i++) {
		/* Iteram prin toti vecinii lui user */
		for (int j = 0; j < nr_friends + 1; j++) {
			if (lg_has_edge(graph, group->data[i].id, group->data[j].id) == 1 &&
				i != j) {
				group->data[i].nr_connect++;
			}
		}
	}

	/* Sortam vectorul de conexiuni descrescator ca sa pot scoate de la final */

	for (int i = 0; i < nr_friends + 1; i++) {
		for (int j = i + 1; j < nr_friends + 1; j++) {
			if (group->data[i].nr_connect < group->data[j].nr_connect) {
				swap_group_data(&group->data[i], &group->data[j]);
			} else if (group->data[i].nr_connect == group->data[j].nr_connect &&
					   group->data[i].id < group->data[j].id) {
				swap_group_data(&group->data[i], &group->data[j]);
			}
		}
	}

	while (group->data[nr_friends].nr_connect != group->size - 1) {
		nr_friends--;
		group->size--;
	}

	/* Sortam vectorul de conexiuni crescator dupa ID */
	for (int i = 0; i < nr_friends + 1; i++)
		for (int j = 0; j < nr_friends + 1; j++)
			if (group->data[i].id < group->data[j].id)
				swap_group_data(&group->data[i], &group->data[j]);

	/* Afisam rezultatul */
	printf("The closest friend group of %s is:\n", name);
	for (int i = 0; i < nr_friends + 1; i++)
		printf("%s\n", get_user_name(group->data[i].id));

	free(group->data);
	free(group);
}

