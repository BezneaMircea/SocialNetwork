CC=gcc
CFLAGS=-Wall -Wextra -Werror -g

DLL_LIST=double_linked_list
LL_LIST=linked_list
GRAPH_LIST=graph_with_list
STACK=stack
QUEUE=queue
FRIENDS_FUNCT=friends_function
STRUCTURI=structuri
FRIENDSS=friendss


.PHONY: build clean

all: build

build: friends posts feed

# Any other object file that is needed for the other files
# add it here, separated by space
UTILS = users.o
friends: $(UTILS) $(FRIENDSS).o $(FRIENDS_FUNCT).o $(DLL_LIST).o $(LL_LIST).o $(GRAPH_LIST).o $(STACK).o $(QUEUE).o social_media_friends.o
	$(CC) $(CFLAGS) -o $@ $^

posts: $(UTILS) posts.o social_media_posts.o
	$(CC) $(CFLAGS) -o $@ $^
	
feed: $(UTILS) posts.o friends.o feed.o social_media_feed.o
	$(CC) $(CFLAGS) -o $@ $^

social_media_friends.o:
	$(CC) $(CFLAGS) -c -D TASK_1 -o $@ social_media.c

social_media_posts.o:
	$(CC) $(CFLAGS) -c -D TASK_2 -o $@ social_media.c

social_media_feed.o:
	$(CC) $(CFLAGS) -c -D TASK_1 -D TASK_2 -D TASK_3 -o $@ social_media.c

$(DLL_LIST).o: $(DLL_LIST).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(LL_LIST).o: $(LL_LIST).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(QUEUE).o: $(QUEUE).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(STACK).o: $(STACK).c $(STRUCTURI).h
	$(CC) $(CFLAGS) $^ -c

$(FRIENDS_FUNCT).o: $(FRIENDS_FUNCT).c $(FRIENDSS).h
	$(CC) $(CFLAGS) $^ -c

clean:
	rm -rf *.o friends posts feed