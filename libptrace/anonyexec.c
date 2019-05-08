#include "anonyexec.h"
#include "common.h"

int anonyexec(const char *path, char *argv[], char *envp[])
{
	int   fd, fdm, filesize;
	void *elfbuf;
	char  cmdline[256];
	
	fd = open(path, O_RDONLY);
	IF(fd < 0, -1);
	filesize = lseek(fd, SEEK_SET, SEEK_END);
	lseek(fd, SEEK_SET, SEEK_SET);
	IF(filesize <= 0, -1);
	elfbuf = malloc(filesize);
	read(fd, elfbuf, filesize);
	close(fd);
	fdm = syscall(__NR_memfd_create, "elf", MFD_CLOEXEC);
	GO(fdm < 0, __clean);
	GO(0 != ftruncate(fdm, filesize), __clean);
	write(fdm, elfbuf, filesize);
	free(elfbuf);
	sprintf(cmdline, "/proc/self/fd/%d", fdm);
	argv[0] = cmdline;
	execve(argv[0], argv, envp);
	return 0;
__clean:
	free(elfbuf);
	return -1;
}
