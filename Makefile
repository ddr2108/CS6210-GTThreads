#### GTThread Library Makefile

CFLAGS  = -Wall -pedantic
LFLAGS  =
CC      = gcc
RM      = /bin/rm -rf
AR      = ar rc
RANLIB  = ranlib

LIBRARY = gtthread.a

LIB_SRC = gtthread.c gtthread_sched.c gtthread_mutex.c

LIB_OBJ = $(patsubst %.c,%.o,$(LIB_SRC))

# pattern rule for object files
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

all: $(LIBRARY)
	$(CC) $(CFLAGS) -I{...} -o philosophers philosophers.c gtthread.a

$(LIBRARY): $(LIB_OBJ)
	$(AR) $(LIBRARY) $(LIB_OBJ)
	$(RANLIB) $(LIBRARY)

clean:
	$(RM) $(LIBRARY) $(LIB_OBJ) philosophers

.PHONY: depend
depend:
	$(CFLAGS) -- $(LIB_SRC)  2>/dev/null
