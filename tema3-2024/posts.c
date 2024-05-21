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
		int id = id_increase();
		create_post(&tree_vector[id], id);
	}
	else if (!strcmp(cmd, "repost")) {
		int id = id_increase();
		repost(tree_vector, id);
	}
	else if (!strcmp(cmd, "common-repost"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "like"))
		like(tree_vector);
	else if (!strcmp(cmd, "ratio")) {
		ratio(tree_vector);
	}
		// TODO: Add function
	else if (!strcmp(cmd, "delete")) {
		delete(tree_vector);
	}
	else if (!strcmp(cmd, "get-likes"))
		get_likes(tree_vector);
	else if (!strcmp(cmd, "get-reposts")) {
		get_reposts(tree_vector);
	}

	free(commands);
}