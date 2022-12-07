CC = gcc
CFLAGS   = -O3 -lm -Wall -Wstrict-prototypes -ansi -pedantic
COMMONSRC = libraries.h
EXECUTABLE = ../bin/lyapunov

$(EXECUTABLE): lyapunov.o parsing.o $(COMMONSRC)
	$(CC) -o $(EXECUTABLE) lyapunov.o parsing.o $(CFLAGS)


parsing.o: parsing.c $(COMMONSRC)
	$(CC) -c -o parsing.o parsing.c $(CFLAGS)

lyapunov.o: lyapunov.c $(COMMONSRC)
	$(CC) -c -o lyapunov.o lyapunov.c $(CFLAGS)

clean:
	rm -f ../bin/*.ppm *.o $(EXECUTABLE)
