CFLAGS= -g3 -Wall -Wextra
LDFLAGS= -lm

all: perf

perf: perf.c
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	@rm -f *.o perf

.PHONY: clean
