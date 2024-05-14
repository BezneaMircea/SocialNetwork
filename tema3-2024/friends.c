#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "structuri.h"
#include "users.h"

void handle_input_friends(char *input)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	list_graph_t *graph = lg_create(MAX_PEOPLE);

	if (!strcmp(cmd, "add")) {
		char *name1 = strtok(NULL, "\n ");
		char *name2 = strtok(NULL, "\n ");
		add_friend(graph, name1, name2);

	} else if (!strcmp(cmd, "remove")) {
		char *name1 = strtok(NULL, "\n ");
		char *name2 = strtok(NULL, "\n ");
		remove_friend(graph, name1, name2);

	} else if (!strcmp(cmd, "suggestions")) {
		char *name1 = strtok(NULL, "\n ");
		char *name2 = strtok(NULL, "\n ");
		distance_friend(graph, name1, name2);

	} else if (!strcmp(cmd, "distance")) {
		(void)cmd;
		// TODO: Add function
	} else if (!strcmp(cmd, "common")) {
		(void)cmd;
		// TODO: Add function
	} else if (!strcmp(cmd, "friends")) {
		(void)cmd;
		// TODO: Add function
	} else if (!strcmp(cmd, "popular")) {
		(void)cmd;
		// TODO: Add function
	}
}
