#include "posts.h"

/** @brief Functie trimisa ca parametru folosita pentru eliberarea
 * 		   memoriei consumata de ce se afla in void *data intr-un nod din arbore
 * 	@param data: Pointer spre void *data ce trebuie eliberat
 */
void free_data(void *data) {
	free(((tree_data *)data)->post_name);
	free(((tree_data *)data)->likes);
}

/** @brief Functia de comparare intre doua noduri. Necomutativa. Daca primul
 * 		   nod este parintele celui de al doilea returnam 0. Daca este mai mare
 * 		   intoarcem 1 daca este mai mic -1
 *  @param data_a: Nodul parinte
 *  @param data_b: Nodul copil
 *  @return 0 le egalitate 1 daca data_a > data_b si -1 daca data_a < data_b
 */
int compare(void *data_a, void *data_b) {
	int node_id = ((tree_data *)(((g_tree_node *)data_a)->data))->id; /// id-ul
	int dad_id = ((tree_data *)(((g_tree_node *)data_b)->data))->parrent_id; /// id-ul lui tata

	if (node_id > dad_id)
		return 1;

	if (node_id < dad_id)
		return -1;

	return 0;
}

/** @brief Functia creeaza o postare cu id-ul id in vectorul de copaci
 * 		   De asemenea, in aceasta functie facem si parsarea inputului
 *  @param tree: Vectorul de copaci.
 *  @param id: Id-ul postarii pe care vrem sa o facem postarea.
 */
void create_post(g_tree **tree, int id) {

	char *name = strtok(NULL, "\n ");
	char *title = strtok(NULL, "\n");
	*tree = g_tree_create(sizeof(tree_data), compare, MAX_CHILD_NR, free_data);

	tree_data data_to_insert;

	data_to_insert.id = id;
	data_to_insert.user_id = get_user_id(name);
	data_to_insert.parrent_id = 0;
	data_to_insert.nr_likes = 0;
	data_to_insert.likes = (int *)calloc(MAX_PEOPLE, sizeof(int));
	DIE(!data_to_insert.likes, "Eroare la alocare\n");

	data_to_insert.post_name = (char *)malloc(MAX_TITLE_LEN);
	DIE(!data_to_insert.post_name, "Eroare la alocare\n");

    strncpy(data_to_insert.post_name, title, MAX_TITLE_LEN);	

	g_tree_insert(*tree, &data_to_insert);

	printf("Created %s for %s\n", title, name);
}

/** @brief Functia creeaza un repost. Se ocupa si cu parsarea
 *  @param tree_vector: Vectorul de copaci
 *  @param id: Id-ul repostului pe care vrem sa il facem
 */ 
void repost(g_tree **tree_vector, int id) {
	char *name = strtok(NULL, "\n ");
	int post_id = atoi(strtok(NULL, "\n "));
	char *repost_id_string = strtok(NULL, "\n ");

	int repost_id;

	tree_data data_to_add;
	data_to_add.user_id = get_user_id(name);
	data_to_add.id = id;
	data_to_add.nr_likes = 0;
	data_to_add.likes = (int *)calloc(MAX_PEOPLE, sizeof(int));
	DIE(!data_to_add.likes, "Eroare la alocare\n");
	data_to_add.post_name = NULL;
	data_to_add.parrent_id = post_id;

	if (repost_id_string) {
		repost_id = atoi(repost_id_string);
		data_to_add.parrent_id = repost_id;
	}

	g_tree_insert(tree_vector[post_id], &data_to_add);
	printf("Created repost #%d for %s\n", data_to_add.id, name);
}

/** @brief Functia printeaza subarborele cu radacina nod. In formatul cerut
 *  @param node: radacina subarborelui
 *  @param was_it_a_repost: 1 daca a fost repost, 0 daca a fost post
 */
void print_sub_tree(g_tree_node *node, int was_it_a_repost) {
	if (!node)
		return;

	if (!was_it_a_repost) {
		printf("%s - Post by %s\n", ((tree_data *)(node->data))->post_name,
			   get_user_name(((tree_data *)(node->data))->user_id));
	} else {
		printf("Repost #%d by %s\n", ((tree_data *)(node->data))->id,
			   get_user_name(((tree_data *)(node->data))->user_id));
	}
	for (int i = 0; i < node->nr_children; i++)
		print_sub_tree(node->children[i], 1);
}


