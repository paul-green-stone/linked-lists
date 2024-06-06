CC := gcc
CFLAGS :=
ALL_CFLAGS := $(CFLAGS) -Wall -Wextra -pedantic-errors -O2

LDFLAGS := -lcunit

SRCS := $(wildcard ./*.c)

BIN := a.out

# ================================================================ #

all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(ALL_CFLAGS) $< -o $@ ../liblists.a $(LDFLAGS) 

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(BIN)
