# ---------------------------------------------------------
CC      := clang
SRC     := src/main.c
TARGET  := jikan
CFLAGS  := -std=c99 -Wall -Wextra -Werror -Weverything -ferror-limit=100 -Wno-poison-system-directories
LDFLAGS :=

# ---------------------------------------------------------
OBJ := $(SRC:.c=.o)

# ---------------------------------------------------------
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------
.PHONY: all clean debug release run lldb

all: release

release: CFLAGS += -O3 -DNDEBUG
release: $(TARGET)

debug: CFLAGS += -g -O0 -DDEBUG
debug: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

run: debug
	./$(TARGET)

lldb: debug
	lldb ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
