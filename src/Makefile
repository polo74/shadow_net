CFLAGS= -g3 -Wall -Wextra
LDFLAGS= -lm

all: main

main: main.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f *.o main

.PHONY: clean
