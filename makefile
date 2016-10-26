CC=gcc
CFLAGS=-lm -lSDL2

EXE=lineart

DEPS=sloth.h lineart.h

OBJ_DEPS=sloth.o lineart.o main.o

%.o: $.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXE): $(OBJ_DEPS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(EXE) *.o *~
