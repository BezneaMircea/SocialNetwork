/**
 * The entrypoint of the homework. Every initialization must be done here
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.h"
#include "friends.h"
#include "posts.h"
#include "feed.h"

/**
 * Initializez every task based on which task we are running
*/
void init_tasks(void)
{
	#ifdef TASK_1

	#endif

	#ifdef TASK_2

	#endif

	#ifdef TASK_3

	#endif
}

/**
 * Entrypoint of the program, compiled with different defines for each task
*/
int main(void)
{
	init_users();
	init_tasks();

	char *input = (char *)malloc(MAX_COMMAND_LEN);

	list_graph_t *graph = lg_create(MAX_PEOPLE);
	g_tree **tree_vector = malloc(MAX_POSTS_NR * sizeof(g_tree *));
	DIE(!tree_vector, "Eroare la alocare\n");

	for (int i = 0; i < MAX_POSTS_NR; i++)
		tree_vector[i] = NULL;

	while (1) {
		char *command = fgets(input, MAX_COMMAND_LEN, stdin);

		// If fgets returns null, we reached EOF
		if (!command)
			break;

		#ifdef TASK_1
		handle_input_friends(input, graph);
		#endif

		#ifdef TASK_2
		handle_input_posts(input, tree_vector);
		#endif

		#ifdef TASK_3
		handle_input_feed(input, tree_vector, graph);
		#endif
	}

	purge_graph(&graph);
	free_users();
	free(input);

	for (int i = 0; i < MAX_POSTS_NR; i++)
		if (tree_vector[i])
			purge_g_tree(&tree_vector[i]);
	free(tree_vector);

	return 0;
}
