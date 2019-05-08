#ifndef _ANONYEXEC_H
#define _ANONYEXEC_H
#include <fcntl.h>
#include <unistd.h>
#include <linux/memfd.h>
#include <sys/syscall.h>
#include <string.h>
#include <errno.h>

int anonyexec(const char *path, char *argv[], char *envp[]);

#endif
