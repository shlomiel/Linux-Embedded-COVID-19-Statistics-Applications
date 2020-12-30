
CC       = gcc
ECHO     = echo "going to compile for target $@"
PROG = print_by_date
SHARED_FLAGS= -shared -fPIC
SHARED_LIBRARY =shared_library.c

SRCS := $(subst ./,,$(shell find . -maxdepth 1 -name "*.c" ! -iname "shared_library.c"))
OBJECTS := $(patsubst %.c, %.out,$(SRCS))

all: libutils.so $(SRCS) $(OBJECTS)

libutils.so: $(SHARED_LIBRARY)
	echo so $<
	$(CC) $(SHARED_FLAGS) -Wall $^ -o $@

%.out: %.c
	$(CC) $< -lutils -L`pwd` -o $@

clean:
	rm *.so *.out