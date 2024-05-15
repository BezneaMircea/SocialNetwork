CC=gcc -g
CFLAGS=-Wall -Wextra

FRIENDS=friends
FRIENDS_F=friends_functions
MY_UTILS=utils
LL_LIST=linked_list
STRUCTURI=structuri
QUEUE=queue
DLL_LIST=double_linked_list
USERS=users
STACK=stack
GRAPH=graph_with_list

.PHONY: build clean

all: build

build: friends
# We need to add posts and feed on the build rule

# Any other object file that is needed for the other files
# add it here, separated by space

friends: $(USERS).o $(FRIENDS).o $(FRIENDS_F).o $(LL_LIST).o $(DLL_LIST).o $(QUEUE).o $(STACK).o $(GRAPH).o friends.o social_media_friends.o
	$(CC) $(CFLAGS) -o $@ $^

social_media_friends.o:
	$(CC) $(CFLAGS) -c -D TASK_1 -o $@ social_media.c

$(USERS).o: $(USERS).c $(USERS).h
	$(CC) $(CFLAGS) $^ -c

$(DLL_LIST).o: $(DLL_LIST).c $(STRUCTURI).h
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

clean:
	rm -rf *.o friends posts feed