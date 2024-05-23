#include "feed.h"

void feed(g_tree **tree_vector, list_graph_t *graph) {
	char *name = strtok(NULL, "\n ");
	unsigned int user_id = get_user_id(name);

	int feed_size = atoi(strtok(NULL, "\n "));

	for (int i = MAX_POSTS_NR - 1; i >= 0 && feed_size; i--)
		if (tree_vector[i]) {
			unsigned int pers_id;
			pers_id = ((tree_data *)tree_vector[i]->root->data)->user_id;
			if (pers_id == user_id || lg_has_edge(graph, pers_id, user_id)) {
				char *pers_name = get_user_name(pers_id);
				printf("%s: %s\n", pers_name,
					   ((tree_data *)tree_vector[i]->root->data)->post_name);
				feed_size--;
			}
		}
}

void view_profile(g_tree **tree_vector) {
	char *name = strtok(NULL, "\n ");
	unsigned int user_id = get_user_id(name);

	for (int i = 0; i < MAX_POSTS_NR; i++) {
		g_tree *cur_tree = tree_vector[i];
		if (!cur_tree)
			continue;

		if (((tree_data *)cur_tree->root->data)->user_id == user_id) {
			printf("Posted: %s\n",
				   ((tree_data *)cur_tree->root->data)->post_name);
		}

		for (int i = 0; i < cur_tree->root->nr_children; i++) {
			unsigned int cur_id;
			cur_id = ((tree_data *)cur_tree->root->children[i]->data)->user_id;
			if (cur_id == user_id) {
				printf("Reposted: %s\n",
					   ((tree_data *)cur_tree->root->data)->post_name);
			}
		}
	}
}

void friends_repost(g_tree **tree_vector, list_graph_t *graph) {
	char *name = strtok(NULL, "\n ");
	unsigned int user_id = get_user_id(name);

	int post_id = atoi(strtok(NULL, "\n "));

	g_tree *post = tree_vector[post_id];

	for (int i = 0; i < post->root->nr_children; i++) {
		unsigned int pers_id;
		pers_id = ((tree_data *)post->root->children[i]->data)->user_id;
		char *pers_name = get_user_name(pers_id);
		if (lg_has_edge(graph, user_id, pers_id))
			printf("%s\n", pers_name);
	}
}

typedef struct {
	int size;
	int *data;
} vect;

static
vect *bron_kerbosch(list_graph_t *graph, vect *R, vect *P, vect *X) {
	
}

void clique(list_graph_t *graph) {
	char *name = strtok(NULL, "\n ");
	
}

