CC     = gcc
CFLAGS = -Wall -Wextra -g
SRC    = src/main.c src/shell.c src/parser.c \
         src/executor.c src/commands.c
OUT    = myshell

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
