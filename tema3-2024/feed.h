#ifndef FEED_H
#define FEED_H

#include "structuri.h"
#include "friends.h"
#include "users.h"
#include "posts.h"

void handle_input_feed(char *input, g_tree * *tree_vector, list_graph_t *graph);
/// Asa arata bine pe codying style cu * * ;))))

void feed(g_tree **tree_vector, list_graph_t *graph);

#endif // FEED_H