/** @brief Functia faca parsarea datelor si da un like corespunzator.
 *  @param tree_data: Vectorul de copaci
 */
void like(g_tree **tree_vector) {
	char *name = strtok(NULL, "\n ");
	int post_id = atoi(strtok(NULL, "\n "));
	char *repost_id_string = strtok(NULL, "\n ");


	g_tree_node look_for_node_to_like;
	look_for_node_to_like.data = malloc(sizeof(tree_data));
	DIE(!look_for_node_to_like.data, "Eroare la alocare\n");

	((tree_data *)(look_for_node_to_like.data))->parrent_id = post_id;

	int repost_id;
	int was_it_a_repost = 0;
	if (repost_id_string) {
		repost_id = atoi(repost_id_string);
		((tree_data *)(look_for_node_to_like.data))->parrent_id = repost_id;
		was_it_a_repost = 1;
	}

	g_tree_node *node_to_like = get_node(tree_vector[post_id]->root,
										&look_for_node_to_like,
										tree_vector[post_id]->compare);

	unsigned int like_user_id = get_user_id(name);
	char *post_name = ((tree_data *)(tree_vector[post_id]->root->data))->post_name;

	if (((tree_data *)(node_to_like->data))->likes[like_user_id] == 0) {
		((tree_data *)(node_to_like->data))->nr_likes++;
		((tree_data *)(node_to_like->data))->likes[like_user_id] = 1;
		if (was_it_a_repost)
			printf("User %s liked repost %s\n", name, post_name);
		else
			printf("User %s liked post %s\n", name, post_name);
	} else {
		((tree_data *)(node_to_like->data))->nr_likes--;
		((tree_data *)(node_to_like->data))->likes[like_user_id] = 0;
		if (was_it_a_repost)
			printf("User %s unliked repost %s\n", name, post_name);
		else
			printf("User %s unliked post %s\n", name, post_name);
	}
	
	free(look_for_node_to_like.data);
}

/** @brief Functia face parsarea datelor si afiseaza nr de likeuri
 *  @param tree_vector: Vectorul de copaci 
 */
void get_likes(g_tree **tree_vector) {
	int post_id = atoi(strtok(NULL, "\n "));
	char *repost_id_string = strtok(NULL, "\n ");

	g_tree_node look_for_node_likes;
	look_for_node_likes.data = malloc(sizeof(tree_data));
	DIE(!look_for_node_likes.data, "Eroare la alocare\n");

	((tree_data *)(look_for_node_likes.data))->parrent_id = post_id;

	int repost_id;
	int was_it_a_repost = 0;
	if (repost_id_string) {
		repost_id = atoi(repost_id_string);
		((tree_data *)(look_for_node_likes.data))->parrent_id = repost_id;
		was_it_a_repost = 1;
	}

	g_tree_node *node_likes = get_node(tree_vector[post_id]->root,
									   &look_for_node_likes,
									   tree_vector[post_id]->compare);
	
	if (was_it_a_repost)
		printf("Repost #%d has %d likes\n", repost_id,
			   ((tree_data *)(node_likes->data))->nr_likes);
	else
		printf("Post %s has %d likes\n",
			   ((tree_data *)(node_likes->data))->post_name,
			   ((tree_data *)(node_likes->data))->nr_likes);
	
	free(look_for_node_likes.data);
}

/** @brief Functia afiseaza ierarhia de reposturi si face parsarea comenzii
 *  @param tree_vector: Vectorul de copaci
 */
void get_reposts(g_tree **tree_vector) {
	int post_id = atoi(strtok(NULL, "\n "));
	char *repost_id_string = strtok(NULL, "\n ");

	g_tree_node node_to_get_repost_from;
	node_to_get_repost_from.data = malloc(sizeof(tree_data));
	DIE(!node_to_get_repost_from.data, "Eroare la alocare\n");

	((tree_data *)(node_to_get_repost_from.data))->parrent_id = post_id;

	int repost_id;
	int was_it_a_repost = 0;
	if (repost_id_string) {
		repost_id = atoi(repost_id_string);
		((tree_data *)(node_to_get_repost_from.data))->parrent_id = repost_id;
		was_it_a_repost = 1;
	}

	g_tree_node *sub_tree_root = get_node(tree_vector[post_id]->root,
										  &node_to_get_repost_from,
										  tree_vector[post_id]->compare);

	free(node_to_get_repost_from.data);
	print_sub_tree(sub_tree_root, was_it_a_repost);
}


