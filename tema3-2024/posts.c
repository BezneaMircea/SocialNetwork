#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "structuri.h"
#include "posts.h"

int id_increase() {
	static int id = 0;
	id++;
	return id;
}

void handle_input_posts(char *input, g_tree **tree_vector)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create")) {	
		char *name = strtok(NULL, "\n ");
		char *title = strtok(NULL, "\n");
		int id = id_increase();
		create_post(name, title, &tree_vector[id], id);
		printf("Created %s for %s\n", title, name);
	}
	else if (!strcmp(cmd, "repost")) {
		char *name = strtok(NULL, "\n ");
		int post_id = atoi(strtok(NULL, "\n "));
		char *repost_id_string = strtok(NULL, "\n ");

		int repost_id;

		tree_data data_to_add;
		data_to_add.user_id = get_user_id(name);
		data_to_add.id = id_increase();
		data_to_add.nr_likes = 0;
		data_to_add.likes = (int *)calloc(MAX_PEOPLE, sizeof(int));
		data_to_add.post_name = NULL;
		data_to_add.parrent_id = post_id;

		if (repost_id_string) {
			repost_id = atoi(repost_id_string);
			data_to_add.parrent_id = repost_id;
		}

		g_tree_insert(tree_vector[post_id], &data_to_add);
		printf("Created Repost #%d for %s\n", data_to_add.id, name);
		// print_sub_tree(tree_vector[post_id]->root);
		// printf("\n");
	}
		// TODO: Add function
	else if (!strcmp(cmd, "common-repost"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "like"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "ratio"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "delete"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "get-reposts")) {
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
		
		print_sub_tree(sub_tree_root, was_it_a_repost);
	}
		// TODO: Add function
	else if (!strcmp(cmd, "get-likes"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}