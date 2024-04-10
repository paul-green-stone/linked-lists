CC 							:= gcc
CFLAGS						:=
ALL_CFLAGS					:= $(CFLAGS) -Wall -Wextra -pedantic-errors -O2

SRCS						:= $(wildcard ./*.c)

BIN							:= test

# ================================================================ #

all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(ALL_CFLAGS) $< -o $@ ../liblists.a -lcunit 

# ================================================================ #

.PHONY: clean

clean:
	rm -rf $(BIN)
