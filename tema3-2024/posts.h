#ifndef POSTS_H
#define POSTS_H

#define MAX_CHILD_NR 100
#define MAX_TITLE_LEN 280

#include "structuri.h"
#include "friends.h"
#include "users.h"
/**
 * Function that handles the calling of every command from task 2
 *
 * Please add any necessary parameters to the functions
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
void get_reposts(g_tree **tree_vector);
void repost(g_tree **tree_vector, int id);
void delete(g_tree **tree_vector);

#endif // POSTS_H
