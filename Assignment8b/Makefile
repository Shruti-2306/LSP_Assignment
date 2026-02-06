# Variables
CC      = gcc
CFLAGS  = -Wall -Wextra -O2
TARGET  = app
SRC     = main.c

# Default target
all: $(TARGET)

# Build rule
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

# Clean target
clean:
	rm -f $(TARGET)
