CC = clang-3.5
HEADERS = famul.h smith_waterman.h read_fasta.h pam.h matrix.h
OBJECTS = famul.o smith_waterman.o read_fasta.o pam.o matrix.o
LIB = -L/usr/local/lib -lgsl -lgslcblas -lm

default: famul

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@

famul: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -lgsl -lgslcblas -lm

clean:
	-rm -f $(OBJECTS)
	-rm -f famul
