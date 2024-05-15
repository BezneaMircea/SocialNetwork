#ifndef FRIENDS_H
#define FRIENDS_H

#define MAX_COMMAND_LEN 100
#define MAX_PEOPLE 550

#include "structuri.h"

/**
 * Function that handles the calling of every command from task 1
 *
 * Please add any necessary parameters to the functions
*/
void handle_input_friends(list_graph_t *graph, char *input);

void add_friend(list_graph_t *graph, char *name1, char *name2);

void remove_friend(list_graph_t *graph, char *name1, char *name2);

void distance_friend(list_graph_t *graph, char *name1, char *name2);

void most_popular(list_graph_t *graph, char *user);

#endif // FRIENDS_H
