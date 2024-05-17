CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iglobal/pair -Iglobal/utilities -Iglobal/vector -I"global/AVL orderMap" -Iglobal/queue -Iglobal/CSL_list -Iglobal/DL_list -Iglobal/hashMap -Iglobal/orderMap -Iglobal/priority_queue -Iglobal/stack
LDFLAGS =

SRCDIR_PAIR = global/pair
SRCDIR_UTILITIES = global/utilities
SRCDIR_VECTOR = global/vector
SRCDIR_AVL_ORDERMAP = global/AVL_orderMap
SRCDIR_QUEUE = global/queue
SRCDIR_CSL_LIST = global/CSL_list
SRCDIR_DL_LIST = global/DL_list
SRCDIR_HASHMAP = global/hashMap
SRCDIR_ORDERMAP = global/orderMap
SRCDIR_STACK = global/stack
SRCDIR_REDBLACKTREE = global/redBlackTree
OBJDIR = bin/obj
BINDIR = bin/out

SRCS_PAIR = $(wildcard $(SRCDIR_PAIR)/*.c)
SRCS_UTILITIES = $(wildcard $(SRCDIR_UTILITIES)/*.c)
SRCS_VECTOR = $(wildcard $(SRCDIR_VECTOR)/*.c)
SRCS_AVL_ORDERMAP = $(wildcard $(SRCDIR_AVL_ORDERMAP)/*.c)
SRCS_QUEUE = $(wildcard $(SRCDIR_QUEUE)/*.c)
SRCS_CSL_LIST = $(wildcard $(SRCDIR_CSL_LIST)/*.c)
SRCS_DL_LIST = $(wildcard $(SRCDIR_DL_LIST)/*.c)
SRCS_HASHMAP = $(wildcard $(SRCDIR_HASHMAP)/*.c)
SRCS_ORDERMAP = $(wildcard $(SRCDIR_ORDERMAP)/*.c)
SRCS_STACK = $(wildcard $(SRCDIR_STACK)/*.c)
SRCS_REDBLACKTREE = $(wildcard $(SRCDIR_REDBLACKTREE)/*.c)

OBJS_PAIR = $(patsubst $(SRCDIR_PAIR)/%.c, $(OBJDIR)/%.o, $(SRCS_PAIR))
OBJS_UTILITIES = $(patsubst $(SRCDIR_UTILITIES)/%.c, $(OBJDIR)/%.o, $(SRCS_UTILITIES))
OBJS_VECTOR = $(patsubst $(SRCDIR_VECTOR)/%.c, $(OBJDIR)/%.o, $(SRCS_VECTOR))
OBJS_AVL_ORDERMAP = $(patsubst $(SRCDIR_AVL_ORDERMAP)/%.c, $(OBJDIR)/%.o, $(SRCS_AVL_ORDERMAP))
OBJS_QUEUE = $(patsubst $(SRCDIR_QUEUE)/%.c, $(OBJDIR)/%.o, $(SRCS_QUEUE))
OBJS_CSL_LIST = $(patsubst $(SRCDIR_CSL_LIST)/%.c, $(OBJDIR)/%.o, $(SRCS_CSL_LIST))
OBJS_DL_LIST = $(patsubst $(SRCDIR_DL_LIST)/%.c, $(OBJDIR)/%.o, $(SRCS_DL_LIST))
OBJS_HASHMAP = $(patsubst $(SRCDIR_HASHMAP)/%.c, $(OBJDIR)/%.o, $(SRCS_HASHMAP))
OBJS_ORDERMAP = $(patsubst $(SRCDIR_ORDERMAP)/%.c, $(OBJDIR)/%.o, $(SRCS_ORDERMAP))
OBJS_STACK = $(patsubst $(SRCDIR_STACK)/%.c, $(OBJDIR)/%.o, $(SRCS_STACK))
OBJS_REDBLACKTREE = $(patsubst $(SRCDIR_REDBLACKTREE)/%.c, $(OBJDIR)/%.o, $(SRCS_REDBLACKTREE))

EXEC = $(BINDIR)/program

.PHONY: all clean

all: $(OBJDIR) $(BINDIR) $(EXEC)

$(EXEC): $(OBJS_PAIR) $(OBJS_UTILITIES) $(OBJS_VECTOR) $(OBJS_AVL_ORDERMAP) $(OBJS_QUEUE) $(OBJS_CSL_LIST) $(OBJS_DL_LIST) $(OBJS_HASHMAP) $(OBJS_ORDERMAP) $(OBJS_STACK) $(OBJS_REDBLACKTREE) $(OBJDIR)/main.o
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR_PAIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_UTILITIES)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_VECTOR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_AVL_ORDERMAP)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_QUEUE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_CSL_LIST)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_DL_LIST)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_HASHMAP)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_ORDERMAP)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_STACK)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_REDBLACKTREE)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)
