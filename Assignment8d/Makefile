# Variables
CC      = gcc
CFLAGS  = -Wall -Wextra -O2
TARGET  = app
OBJ     = main.o helper.o

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET)

# Compile main.o (depends on helper.h)
main.o: main.c helper.h
	$(CC) $(CFLAGS) -c main.c

# Compile helper.o (depends on helper.h)
helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c

# Run
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -f $(TARGET) *.o

# Help
help:
	@echo "make        -> build app"
	@echo "make run    -> run app"
	@echo "make clean  -> remove binaries"
