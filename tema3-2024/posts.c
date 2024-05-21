#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "users.h"
#include "structuri.h"
#include "posts.h"

/** @brief Functie folosita pentru a incrementa si a intoarce id-ul
 *  @return Intoarce id-ul
 */
static
int id_increase(void) {
	static int id;
	id++;
	return id;
}

/** @brief Functia verifica ce comanda avem si ne redirectioneaza spre
 *		   o alta functie specifica cerintei curente
 *  @param input: Comanda
 *  @param tree_vector: Vectorul de copaci
 */
void handle_input_posts(char *input, g_tree **tree_vector)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");

	if (!cmd)
		return;

	if (!strcmp(cmd, "create")) {
		int id = id_increase();
		create_post(&tree_vector[id], id);
	} else if (!strcmp(cmd, "repost")) {
		int id = id_increase();
		repost(tree_vector, id);
	} else if (!strcmp(cmd, "common-repost")) {
		common_repost(tree_vector);
	} else if (!strcmp(cmd, "like")) {
		like(tree_vector);
	} else if (!strcmp(cmd, "ratio")) {
		ratio(tree_vector);
	} else if (!strcmp(cmd, "delete")) {
		delete(tree_vector);
	} else if (!strcmp(cmd, "get-likes")) {
		get_likes(tree_vector);
	} else if (!strcmp(cmd, "get-reposts")) {
		get_reposts(tree_vector);
	}

	free(commands);
}