/** @brief Functia sterge toata ierarhia de postari/repostari si face parsarea
 *  @param tree_vector: Vectorul de copaci
 */
void delete(g_tree **tree_vector) {
	int post_id = atoi(strtok(NULL, "\n "));
	char *repost_id_string = strtok(NULL, "\n ");

	g_tree_node node_to_delete_from;
	node_to_delete_from.data = malloc(sizeof(tree_data));
	DIE(!node_to_delete_from.data, "Eroare la alocare\n");

	((tree_data *)(node_to_delete_from.data))->parrent_id = post_id;

	int repost_id;
	int was_it_a_repost = 0;
	if (repost_id_string) {
		repost_id = atoi(repost_id_string);
		((tree_data *)(node_to_delete_from.data))->parrent_id = repost_id;
		was_it_a_repost = 1;
	}

	g_tree_node *sub_tree_root = remove_g_subtree(tree_vector[post_id],
										  		  &node_to_delete_from);

	if (was_it_a_repost) {
		printf("Deleted repost #%d of post %s\n", repost_id,
			   ((tree_data *)(tree_vector[post_id]->root->data))->post_name);
	} else {
		printf("Deleted %s\n", ((tree_data *)(sub_tree_root->data))->post_name);
	}

	clear_tree(sub_tree_root, tree_vector[post_id]->free_data);
	free(node_to_delete_from.data);
}

/** @brief Face ratio-ul si parsarea
 *  @param tree_vector: Vectorul de copaci
 */
void ratio(g_tree **tree_vector) {
	int post_id = atoi(strtok(NULL, "\n "));

	g_tree *tree = tree_vector[post_id];
	g_tree_node *root_node = tree->root;

	int max_likes = ((tree_data *)(root_node->data))->nr_likes;
	int og_post_id = ((tree_data *)(root_node->data))->id;

	int post_that_ratioed = og_post_id;
	for (int i = 0; i < root_node->nr_children; i++) {
		int cur_likes = ((tree_data *)(root_node->children[i]->data))->nr_likes;
		int cur_id = ((tree_data *)(root_node->children[i]->data))->id;
		if (cur_likes > max_likes)
			post_that_ratioed = cur_id;
	}
	
	if (post_that_ratioed == og_post_id) {
		printf("The original post is the highest rated\n");
	} else {
		printf("Post %d got ratio'd by repost %d\n", og_post_id,
			   post_that_ratioed);
	}
}

/** @brief Fac un BFS, calculez distanta de la radacina la fiecare nod si creez
 *		   un vector de parinti
 *  @param node: Radacina arborelui
 *  @param parent: Vector de parinti
 *  @param vizitat: Vector de vizitat
 *  @param dist: Vector de distante (nivelul fiecarui nod in arbore)
 */
static
void bfs(g_tree_node *node, g_tree_node **parent, int *vizitat, int *dist) {
	dist[((tree_data *)(node->data))->id] = 0;
	vizitat[((tree_data *)(node->data))->id] = 1;

	queue_t *queue = q_create(sizeof(g_tree_node *), MAX_PEOPLE);
	q_enqueue(queue, &node);

	while(!q_is_empty(queue)) {
		g_tree_node *current_node = *(g_tree_node **)q_front(queue);
		q_dequeue(queue);

		for (int i = 0; i < current_node->nr_children; i++) {
			if (!vizitat[((tree_data *)(current_node->children[i]->data))->id]) {
				vizitat[((tree_data *)(current_node->children[i]->data))->id] = 1;
				dist[((tree_data *)(current_node->children[i]->data))->id] = dist[((tree_data *)(current_node->data))->id] + 1;
				parent[((tree_data *)(current_node->children[i]->data))->id] = current_node;
				q_enqueue(queue, &current_node->children[i]);
			}
		}
	}

	q_free(queue);
	free(queue);
}

