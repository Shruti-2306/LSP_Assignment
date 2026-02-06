# Variables
CC      = gcc
AR      = ar
CFLAGS  = -Wall -Wextra -O2
TARGET  = app
LIB     = libmath.a
LIBOBJ  = math.o
APPOBJ  = main.o

# Default target
all: lib app

# Build static library
lib: $(LIB)

$(LIB): $(LIBOBJ)
	$(AR) rcs $(LIB) $(LIBOBJ)

# Compile library object
math.o: math.c math.h
	$(CC) $(CFLAGS) -c math.c

# Build application
app: $(APPOBJ) $(LIB)
	$(CC) $(CFLAGS) $(APPOBJ) -L. -lmath -o $(TARGET)

# Compile main object
main.o: main.c math.h
	$(CC) $(CFLAGS) -c main.c

# Clean
clean:
	rm -f *.o $(LIB) $(TARGET)

# Help
help:
	@echo "make lib    -> build static library libmath.a"
	@echo "make app    -> build application using static library"
	@echo "make clean  -> remove all generated files"
