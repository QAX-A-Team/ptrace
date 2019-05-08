#ifndef _PTRACE_H
#define _PTRACE_H

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reg.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int proc_child(const char *path, char *argv[], char *envp[]);
#endif