/** @brief Functia calculeaza cel mai apropiat stramos comun
 *  @param tree: Arborele
 *  @param node1: Nodul 1
 *  @param node2: Nodul 2
 *  @param parent: Vector de parinti
 *  @param dist: Vector de distante
 *  @return Returneaza nodul care este stramos comun
 */
static
g_tree_node *get_that_ancestor(g_tree *tree, g_tree_node *node1,
							   g_tree_node *node2, g_tree_node **parent,
							   int *dist)
{
	int dist1 = dist[((tree_data *)(node1->data))->id];
	int dist2 = dist[((tree_data *)(node2->data))->id];

	if (dist1 > dist2) {
		int d = dist1 - dist2;
		while (d > 0) {
			node1 = parent[((tree_data *)(node1->data))->id];
			d--;
		}
	} else {
		int d = dist2 - dist1;
		while (d > 0) {
			node2 = parent[((tree_data *)(node2->data))->id];
			d--;
		}
	}

	if (node1 == node2)
		return node1;

	if (tree->root == node1 || tree->root == node2)
			return tree->root;

	while (parent[((tree_data *)(node1->data))->id] != parent[((tree_data *)(node2->data))->id]) {
		if (tree->root == node1 || tree->root == node2)
			return tree->root;
		node1 = parent[((tree_data *)(node1->data))->id];
		node2 = parent[((tree_data *)(node2->data))->id];
	}
	return parent[((tree_data *)(node1->data))->id];
}

/** @brief Functia apeleaza bfs-ul si get_that_ancestor pentru a gasi cel mai 
 *		   apropiat stramos comun
 *  @param tree: Arborele
 *  @param node1: Nodul 1
 *  @param node2: Nodul 2
 *  @return Returneaza nodul care este stramos comun
 */
static 
g_tree_node *least_comm_ancestor(g_tree *tree, g_tree_node *node1,
								 g_tree_node *node2)
{
	if (!tree) {
		printf("Create a tree first\n");
		return NULL;
	}

	if (!node1 || !node2) {
		printf("Ancestor for NULL? Really?\n");
		return NULL;
	}

	if (!tree->root) {
		printf("Dude... Tree is empty, stop trying\n");
		return NULL;
	}

	if (!tree->root->nr_children) {
		printf("I have no kids!!!\n");
		return NULL;
	}

	if (tree->root == node1 || tree->root == node2)
		return tree->root;

	g_tree_node **parent = malloc(MAX_PEOPLE * sizeof(g_tree_node *));
	DIE(!parent, "Eroare la alocare\n");

	int *vizitat = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!vizitat, "Eroare la alocare\n");

	int *dist = calloc(MAX_PEOPLE, sizeof(int));
	DIE(!dist, "Eroare la alocare\n");

	bfs(tree->root, parent, vizitat, dist);

	g_tree_node *ancestor = get_that_ancestor(tree, node1, node2, parent, dist);
	
	free(parent);
	free(vizitat);
	free(dist);
	
	return ancestor;	
}

/** @brief Functia imi gaseste primul repost comun al doua reposturi
 *  @param tree_vector: Vectorul de copaci
 */
void common_repost(g_tree **tree_vector) {
	int post_id = atoi(strtok(NULL, "\n "));
	int repost_id1 = atoi(strtok(NULL, "\n "));
	int repost_id2 = atoi(strtok(NULL, "\n "));

	g_tree *tree = tree_vector[post_id];

	g_tree_node find_node1;
	find_node1.data = malloc(sizeof(tree_data));
	DIE(!find_node1.data, "Eroare la alocare\n");

	((tree_data *)(find_node1.data))->parrent_id = repost_id1;

	g_tree_node find_node2;
	find_node2.data = malloc(sizeof(tree_data));
	DIE(!find_node1.data, "Eroare la alocare\n");

	((tree_data *)(find_node2.data))->parrent_id = repost_id2;

	g_tree_node *node1 = get_node(tree->root, &find_node1, tree->compare);
	g_tree_node *node2 = get_node(tree->root, &find_node2, tree->compare);


	g_tree_node *ancestor = least_comm_ancestor(tree, node1, node2);

	if (!ancestor) {
		printf("No common repost found\n");
	} else {
		printf("The first common repost of %d and %d is %d\n", repost_id1,
			   repost_id2, ((tree_data *)(ancestor->data))->id);
	}
	
	free(find_node1.data);
	free(find_node2.data);
}