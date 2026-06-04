CC      = gcc
TARGET  = snake_game
SRCS    = main.c structs.c logic.c ui.c input.c
CFLAGS  = $(shell pkg-config --cflags gtk+-3.0)
LIBS    = $(shell pkg-config --libs gtk+-3.0)

all:
	$(CC) $(SRCS) -o $(TARGET) $(CFLAGS) $(LIBS)
	@echo "Build successful! Run with: ./$(TARGET)"

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET)
