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

build: $(OBJDIR) $(EXEC)
test: $(OBJDIR) $(TESTDIR)/$(TESTBIN) $(OBJS_NOMAIN) $(TESTEXEC)
	for test in $(TESTEXEC) ; do ./$$test ; done

clean: 
	rm -rf $(OBJS) $(TESTEXEC) $(EXEC) $(TESTDIR)/$(TESTBIN)/*

$(TESTDIR)/$(TESTBIN)/%: $(TESTDIR)/%.c
	$(CC) $(CFLAGS) $< $(OBJS_NOMAIN) -o $@

$(EXEC): $(OBJS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $(OBJDIR)

$(TESTDIR)/$(TESTBIN):
	mkdir $(TESTDIR)/$(TESTBIN)