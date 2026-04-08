CC      = gcc
CFLAGS  = -O2 -Wall -lm
SRCDIR  = algorithms
BINS    = sorting search matrix

.PHONY: all clean run

all: $(BINS)

sorting: $(SRCDIR)/sorting.c util/util.c data/dataset.c
	$(CC) $(CFLAGS) -o $@ $^

search: $(SRCDIR)/searching.c util/util.c
	$(CC) $(CFLAGS) -o $@ $^

matrix: $(SRCDIR)/matrix.c util/util.c
	$(CC) $(CFLAGS) -o $@ $^

run: all
	@echo "\n=== SORTING ===" && ./sorting
	@echo "\n=== SEARCH ===" && ./search
	@echo "\n=== MATRIX MULTIPLY ===" && ./matrix

clean:
	rm -f $(BINS)