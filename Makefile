CC = g++
CFLAGS = -g -Wall -Werror -std=c++11
TARGETS = main
SRCS = main.cpp read/read.cpp syntax/syntax.cpp word/word.cpp
OBJS = $(SRCS:.cpp=.o)

.PHONY: all clean
all: $(TARGETS)

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGETS) $(OBJS)
