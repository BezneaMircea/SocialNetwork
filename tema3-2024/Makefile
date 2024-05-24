CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

FRIENDS=friends
FRIENDS_F=friends_functions
MY_UTILS=utils
LL_LIST=linked_list
STRUCTURI=structuri
QUEUE=queue
USERS=users
STACK=stack
GRAPH=graph_with_list
G_TREE=generic_tree
POSTS=posts
POSTS_F=posts_functions
FEED=feed
FEED_F=feed_functions

.PHONY: build clean

all: build

build: friends posts feed
# We need to add posts and feed on the build rule

# Any other object file that is needed for the other files
# add it here, separated by space

friends: $(USERS).o $(FRIENDS).o $(FRIENDS_F).o $(LL_LIST).o $(QUEUE).o $(STACK).o $(G_TREE).o $(GRAPH).o social_media_friends.o
	$(CC) $(CFLAGS) -o $@ $^

posts: $(USERS).o $(LL_LIST).o $(QUEUE).o $(STACK).o $(POSTS).o $(POSTS_F).o $(GRAPH).o $(G_TREE).o social_media_posts.o
	$(CC) $(CFLAGS) -o $@ $^

feed: $(FEED).o $(FEED_F).o $(USERS).o $(LL_LIST).o $(QUEUE).o $(STACK).o $(POSTS).o $(POSTS_F).o $(GRAPH).o $(G_TREE).o $(FRIENDS).o $(FRIENDS_F).o social_media_feed.o
	$(CC) $(CFLAGS) -o $@ $^

social_media_friends.o:
	$(CC) $(CFLAGS) -c -D TASK_1 -o $@ social_media.c

social_media_posts.o:
	$(CC) $(CFLAGS) -c -D TASK_2 -o $@ social_media.c

social_media_feed.o:
	$(CC) $(CFLAGS) -c -D TASK_3 -o $@ social_media.c

$(USERS).o: $(USERS).c $(USERS).h
	$(CC) $(CFLAGS) $^ -c

$(STACK).o: $(STACK).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(QUEUE).o: $(QUEUE).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(LL_LIST).o: $(LL_LIST).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(GRAPH).o: $(GRAPH).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(FRIENDS).o: $(FRIENDS).c $(FRIENDS).h
	$(CC) $(CFLAGS) $^ -c

$(FRIENDS_F).o: $(FRIENDS_F).c $(FRIENDS).h
	$(CC) $(CFLAGS) $^ -c

$(POSTS).o: $(POSTS).c $(POSTS).h
	$(CC) $(CFLAGS) $^ -c

$(POSTS_F).o: $(POSTS_F).c $(POSTS).h
	$(CC) $(CFLAGS) $^ -c

$(G_TREE).o: $(G_TREE).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(FEED).o: $(FEED).c $(FEED).h
	$(CC) $(CFLAGS) $^ -c

$(FEED_F).o: $(FEED_F).c $(FEED).h
	$(CC) $(CFLAGS) $^ -c

clean:
	rm -rf *.o *.gch friends posts feed
