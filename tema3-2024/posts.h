#ifndef POSTS_H
#define POSTS_H

/**
 * Function that handles the calling of every command from task 2
 *
 * Please add any necessary parameters to the functions
*/
// typedef struct tree_data tree_data;
// struct tree_data
// {
// 	unsigned int id, user_id;
// 	int nr_likes;
// 	int likes[MAX_PEOPLE];
// };

void handle_input_posts(char *input, g_tree **tree_vector);

#endif // POSTS_H
