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

		unsigned int post_id = ((tree_data *)cur_tree->root->data)->user_id;
		if (post_id == user_id) {
			/* Daca postarea a fost facuta de utilizatorul din input */
			printf("Posted: %s\n",
				   ((tree_data *)cur_tree->root->data)->post_name);
		}
	}

	for (int i = 0; i < MAX_POSTS_NR; i++) {
		/* Iteram in ordine prin vectorul de postari */
		g_tree *cur_tree = tree_vector[i];
		if (!cur_tree)
			continue;
		/* Daca postarea nu a fost facuta mergem mai departe */

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

/* Structura pe care o va avea un element din vectorul de common-group */
typedef struct {
	/* Numarul de legaturi cu ceilalti useri din vectorul de common-group */
	int nr_connect;
	/* ID-ul userului*/
	unsigned int id;
} id_connections;

/* Structura pe care o va avea vectorul de common-group */
typedef struct {
	/* Dimensiunea vectorului */
	int size;
	/* Vectorul in sine */
	id_connections *data;
} group_vector;

/** @brief Functie de swap pentru doua elemente de tip id_connections
 *  din vectorul de common-group
 *  @param a: Primul element
 *  @param b: Al doilea element
 */
static void swap_group_data(id_connections *a, id_connections *b) {
	id_connections aux = *a;
	*a = *b;
	*b = aux;
}

/** @brief Functie de sortare a vectorului de common-group
 *  Daca numarul de conexiuni este acelasi, sortam descrescator dupa ID
 *  @param data: Vectorul de common-group
 *  @param size: Dimensiunea vectorului
 */
static void sort_group_descrescator_nr_connect(id_connections *data, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (data[i].nr_connect < data[j].nr_connect) {
				swap_group_data(&data[i], &data[j]);
			} else if (data[i].nr_connect == data[j].nr_connect &&
					   data[i].id < data[j].id) {
				swap_group_data(&data[i], &data[j]);
			}
		}
	}
}

/** @brief Functia face parsarea si imi afiseaza cel mai mare grup de prieteni
 *  care îl conține pe un anumit user
 *  @param graph: Graful de prieteni
 */
void clique(list_graph_t *graph) {
	char *name = strtok(NULL, "\n ");
	unsigned int user_id = get_user_id(name);

	/* Numarul de prieteni ai userului primit de la input */
	int nr_friends = graph->neighbors[user_id]->size;

	/* Vectorul de common-group */
	/* Alocam memorie pentru nr_friends + 1 elemente deoarece adaugam in vector
	 * si userul in sine, pe langa prietenii lui */
	group_vector *group = malloc(sizeof(group_vector));
	group->data = calloc(nr_friends + 1, sizeof(id_connections));

	group->size = nr_friends + 1;

	/* Adaugam in vector userul in sine si prietenii lui*/
	int k = 0;
	for (unsigned int i = 0; i < MAX_PEOPLE; i++) {
		if (lg_has_edge(graph, user_id, i) == 1 || i == user_id) {
			/* Tinem minte si ID-urile pentru afisare la final, si pentru a
			 * sorta userii dupa ID asa cum ni se cere */
			group->data[k].id = i;

			/* Initializam numarul de conexiuni */
			group->data[k].nr_connect = 0;
			k++;
		}
	}

	/* Iteram prin toate elementele din vector si adaugam conexiunile */
	for (int i = 0; i < nr_friends + 1; i++)
		for (int j = 0; j < nr_friends + 1; j++)
			if (lg_has_edge(graph, group->data[i].id, group->data[j].id) == 1)
				group->data[i].nr_connect++;

	/* Sortam vectorul descrescator ca sa pot scoate de la final.
	 * La final vor fi userii cu cele mai putine conexiuni asa ca aceia stim ca
	 * nu fac parte din common-group. */
	sort_group_descrescator_nr_connect(group->data, nr_friends + 1);

	/* Regula prin care stim cand ne vom opri din a scoate elemente din vector
	 * este ca la fiecare pas, daca numarul de conexiuni ale elementului pe care
	 * vrem sa-l scoatem este diferit de numarul de noduri ramase - 1 inseamna
	 * ca acel grup nu satisface conditia de graf complet, conditie necesara
	 * pentru common-group.
	 * Ne putem opri atunci deoarece noi vrem cel mai mare grup si pentru ca,
	 * fiind sortate elementele dupa numarul de conexiuni, restul sigur satisfac
	 * conditia */
	while (group->data[nr_friends].nr_connect != group->size - 1) {
		/* Scoatem din vector userul cu cele mai putine conexiuni.
		 * Scadem numarul conexiunilor userilor care erau conectati cu el
		 * deoarece nodul scos nu face parte din common-group deci conexiunea
		 * lui nu trebuie luata in calcul */
		for (int i = 0; i < nr_friends; i++) {
			int friend_id = group->data[i].id;
			if (lg_has_edge(graph, group->data[nr_friends].id, friend_id) == 1)
				group->data[i].nr_connect--;
		}
		nr_friends--;

		/* Sortam din nou vectorul dupa numarul de conexiuni si ID */
		sort_group_descrescator_nr_connect(group->data, nr_friends + 1);

		group->size--;
	}

	/* Sortam vectorul ramas crescator dupa ID */
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

