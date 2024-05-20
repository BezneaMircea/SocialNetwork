#include "posts.h"

void free_data(void *data) {
	free(((tree_data *)data)->post_name);
	free(((tree_data *)data)->likes);
}

int compare(void *data_a, void *data_b) {
	int node_id = ((tree_data *)(((g_tree_node *)data_a)->data))->id; /// id-ul
	int dad_id = ((tree_data *)(((g_tree_node *)data_b)->data))->parrent_id; /// id-ul lui tata

	if (node_id > dad_id)
		return 1;

	if (node_id < dad_id)
		return -1;

	return 0;
}

void create_post(char *name, char *titlu, g_tree **tree, int id) {

	*tree = g_tree_create(sizeof(tree_data), compare, MAX_CHILD_NR, free_data);

	tree_data data_to_insert;

	data_to_insert.id = id;
	data_to_insert.user_id = get_user_id(name);
	data_to_insert.parrent_id = 0;
	data_to_insert.nr_likes = 0;
	data_to_insert.likes = (int *)calloc(MAX_PEOPLE, sizeof(int));

	data_to_insert.post_name = (char *)malloc(MAX_TITLE_LEN);
    strncpy(data_to_insert.post_name, titlu, MAX_TITLE_LEN);	

	/// add more shit if needed
	g_tree_insert(*tree, &data_to_insert);
}