/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */

#ifndef FEED_H
#define FEED_H

#include "../structures/structuri.h"
#include "../friends/friends.h"
#include "../users/users.h"
#include "../posts/posts.h"

void handle_input_feed(char *input, g_tree * *tree_vector, list_graph_t *graph);
/// Asa arata bine pe codying style cu * * ;))))

void feed(g_tree **tree_vector, list_graph_t *graph);

void view_profile(g_tree **tree_vector);

void friends_repost(g_tree **tree_vector, list_graph_t *graph);

void clique(list_graph_t *graph);

#endif // FEED_H
