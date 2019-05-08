#ifndef _ELFREADER_H
#define _ELFREADER_H
#include <fcntl.h>
#include <elf.h>
#include <stdint.h>
uint64_t elfentry(const char *path);
#endif
