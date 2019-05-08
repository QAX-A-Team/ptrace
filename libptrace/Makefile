CC       = gcc
AR       = ar
CFLAGS   = -Wall

LIBS = 

.PHONY: all
all: libptrace.a test

test: test.o
	$(CC) -o $@ $^ -L. -lptrace $(LIBS)

test.o: test.c
	$(CC) $(CFLAGS) -c $^ -o $@

libptrace.a: ptrace.o anonyexec.o elfreader.o
	$(AR) rcs -o $@ $^ $(LIBS)

ptrace.o: ptrace.c
	$(CC) $(CFLAGS) -c $^ -o $@

anonyexec.o: anonyexec.c
	$(CC) $(CFLAGS) -c $^ -o $@

elfreader.o: elfreader.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
.PHONY: clean
clean:
	rm -f libptrace.a test test.o ptrace.o anonyexec.o elfreader.o
