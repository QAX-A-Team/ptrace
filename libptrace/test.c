#include <stdio.h>

extern int execve2(char *path, char *argv[], char *envp[]);
 
int main()
{
	char *argv[] = {"/bin/ls", "-al", "xxxxxxxx", NULL};
	execve2(argv[0], argv, NULL);
	return 0;
}

