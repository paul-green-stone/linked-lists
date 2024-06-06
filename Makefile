OBJDIR := objects
OBJECTS := $(addprefix $(OBJDIR)/, Lists.o)

CC := gcc
CFLAGS := -g -c
ALL_CFLAGS := $(CFLAGS) -Wall -Wextra -pedantic-errors -fPIC -O2

AR := ar
ARFLAGS := -r -s

OS_NAME := $(shell uname -s)

INCLUDE := -Iinclude

LIB_NAME := lists

ifeq ($(OS_NAME), Linux)
    LIB_PREFIX				:= lib
    LIB_SUFFIX				:= .a
    DLL_SUFFIX				:= .so
else ifeq ($(OS_NAME), Darwin)
    LIB_PREFIX				:= lib
    LIB_SUFFIX				:= .a
    DLL_SUFFIX				:= .dylib
else ifeq ($(OS_NAME), MINGW32_NT-10.0)
    LIB_PREFIX				:=
    LIB_SUFFIX				:= .a
    DLL_SUFFIX				:= .dll
else
    $(echo Unsupported operating system)
endif

SRCS := $(wildcard source/*.c)
OBJS := $(patsubst source/%.c, objects/%.o, $(SRCS))

TARGET_STATIC := $(LIB_PREFIX)$(LIB_NAME)$(LIB_SUFFIX)
TARGET_SHARED := $(LIB_PREFIX)$(LIB_NAME)$(DLL_SUFFIX)

# ================================================================ #

all: $(TARGET_STATIC) $(TARGET_SHARED)

$(TARGET_STATIC): $(OBJS)
	$(AR) $(ARFLAGS) $(TARGET_STATIC) $^

$(TARGET_SHARED): $(OBJS)
	$(CC) -shared -o $@ $^

# ================================ #

$(OBJDIR)/%.o: source/%.c
	$(CC) $(INCLUDE) $(ALL_CFLAGS) $< -o $@

# ================================================================ #

$(shell mkdir -p $(OBJDIR))

.PHONY: clean

clean:
	rm -rf $(OBJS) $(OBJDIR) $(TARGET_STATIC) $(TARGET_SHARED)
