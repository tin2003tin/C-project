CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Iglobal/data_structure/pair -Iglobal/data_structure/utilities \
        -Iglobal/data_structure/vector -I"global/data_structure/AVL orderMap" -Iglobal/data_structure/queue \
        -Iglobal/data_structure/CSL_list -Iglobal/data_structure/DL_list -Iglobal/data_structure/SL_list \
         -Iglobal/data_structure/hashMap -Iglobal/data_structure/priority_queue -Iglobal/data_structure/stack \
        -Iglobal/data_structure/redBlackTree -Iglobal/cryto/sha256
LDFLAGS =

SRCDIR_PAIR = global/data_structure/pair
SRCDIR_UTILITIES = global/data_structure/utilities
SRCDIR_VECTOR = global/data_structure/vector
SRCDIR_AVL_ORDERMAP = global/data_structure/AVL_orderMap
SRCDIR_QUEUE = global/data_structure/queue
SRCDIR_CSL_LIST = global/data_structure/CSL_list
SRCDIR_DL_LIST = global/data_structure/DL_list
SRCDIR_SL_LIST = global/data_structure/SL_list
SRCDIR_HASHMAP = global/data_structure/hashMap
SRCDIR_STACK = global/data_structure/stack
SRCDIR_PRIORITYQUEUE = global/data_structure/priority_queue
SRCDIR_REDBLACKTREE = global/data_structure/redBlackTree
SRCDIR_SHA256 = global/cryto/sha256

OBJDIR = bin/obj
BINDIR = bin/out

SRCS_PAIR = $(wildcard $(SRCDIR_PAIR)/*.c)
SRCS_UTILITIES = $(wildcard $(SRCDIR_UTILITIES)/*.c)
SRCS_VECTOR = $(wildcard $(SRCDIR_VECTOR)/*.c)
SRCS_AVL_ORDERMAP = $(wildcard $(SRCDIR_AVL_ORDERMAP)/*.c)
SRCS_QUEUE = $(wildcard $(SRCDIR_QUEUE)/*.c)
SRCS_CSL_LIST = $(wildcard $(SRCDIR_CSL_LIST)/*.c)
SRCS_DL_LIST = $(wildcard $(SRCDIR_DL_LIST)/*.c)
SRCS_SL_LIST = $(wildcard $(SRCDIR_SL_LIST)/*.c)
SRCS_HASHMAP = $(wildcard $(SRCDIR_HASHMAP)/*.c)
SRCS_STACK = $(wildcard $(SRCDIR_STACK)/*.c)
SRCS_PRIORITYQUEUE = $(wildcard $(SRCDIR_PRIORITYQUEUE)/*.c)
SRCS_REDBLACKTREE = $(wildcard $(SRCDIR_REDBLACKTREE)/*.c)
SRCS_SHA256 = $(wildcard $(SRCDIR_SHA256)/*.c)

OBJS_PAIR = $(patsubst $(SRCDIR_PAIR)/%.c, $(OBJDIR)/%.o, $(SRCS_PAIR))
OBJS_UTILITIES = $(patsubst $(SRCDIR_UTILITIES)/%.c, $(OBJDIR)/%.o, $(SRCS_UTILITIES))
OBJS_VECTOR = $(patsubst $(SRCDIR_VECTOR)/%.c, $(OBJDIR)/%.o, $(SRCS_VECTOR))
OBJS_AVL_ORDERMAP = $(patsubst $(SRCDIR_AVL_ORDERMAP)/%.c, $(OBJDIR)/%.o, $(SRCS_AVL_ORDERMAP))
OBJS_QUEUE = $(patsubst $(SRCDIR_QUEUE)/%.c, $(OBJDIR)/%.o, $(SRCS_QUEUE))
OBJS_CSL_LIST = $(patsubst $(SRCDIR_CSL_LIST)/%.c, $(OBJDIR)/%.o, $(SRCS_CSL_LIST))
OBJS_DL_LIST = $(patsubst $(SRCDIR_DL_LIST)/%.c, $(OBJDIR)/%.o, $(SRCS_DL_LIST))
OBJS_SL_LIST = $(patsubst $(SRCDIR_SL_LIST)/%.c, $(OBJDIR)/%.o, $(SRCS_SL_LIST))
OBJS_HASHMAP = $(patsubst $(SRCDIR_HASHMAP)/%.c, $(OBJDIR)/%.o, $(SRCS_HASHMAP))
OBJS_STACK = $(patsubst $(SRCDIR_STACK)/%.c, $(OBJDIR)/%.o, $(SRCS_STACK))
OBJS_PRIORITYQUEUE = $(patsubst $(SRCDIR_PRIORITYQUEUE)/%.c, $(OBJDIR)/%.o, $(SRCS_PRIORITYQUEUE))
OBJS_REDBLACKTREE = $(patsubst $(SRCDIR_REDBLACKTREE)/%.c, $(OBJDIR)/%.o, $(SRCS_REDBLACKTREE))
OBJS_SHA256 = $(patsubst $(SRCDIR_SHA256)/%.c, $(OBJDIR)/%.o, $(SRCS_SHA256))

EXEC = $(BINDIR)/program

.PHONY: all clean

all: $(OBJDIR) $(BINDIR) $(EXEC)

$(EXEC): $(OBJS_PAIR) $(OBJS_UTILITIES) $(OBJS_VECTOR) $(OBJS_AVL_ORDERMAP) $(OBJS_QUEUE) \
         $(OBJS_CSL_LIST) $(OBJS_DL_LIST) $(OBJS_SL_LIST) $(OBJS_HASHMAP) $(OBJS_STACK) \
         $(OBJS_PRIORITYQUEUE) $(OBJS_REDBLACKTREE) $(OBJS_SHA256) $(OBJDIR)/main.o
	@$(CC) $(LDFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR_PAIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_UTILITIES)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_VECTOR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_AVL_ORDERMAP)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_QUEUE)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_CSL_LIST)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_DL_LIST)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_SL_LIST)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_HASHMAP)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_STACK)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_PRIORITYQUEUE)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_REDBLACKTREE)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR_SHA256)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
