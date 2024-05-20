#ifndef POSTS_H
#define POSTS_H

#define MAX_CHILD_NR 100
#define MAX_TITLE_LEN 280
#define MAX_NAME_LENGHT

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
void create_post(char *name, char *titlu, g_tree **tree, int id);
void print_sub_tree(g_tree_node *node, int was_it_a_repost);

#endif // POSTS_H
