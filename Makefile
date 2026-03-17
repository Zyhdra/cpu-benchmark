CC      = gcc
CFLAGS  = -O2 -Wall
BINS    = sorting

.PHONY: all clean run

all: $(BINS)

sorting: algorithms/sorting.c
	$(CC) $(CFLAGS) -o $@ $

run: all
	@echo "\n=== SORTING ===" && ./sorting

clean:
	rm -f $(BINS)