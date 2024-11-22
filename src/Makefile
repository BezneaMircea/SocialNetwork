# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
FEED_DIR = feed
FRIENDS_DIR = friends
POSTS_DIR = posts
STRUCTURES_DIR = structures
USERS_DIR = users
UTILS_DIR = utils

# Object files
FEED_OBJS = $(FEED_DIR)/feed.o $(FEED_DIR)/feed_functions.o
FRIENDS_OBJS = $(FRIENDS_DIR)/friends.o $(FRIENDS_DIR)/friends_functions.o
POSTS_OBJS = $(POSTS_DIR)/posts.o $(POSTS_DIR)/posts_functions.o
STRUCTURES_OBJS = $(STRUCTURES_DIR)/stack.o \
                  $(STRUCTURES_DIR)/queue.o \
                  $(STRUCTURES_DIR)/generic_tree.o \
                  $(STRUCTURES_DIR)/graph_with_list.o \
                  $(STRUCTURES_DIR)/linked_list.o
USER_OBJS = $(USERS_DIR)/users.o

# Phony targets
.PHONY: all build clean

# Default target
all: build

# Build rule
build: friends_exec posts_exec feed_exec

# Executables
friends_exec: $(USER_OBJS) $(STRUCTURES_OBJS) $(FRIENDS_OBJS) social_media_friends.o
	$(CC) $(CFLAGS) -o $@ $^

posts_exec: $(USER_OBJS) $(STRUCTURES_OBJS) $(POSTS_OBJS) social_media_posts.o
	$(CC) $(CFLAGS) -o $@ $^

feed_exec: $(USER_OBJS) $(STRUCTURES_OBJS) $(FRIENDS_OBJS) $(POSTS_OBJS) $(FEED_OBJS) social_media_feed.o
	$(CC) $(CFLAGS) -o $@ $^

# Social media file with task-specific macros
social_media_friends.o: social_media.c
	$(CC) $(CFLAGS) -c -D TASK_1 -o $@ $<

social_media_posts.o: social_media.c
	$(CC) $(CFLAGS) -c -D TASK_2 -o $@ $<

social_media_feed.o: social_media.c
	$(CC) $(CFLAGS) -c -D TASK_3 -o $@ $<

# Clean rule
clean:
	rm -rf $(FEED_DIR)/*.o $(FRIENDS_DIR)/*.o $(POSTS_DIR)/*.o \
	       $(STRUCTURES_DIR)/*.o $(USERS_DIR)/*.o *.o \
	       friends_exec posts_exec feed_exec
