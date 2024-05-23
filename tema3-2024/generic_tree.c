/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */

#include "structuri.h"
#include "posts.h"

/** @brief Functia creeaza un nod
 *  @param data: Datele pe care le va contine nodul
 *  @param max_children_nr: Nr maxim de copii ai nodului
 *  @param data_size: Dimensiunea datelor copiate
 *  @return Returneaza un nod al arborelui generic
 */
static g_tree_node *
g_tree_create_node(void *data, unsigned int max_children_nr,
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
 *  @param compare:	Pointer spre o functie de comparare a nodurilor din arbore.
 *					Intoarce 1 daca primul nod este mai mare, 0 daca sunt egale,
 *					-1 daca al doilea nod este mai mare
 *  @param max_children_nr: Numarul maxim de copii ai unui nod
 *  @param free_data: Functie de eliberare a datelor dintr-un nod
 *					  daca se trimite NULL nu are niciun efect
 *  @return Returneaza arborele generic
 */
g_tree *g_tree_create(unsigned int data_size,
					  int (*compare)(g_tree_node *, g_tree_node *),
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

/** @brief Funcita cauta recursiv nodul unde ar trebui sa fie adaugat copilul
 *		   node_to_get. ATENTIE! Functia compare nu este obligatoriu sa
 *		   fie comutativa. Asa ca pentru a spori genericitate, vom considera
 *		   mereu ca node_to_add, node_to_remove, node_to_print, etc. O sa fie
 *		   al doilea nod din functia compare. Cu alte cuvinte, primul este
 *		   parintele. In aceasta functie parcurgerea se face evident de sus
 *		   in jos
 *  @param node: Nodul curent
 *  @param node_to_get: Nodul ce contine in void *data o informatie adecavata
 *						astfel incat functia compare sa il poata recunoaste in
 *						arbore
 *  @param compare: Pointer spre o functie de comparare a nodurilor din arbore.
 *					Intoarce 1 daca primul nod este mai mare, 0 daca sunt egale,
 *					-1 daca al doilea nod este mai mare
 *  @return Returneaza nodul corespunzator, conform functiei compare
 */
g_tree_node *get_node(g_tree_node *node, g_tree_node *node_to_get,
					  int (*compare)(g_tree_node *, g_tree_node *))
{
	g_tree_node *node_to_return;

	if (!compare(node, node_to_get))
		return node;
	/* La egalitate intoarcem nodul */

	if (!node->nr_children)
		return NULL;
	/* Nu mai are copii deci intoarcem NULL */

	if (compare(node, node_to_get) < 0) {
		/* Datorita proprietatii arborelui nodurile mai mari decat nodul cautat
		 * nu ne intereseaza
		 */
		for (int i = 0; i < node->nr_children; i++)
			if (compare(node->children[i], node_to_get) <= 0) {
				/* Ne intereseaza doar copii mai mici sau egali */
				node_to_return = get_node(node->children[i], node_to_get,
										  compare);
				if (node_to_return)
					return node_to_return;
				/* Daca functia returneaza altceva decat NULL ne intoarcem
				 * cu nodul gasit la portiunea din cod unde a fost apelata
				 * functia */
			}
	}

	return NULL;
	/* Intoarcem NULL daca nu am gasit nodul cautat pe subarborele curent */
}

/** @brief Functia insereaza in arbore un nod ce contine informatia data.
 *		   Inserarea se face pe baza raspunsului functiei compare. Daca aceasta
 *		   intoarce 0, acele va fi nodul de unde va mai pleca o legatura.
 *  @param tree: Arborele in care vrem sa adaugam
 *  @param data: Datele pe care vrem sa le inseram in arbore.
 */
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
		/* Daca inseram la radacina */
	}

	if (tree->compare(tree->root, node_to_add) > 0) {
		printf("Nu se poate adauga\n");
		tree->free_data(node_to_add->data);
		free(node_to_add->data);
		free(node_to_add->children);
		free(node_to_add);
		/* Daca inserarea este imposibila
		 * (nu se respecta proprietatea arborelui)*/
		return;
	}

	g_tree_node *where_to_add = get_node(tree->root, node_to_add,
										 tree->compare);
	if (!where_to_add) {
		printf("Reposting what?\n");
		/* Daca nu am gasit unde trebuie sa adaugam */
		return;
	}

	where_to_add->children[where_to_add->nr_children] = node_to_add;
	where_to_add->nr_children++;
	/* Adaugam nodul nou creat la finalul vectorului de copii */
}

