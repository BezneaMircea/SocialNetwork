/*
 * Copyright (c) 2024, <> Beznea Mircea <bezneamirceaandrei21@gmail.com>
 *                        Ghenescu Stefan <stefan.ghenescu2005@gmail.com>
 */

#ifndef UTILS_H
#define UTILS_H

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHILD_NR 100
#define MAX_TITLE_LEN 280
#define MAX_POSTS_NR 300
#define MAX_COMMAND_LEN 500
#define MAX_PEOPLE 550
#define MAX_QUEUE_SIZE 900

#define DIE(assertion, call_description)                                      \
	do {                                                                      \
		if (assertion) {                                                      \
			fprintf(stderr, "(%s, %d): ", __FILE__, __LINE__);                \
			perror(call_description);                                         \
			exit(errno);                                                      \
		}                                                                     \
	} while (0)

#endif /* UTILS_H */
