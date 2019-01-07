CC       = gcc
CFLAGS   = -Wall

LIBS = 

.PHONY: all
all: ptrace

ptrace: ptrace.o anonyexec.o elfreader.o
	$(CC) -o $@ $^ $(LIBS)

ptrace.o: ptrace.c
	$(CC) $(CFLAGS) -c $^ -o $@

anonyexec.o: anonyexec.c
	$(CC) $(CFLAGS) -c $^ -o $@

elfreader.o: elfreader.c
	$(CC) $(CFLAGS) -c $^ -o $@
	
.PHONY: clean
clean:
	rm -f ptrace ptrace.o anonyexec.o elfreader.o
