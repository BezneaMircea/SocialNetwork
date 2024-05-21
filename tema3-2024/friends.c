#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "structuri.h"
#include "users.h"

/** @brief Aceasta functie face parsarea datelor pentru Task1
 *         si apeleaza functiile corespunzatoare acestora
 *  @param graph: Graful pe care vom executa comanda
 *  @param input: Comanda efectiva.
 */
void handle_input_friends(list_graph_t *graph, char *input)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "add")) {
		char *name1 = strtok(NULL, "\n ");
		char *name2 = strtok(NULL, "\n ");
		add_friend(graph, name1, name2);

	} else if (!strcmp(cmd, "remove")) {
		char *name1 = strtok(NULL, "\n ");
		char *name2 = strtok(NULL, "\n ");
		remove_friend(graph, name1, name2);

	} else if (!strcmp(cmd, "suggestions")) {
		char *user = strtok(NULL, "\n ");
		suggestions_friend(graph, user);

	} else if (!strcmp(cmd, "distance")) {
		char *name1 = strtok(NULL, "\n ");
		char *name2 = strtok(NULL, "\n ");
		distance_friend(graph, name1, name2);

	} else if (!strcmp(cmd, "common")) {
		char *name1 = strtok(NULL, "\n ");
		char *name2 = strtok(NULL, "\n ");
		common_friends(graph, name1, name2);

	} else if (!strcmp(cmd, "friends")) {
		char *name = strtok(NULL, "\n ");
		int id = get_user_id(name);
		printf("%s has %d friends\n", name, graph->neighbors[id]->size);

	} else if (!strcmp(cmd, "popular")) {
		char *name = strtok(NULL, "\n ");
		most_popular(graph, name);
	}

	free(commands);
}
