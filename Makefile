CC = clang-3.5
DERS = famul.h smith_waterman.h
OBJECTS = famul.o smith_waterman.o

default: famul

%.o: %.c $(HEADERS)
	$(CC) -c $< -o $@ -g

famul: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ -g

clean:
	-rm -f $(OBJECTS)
	-rm -f famul
