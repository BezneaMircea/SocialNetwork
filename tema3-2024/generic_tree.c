#include "structuri.h"
#include "posts.h"

/** @brief Functia creeaza un nod
 *  @param data: Datele pe care le va contine nodul
 *  @param max_children_nr: Nr maxim de copii ai nodului
 *  @param data_size: Dimensiunea datelor copiate
 *  @return Returneaza un nod al arborelui generic
 */
static g_tree_node *
g_tree_create_node(void *data, unsigned max_children_nr,
				   unsigned int data_size)
{
	g_tree_node *node = malloc(sizeof(g_tree_node));
	DIE(!node, "Eroare la alocare\n");

	node->nr_children = 0;
	node->children = malloc(max_children_nr * sizeof(g_tree_node *));
	DIE(!node->children, "Eroare la alocare\n");

	node->data = malloc(data_size);
	DIE(!node->data, "Eroare la alocare\n");
	memcpy(node->data, data, data_size);

	return node;
}

/** @brief Functia creeaza un arbore generic
 *  @param data_size: Dimensiunea datelor stocate in arbore
 *  @param compare: Pointer spre o functie de comparare a nodurilor din arbore.
 * 					Intoarce 1 daca primul nod este mai mare, 0 daca sunt egale,
 * 					-1 daca al doilea nod este mai mare
 *  @param max_children_nr: Numarul maxim de copii ai unui nod
 *  @param free_data: Functie de eliberare a datelor dintr-un nod
 * 					  daca se trimite NULL nu are niciun efect
 *  @return Returneaza arborele generic
 */
g_tree *g_tree_create(unsigned int data_size, int (*compare)(void *, void *),
					  unsigned int max_children_nr, void (*free_data)(void *))
{
	g_tree *tree = malloc(sizeof(g_tree));
	DIE(!tree, "Eroare la alocare\n");

	tree->compare = compare;
	tree->data_size = data_size;
	tree->max_children_nr = max_children_nr;
	tree->free_data = free_data;
	tree->root = NULL;

	return tree;
}

/** @brief Funcita cauta recursiv nodul unde trebuie sa adauge copilul
 *		   node_to_add. IN FUNCTIA COMPARE PARINTELE E MEREU PRIMUL
 *  @param node: Nodul curent
 *  @param node_to_add: Nodul pe care vrem sa il adaugam
 *  @param compare: Pointer spre o functie de comparare a nodurilor din arbore.
 * 					Intoarce 1 daca primul nod este mai mare, 0 daca sunt egale,
 * 					-1 daca al doilea nod este mai mare
 */
g_tree_node *get_node(g_tree_node *node, g_tree_node *node_to_add,
					  int (*compare)(void *, void *))
{
	g_tree_node *node_to_return;

	if (!compare(node, node_to_add))
		return node;

	if (!node->nr_children)
		return NULL;

	if (compare(node, node_to_add) < 0) {
		for (int i = 0; i < node->nr_children; i++)
			if (compare(node->children[i], node_to_add) <= 0) {
				node_to_return = get_node(node->children[i], node_to_add,
										  compare);
				if (node_to_return)
					return node_to_return;
			}
	}

	return NULL;
}

void g_tree_insert(g_tree *tree, void *data) {
	if (!tree) {
		printf("Create a tree\n");
		return;
	}

	g_tree_node *node_to_add = g_tree_create_node(data, tree->max_children_nr,
												  tree->data_size);

	if (!tree->root) {
		tree->root = node_to_add;
		return;
	}

	/// Urmeaza Logica de la repost

	if (tree->compare(tree->root, node_to_add) > 0) {
		printf("Nu se poate adauga\n");
		tree->free_data(node_to_add->data);
		free(node_to_add->data);
		free(node_to_add->children);
		free(node_to_add);

		return;
	}

	g_tree_node *where_to_add = get_node(tree->root, node_to_add,
										 tree->compare);
	if (!where_to_add) {
		printf("Reposting what?\n");
		return;
	}

	where_to_add->children[where_to_add->nr_children] = node_to_add;
	where_to_add->nr_children++;
}

