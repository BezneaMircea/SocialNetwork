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

	if (!strcmp(cmd, "add"))
		add_friend(graph);
	else if (!strcmp(cmd, "remove"))
		remove_friend(graph);
	else if (!strcmp(cmd, "suggestions"))
		suggestions_friend(graph);
	else if (!strcmp(cmd, "distance"))
		distance_friend(graph);
	else if (!strcmp(cmd, "common"))
		common_friends(graph);
	else if (!strcmp(cmd, "friends"))
		how_many_friends(graph);
	else if (!strcmp(cmd, "popular"))
		most_popular(graph);

	free(commands);
}
