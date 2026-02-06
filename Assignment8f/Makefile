CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared

.PHONY: so app run clean

so: helper.o
	$(CC) $(LDFLAGS) -o libmath.so helper.o

helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c

app: main.o
	$(CC) -o app main.o -L. -lmath

main.o: main.c helper.h
	$(CC) -c main.c

run: app
	LD_LIBRARY_PATH=. ./app

clean:
	rm -f *.o *.so app
