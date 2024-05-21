#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "feed.h"
#include "users.h"
#include "posts.h"
#include "friends.h"

/** @brief Functie folosita pentru a incrementa si a intoarce id-ul
 *  @return Intoarce id-ul
 */
static
int id_increase(void) {
	static int id;
	id++;
	return id;
}

void handle_input_feed(char *input, g_tree **tree_vector, list_graph_t *graph)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "feed")) {
		feed(tree_vector, graph);
	} else if (!strcmp(cmd, "view-profile")) {
		(void)cmd;
		// TODO: Add function
	} else if (!strcmp(cmd, "friends-repost")) {
		(void)cmd;
		// TODO: Add function
	} else if (!strcmp(cmd, "common-groups")) {
		(void)cmd;
		// TODO: Add function
	} else if (!strcmp(cmd, "create")) {
		int id = id_increase();
		create_post(&tree_vector[id], id);
	} else if (!strcmp(cmd, "repost")) {
		int id = id_increase();
		repost(tree_vector, id);
	} else if (!strcmp(cmd, "common-repost")) {
		common_repost(tree_vector);
	} else if (!strcmp(cmd, "like")) {
		like(tree_vector);
	} else if (!strcmp(cmd, "ratio")) {
		ratio(tree_vector);
	} else if (!strcmp(cmd, "delete")) {
		delete(tree_vector);
	} else if (!strcmp(cmd, "get-likes")) {
		get_likes(tree_vector);
	} else if (!strcmp(cmd, "get-reposts")) {
		get_reposts(tree_vector);
	} else if (!strcmp(cmd, "add")) {
		add_friend(graph);
	} else if (!strcmp(cmd, "remove")) {
		remove_friend(graph);
	} else if (!strcmp(cmd, "suggestions")) {
		suggestions_friend(graph);
	} else if (!strcmp(cmd, "distance")) {
		distance_friend(graph);
	} else if (!strcmp(cmd, "common")) {
		common_friends(graph);
	} else if (!strcmp(cmd, "friends")) {
		how_many_friends(graph);
	} else if (!strcmp(cmd, "popular")) {
		most_popular(graph);
	}

	free(commands);
}