/** @brief Interschimba doi pointeri intre ei
 *  @param node_a: Primul nod
 *  @param node_b: Al doilea nod
 */
static
void swap_nodes(g_tree_node **node_a, g_tree_node **node_b) {
	g_tree_node *aux;
	aux = *node_a;
	*node_a = *node_b;
	*node_b = aux;
}

/** @brief Strica legatura dintre parintele nod si al i-lea copil al sau
 *		   Legatura este acum spre NULL
 *  @param node: Nodul parinte
 *  @param i: Indicele nodului copil
 */
static
void remove_kid(g_tree_node *node, int i) {
	for (int j = i; j < node->nr_children - 1; j++)
		swap_nodes(&node->children[j], &node->children[j + 1]);
	/* Mutam copilul la final */
	node->nr_children--;
	node->children[node->nr_children] = NULL;
	/* Acum in vector pozitia acestuia pointeaza spre NULL
	 * pentru a nu avea probleme de tip invalid read/write
	 * ulterior */
}

/** @brief Functia distruce legatura dintre doua noduri parinte-copil din arbore
 *		   Functia este apelata recursiv pentru a obtine rezultatul dorit
 *  @param node: nodul curent
 *  @param node_to_remove: un nod ce contine informatii curespunzatoare cu
 *						   nodul pe care vrem sa il eliberam
 *  @param compare: Functia de comparare a nodurilor
 *  @return intoarce nodul parinte
 */
static
g_tree_node *destroy_edge(g_tree_node *node, g_tree_node *node_to_remove,
						  int (*compare)(g_tree_node *, g_tree_node *))
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
			/* Daca l-am gasit il intoarcem si stricam legatura */
		} else if (cmp_res == -1) {
			/* Daca copilul este mai mic decat data */
			node_to_return = destroy_edge(node->children[i], node_to_remove,
										  compare);
			if (node_to_return)
				return node_to_return;
		}
		/* Cazul in care copilul este mai mare nu ne intereseaza */
	}

	return NULL;
}

/** @brief Functia distruge legatura dintre parintele ce contine nodul
 *		   cu informatia data si acesta. Facand ca parintele sa pointeze
 *		   spre NULL. Memoria este eliberata de callee
 *  @param tree: Arborele in care vrem sa distrugem legatura
 *  @param data_to_remove: Nodul pe care vrem sa il eliminam din arbore
 *  @return Functia intoarce nodul ce contine informatia data. Cel care
 *			a fost eliminat din arbore. Practic radacina subarborelui
 *			eliminat.
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
		/* Cazul in care vrem sa eliminam chiar radacina arborelui */
	}

	return destroy_edge(node_to_return, node_to_remove, tree->compare);
}

/** @brief Functia elibereaza memoria consumata de tot subarborele care pleaca
 *		   de la node, inclusiv node
 *  @param node: radacina subarborelui a carui memorie vrem sa o eliberam.
 *  @param free_data: Pointer spre o functie care elibereaza memoria din campul
 *					  data in cazul unei structuri complexe. NU memoria alocata
 *					  pentru void *data. Daca se trimite NULL, nu are efect
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
}

/** @brief Functia elibereaza toata memoria consumata (de nodurile arborelui,
 *		   cat si memoria consumata de arbore insusi). Si face ca acesta sa
 *		   pointeze spre NULL ulterior
 *  @param tree: adresa arborelui a carui memorie vrem sa o eliberam.
 */
void purge_g_tree(g_tree **tree)
{
	g_tree *tree_to_remove = *tree;
	clear_tree(tree_to_remove->root, tree_to_remove->free_data);
	free(tree_to_remove);

	*tree = NULL;
}
