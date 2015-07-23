CC=gcc
MAIN=rousbot
CFLAGS=-ansi -Wall -Wextra -pedantic -Wno-unused-parameter `curl-config --cflags`
CFLAGSCOMP=`curl-config --libs`
CFLAGSDEBUG=-g $(CFLAGS) $(CFLAGSCOMP)
CFLAGSFINAL=-O3 $(CFLAGS) $(CFLAGSCOMP)
SRCS=rousbot.c
DEPS=message.c
OBJS=$(DEPS:.c=.o)
TEST=test
TEST_SRCS=test.c

build: $(OBJS)
	$(CC) $(CFLAGSFINAL) $(OBJS) -o $(MAIN) $(SRCS)

debug: $(OBJS)
	$(CC) $(CFLAGSDEBUG) $(OBJS) -o $(MAIN) $(SRCS)
	@gdb ./$(MAIN)
	@rm ./$(MAIN)

all: build

%.o: %.c
	$(CC) $(CFLAGS) -g -c $(@:.o=.c) -o $@

test: $(OBJS)
	$(CC) $(CFLAGSFINAL) $(OBJS) -o $(TEST) $(TEST_SRCS)
	@./$(TEST)
	@rm ./$(TEST)

debug_test: $(OBJS)
	$(CC) $(CFLAGSDEBUG) $(OBJS) -o $(TEST) $(TEST_SRCS)
	@gdb ./$(TEST)
	@rm ./$(TEST)

clean:
	rm -f *.o *~ *.gch

cleanall: clean
	rm -f $(MAIN)
