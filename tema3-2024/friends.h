#ifndef FRIENDS_H
#define FRIENDS_H

#include "structuri.h"

/**
 * Function that handles the calling of every command from task 1
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_friends(char *input, list_graph_t *graph);

void add_friend(list_graph_t *graph);

void remove_friend(list_graph_t *graph);

void suggestions_friend(list_graph_t *graph);

void common_friends(list_graph_t *graph);

void distance_friend(list_graph_t *graph);

void most_popular(list_graph_t *graph);

void how_many_friends(list_graph_t *graph);

#endif // FRIENDS_H
