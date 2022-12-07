CC = gcc
CFLAGS   = -O3 -lm -lSDL -Wall -Wstrict-prototypes -ansi -pedantic
COMMONSRC = libraries.h constants.h
EXECUTABLE = ../bin/double_pendulum

$(EXECUTABLE): double_pendulum.o parsing.o simple_random.o\
               visualization.o $(COMMONSRC)
	$(CC) -o $(EXECUTABLE) double_pendulum.o parsing.o\
                           simple_random.o visualization.o $(CFLAGS)


parsing.o: parsing.c $(COMMONSRC)
	$(CC) -c -o parsing.o parsing.c $(CFLAGS)

visualization.o: visualization.c $(COMMONSRC)
	$(CC) -c -o visualization.o visualization.c $(CFLAGS)

simple_random.o: simple_random.c $(COMMONSRC)
	$(CC) -c -o simple_random.o simple_random.c $(CFLAGS)

double_pendulum.o: double_pendulum.c $(COMMONSRC)
	$(CC) -c -o double_pendulum.o double_pendulum.c $(CFLAGS)

clean:
	rm -f ../bin/*.ppm *.o $(EXECUTABLE)
