CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
LDFLAGS = -lm

.PHONY: all clean classic run

all: cooridor

# Full game: human vs human or human vs AI (5 difficulty levels)
cooridor: cooridor.c
	$(CC) $(CFLAGS) cooridor.c -o cooridor $(LDFLAGS)

# Classic two-player mode without AI (earlier course milestone)
classic: main.c
	$(CC) $(CFLAGS) main.c -o classic $(LDFLAGS)

run: cooridor
	./cooridor

clean:
	rm -f cooridor classic *.exe *.o
