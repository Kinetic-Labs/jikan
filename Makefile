# ---------------------------------------------------------
CC      := clang
SRC     := src/main.c
TARGET  := jikan
CFLAGS  := -std=c99 -Wall -Wextra -Werror -Weverything -ferror-limit=100 \
           -Wno-poison-system-directories
LDFLAGS :=

CC_INFO := $(shell $(CC) --version 2>/dev/null | head -n1)

# ---------------------------------------------------------
OBJ := $(SRC:.c=.o)

# ---------------------------------------------------------
.PHONY: all clean debug release run lldb

all: release

debug: CFLAGS += -g -O0 -DDEBUG
debug: $(TARGET)

release: CFLAGS += -O3 -DNDEBUG
release: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

$(OBJ): config.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# janky hack: maybe update (or just use autotools / cmake or something)
config.h: config.h.in
	sed 's/@CC@/$(CC_INFO)/g; s/^.*@CC_V@.*$$//g' $< > $@.tmp && \
	mv $@.tmp $@

run: debug
	./$(TARGET)

lldb: debug
	lldb ./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET) config.h
