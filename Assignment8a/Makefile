
CC = gcc
CFLAGS = -Wall -Wextra


TARGET = app


all: $(TARGET)

# Build rule
$(TARGET): main.c
	$(CC) $(CFLAGS) main.c -o $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

# Clean target
clean:
	rm -f $(TARGET)
