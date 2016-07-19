#SRC			= estr.c estrtoken.c estrbuffer.c
SRC			= estr.c
OBJ			= $(SRC:.c=.o)
INSTALL			= ../deploy/$(shell uname -m)
LIB			= libestr.so
CC			= gcc
FLAGS			= -Wl,-z,relro,-z,now -fstack-protector-all -ffunction-sections -Wall -W -pedantic -fPIC
DEBUG_FLAGS		= -g -O0
INC_FLAGS		= -I$(PWD)/../api
# Compiler
CFLAGS			= $(DEBUG_FLAGS) $(INC_FLAGS) $(FLAGS)
# Linker
LDFLAGS			=

.SUFFIXES: .c

default: $(LIB)

all: $(LIB)


$(LIB): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) -shared
	@mkdir -p $(INSTALL) 
	@mv $(LIB) $(INSTALL)

.c.o:
	echo 'Building target: $@'
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(INSTALL)/$(LIB) *~

