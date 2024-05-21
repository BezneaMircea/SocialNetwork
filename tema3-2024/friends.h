#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 500
#define MAX_PEOPLE 550

#include "structuri.h"

/**
 * Function that handles the calling of every command from task 1
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_friends(list_graph_t *graph, char *input);

void add_friend(list_graph_t *graph);

void remove_friend(list_graph_t *graph);

void suggestions_friend(list_graph_t *graph);

void common_friends(list_graph_t *graph);

void distance_friend(list_graph_t *graph);

void most_popular(list_graph_t *graph);

void how_many_friends(list_graph_t *graph);

#endif // FRIENDS_H
