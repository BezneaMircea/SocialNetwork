/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */

#ifndef POSTS_H
#define POSTS_H

#include "../structures/structuri.h"
#include "../friends/friends.h"
#include "../users/users.h"

/** @brief Aceasta este structura pe care o va retine fiecare nod din arbore
 *  @param id: Id-ul postarii
 *  @param user_id: Id-ul celui care a facut postarea/repostarea
 *  @param parrent_id: Id-ul parintelui
 *  @param nr_likes: Nr de likeuri ale postarii/repostarii curente
 *  @param post_name: Numele postarii. Setat pe NULL daca acesta e un repost
 *  @param likes: Vector de frecventa. Daca likes[user_id] = 1 inseamna ca
 *				  userul cu user_id a dat like. Daca e 0 inseamna ca nu a dat
 *				  like, sau ca a dat like si apoi dislike
 */
typedef struct tree_data tree_data;
struct tree_data
{
	unsigned int id, user_id, parrent_id;
	int nr_likes;
	char *post_name;
	int *likes;
};

void handle_input_posts(char *input, g_tree **tree_vector);

void create_post(g_tree **tree, int id);

void like(g_tree **tree_vector);

void common_repost(g_tree **tree_vector);

void get_likes(g_tree **tree_vector);

void get_reposts(g_tree **tree_vector);

void repost(g_tree **tree_vector, int id);

void delete(g_tree **tree_vector);

void ratio(g_tree **tree_vector);

#endif // POSTS_H
