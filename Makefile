CC := gcc
CFLAGS := -Wall -Wextra
SOURCE := xkbdlight.c
BINARY := xkbdlight

all: $(SOURCE)
	-@$(CC) $(CFLAGS) -o $(BINARY) $(SOURCE)
	-@echo "Nice. Now, before running:"
	-@echo "chown root:root $(BINARY) && chmod +s $(BINARY)"

clean:
	-@rm -f $(BINARY)
