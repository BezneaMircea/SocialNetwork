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

	data_to_insert.post_name = (char *)malloc(MAX_TITLE_LEN);
    strncpy(data_to_insert.post_name, title, MAX_TITLE_LEN);	

	/// add more shit if needed
	g_tree_insert(*tree, &data_to_insert);

	printf("Created %s for %s\n", title, name);
}

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
	data_to_add.post_name = NULL;
	data_to_add.parrent_id = post_id;

	if (repost_id_string) {
		repost_id = atoi(repost_id_string);
		data_to_add.parrent_id = repost_id;
	}

	g_tree_insert(tree_vector[post_id], &data_to_add);
	printf("Created repost #%d for %s\n", data_to_add.id, name);
}

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

void like (g_tree **tree_vector) {
	(void)(tree_vector);
}

void get_likes (g_tree **tree_vector) {
	int post_id = atoi(strtok(NULL, "\n "));
	char *repost_id_string = strtok(NULL, "\n ");

	g_tree_node look_for_node_likes;
	look_for_node_likes.data = malloc(sizeof(tree_data));
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

void get_reposts (g_tree **tree_vector) {
	int post_id = atoi(strtok(NULL, "\n "));
	char *repost_id_string = strtok(NULL, "\n ");

	g_tree_node node_to_get_repost_from;
	node_to_get_repost_from.data = malloc(sizeof(tree_data));
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

void delete(g_tree **tree_vector) {
	int post_id = atoi(strtok(NULL, "\n "));
	char *repost_id_string = strtok(NULL, "\n ");

	g_tree_node node_to_delete_from;
	node_to_delete_from.data = malloc(sizeof(tree_data));
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