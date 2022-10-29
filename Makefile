EXEC = bs.out

SRCDIR = src
OBJDIR = obj
TESTDIR = tests
TESTBIN = bin

SRCS = $(wildcard $(SRCDIR)/*.c)
SRCS_NOMAIN = $(wildcard $(SRCDIR)/bs_*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
OBJS_NOMAIN = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS_NOMAIN))
TESTS = $(wildcard $(TESTDIR)/*.c)
TESTEXEC = $(patsubst $(TESTDIR)/%.c,$(TESTDIR)/$(TESTBIN)/%,$(TESTS))

CFLAGS = -g -Wall
INCL = -I../include

build: $(EXEC)
test: $(OBJS_NOMAIN) $(TESTEXEC)
	for test in $(TESTEXEC) ; do ./$$test ; done

$(TESTDIR)/$(TESTBIN)/%: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $< $(OBJS_NOMAIN) -o $@

$(EXEC): $(OBJS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@