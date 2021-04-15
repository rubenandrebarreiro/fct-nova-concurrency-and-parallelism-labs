CC=gcc
SYS := $(shell uname -s)
CFLAGS := -c -Wall -g -ansi -pedantic -std=gnu11 -Werror -I/usr/local/include
LDFLAGS := -L/usr/local/lib
LIBS := -lpcre

ifeq ($(SYS),Linux)
# Add stuff here stuff specific for Linux
endif
ifeq ($(SYS),Darwin)
# Add stuff here stuff specific for macOS
CC=clang
LLVMDIR=/usr/local/opt/llvm
LLVM := $(wildcard $(LLVMDIR))
ifneq ($(LLVM),)
# Add stuff here stuff specific for macOS with HomeBrew clang/llvm
CC=$(LLVMDIR)/bin/clang
CFLAGS += -I$(LLVMDIR)/include
LDFLAGS += -L$(LLVMDIR)/lib
endif
endif

P=60
R=100
C=70


EXE=glife
SRC=config.c game.c main.c mem.c
OBJ=$(patsubst %.c,%.o,$(SRC))

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(LIBS)

# This is the default rule, so it is commented
%.o: %.c
	$(CC) $(CFLAGS) $<

.PHONY: board
board:
	genboard $(P) $(R) $(C)

.PHONY: clean
clean:
	rm -f $(EXE) $(OBJ)
