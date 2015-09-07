CC = clang-3.5
HEADERS = famul.h smith_waterman.h read_fasta.h
OBJECTS = famul.o smith_waterman.o read_fasta.o

default: famul

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@ -g

famul: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -g

clean:
	-rm -f $(OBJECTS)
	-rm -f famul