static
void swap_nodes(g_tree_node **node_a, g_tree_node **node_b) {
	g_tree_node *aux;
	aux = *node_a;
	*node_a = *node_b;
	*node_b = aux;
}

static
void remove_kid(g_tree_node *node, int i) {
	for (int j = i; j < node->nr_children - 1; j++)
		swap_nodes(&node->children[j], &node->children[j + 1]);
	node->nr_children--;
	node->children[node->nr_children] = NULL;
}

static
g_tree_node *destroy_edge(g_tree_node *node, g_tree_node *node_to_remove,
						  int (*compare)(void *, void *))
{
	g_tree_node *node_to_return;
	int cmp_res;

	if (!node)
		return NULL;

	if (!node->children)
		return NULL;

	for (int i = 0; i < node->nr_children; i++) {
		cmp_res = compare(node->children[i], node_to_remove);
		if (!cmp_res) {
			node_to_return = node->children[i];
			remove_kid(node, i);
			return node_to_return;
		} else if (cmp_res == -1) {
			/// daca copilul este mai mic decat data
			node_to_return = destroy_edge(node->children[i], node_to_remove, compare);
			if (node_to_return)
				return node_to_return;
		}
	}

	return NULL;
}

/** @brief Functia distruge legatura dintre parintele ce contine nodul
 * 		   cu informatia data si acesta. Facand ca parintele sa pointeze
 * 		   spre NULL
 *  @param tree: Arborele in care vrem sa distrugem legatura
 *  @param data_to_remove: Nodul pe care vrem sa il eliminam din arbore
 *  @return Functia intoarce nodul ce contine informatia data. Cel care
 * 			a fost eliminat din arbore.
 */
g_tree_node *remove_g_subtree(g_tree *tree, g_tree_node *node_to_remove) {
	if (!tree)
		return NULL;

	if (!tree->root)
		return NULL;
	
	g_tree_node *node_to_return = tree->root;

	if (!tree->compare(tree->root, node_to_remove)) {
		tree->root = NULL;
		return node_to_return;
	}
	/// Am tratat cazul in care vrem sa eliminam o postare

	return destroy_edge(node_to_return, node_to_remove, tree->compare);
}

/** @brief Functia elibereaza memoria consumata de tot subarborele care pleaca
 * 		   de la node;
 *  @param node: radacina subarborelui a carui memorie vrem sa o eliberam.
 *  @param free_data: Pointer spre o functie care elibereaza memoria din campul
 * 					  data in cazul unei structuri complexe. NU memoria alocata
 * 					  pentru void *data. Daca se trimite NULL, nu are efect
 */
void clear_tree(g_tree_node *node, void (*free_data)(void *))
{
	if (!node)
		return;

	for (int i = 0; i < node->nr_children; i++)
		clear_tree(node->children[i], free_data);

	if (free_data)
		free_data(node->data);
	free(node->data);
	free(node->children);
	free(node);

	return;
}

/** @brief Functia elibereaza toata memoria consumata (de nodurile arborelui,
 *		   cat si memoria consumata de arborele insusi).
 *  @param tree: adresa arborelui a carui memorie vrem sa o eliberam.
 */
void purge_g_tree(g_tree **tree)
{
	g_tree *tree_to_remove = *tree;
	clear_tree(tree_to_remove->root, tree_to_remove->free_data);
	free(tree_to_remove);

	*tree = NULL;
}

static
void bfs (g_tree_node *node, g_tree_node **parent, int *vizitat, int *dist) {
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
	int *vizitat = calloc(MAX_PEOPLE, sizeof(int));
	int *dist = calloc(MAX_PEOPLE, sizeof(int));
	bfs(tree->root, parent, vizitat, dist);

	g_tree_node *ancestor = get_that_ancestor(tree, node1, node2, parent, dist);
	
	free(parent);
	free(vizitat);
	free(dist);
	
	return ancestor;

	// trebuie sa dau free la parents
	
}