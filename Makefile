CC      = gcc
CFLAGS  = -Wall -Wextra -g -Iinclude -fsanitize=address
TARGET  = build/main
 
SRC     = $(wildcard src/*.c)
OBJ     = $(patsubst src/%.c, build/%.o, $(SRC))
 
all: build $(TARGET)
 
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^
 
build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
 
build:
	mkdir -p build
 
clean:
	rm -f build/*.o $(TARGET)
 
fclean: clean
	rm -rf build
 
re: fclean all
 
.PHONY: all clean fclean re build
 

