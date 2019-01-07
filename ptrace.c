#include "ptrace.h"
#include "anonyexec.h"
#include "elfreader.h"
#include "common.h"

int main(int argc, char *argv[], char *envp[])
{
	pid_t  child = 0;
	long   addr  = 0, argaddr = 0;
	int    status = 0, i = 0, arc = 0;
	struct user_regs_struct regs;
	union
	{
		long val;
		char chars[sizeof(long)];
    } data;
    char *args[] = { "/bin/ls", "-a", "-l", NULL };
	uint64_t entry = elfentry(args[0]);    //_start: entry point

	child = fork();
	IFMSG(child == -1, 0, "fork");
	IF(child == 0, proc_child(args[0], args));
	MSG("child pid = %d\r\n", child);
	while(1)
	{
		wait(&status);
		if(WIFEXITED(status))
			break;
		ptrace(PTRACE_GETREGS, child, NULL, &regs);
		if(regs.rip == entry)
		{
			MSG("EIP: _start %llx \r\n", regs.rip);
			MSG("RSP: %llx\r\n", regs.rsp);
			MSG("RSP + 8 => RDX(char **ubp_av) to __libc_start_main\r\n");
			//解析堆栈数据，栈顶为int argc
			addr = regs.rsp;
			arc = ptrace(PTRACE_PEEKTEXT, child, addr, NULL);
			MSG("argc: %d\r\n", arc);
			//POP ESI后栈顶为char **ubp_av, 同时可见此指针数组存储在堆栈之上
			addr += 8;
			//开始解析和修改参数
			for(i = 1;i < arc;i ++)
			{
				argaddr = ptrace(PTRACE_PEEKTEXT, child, addr + (i * sizeof(void*)), NULL);
				data.val = ptrace(PTRACE_PEEKTEXT, child, argaddr, NULL);
				MSG("src: ubp_av[%d]: %s\r\n", i, data.chars);
				MSG("dst: upb_av[%d]: %s\r\n", i, args[i]);
				//修改参数指针指向的内容,demo暂时不支持超过7个字符的参数
				strncpy(data.chars, args[i], sizeof(long) - 1);
				ptrace(PTRACE_POKETEXT, child, argaddr, data.val);
			}
			ptrace(PTRACE_CONT, child, NULL, NULL);
			ptrace(PTRACE_DETACH, child, NULL, NULL);
			break;
		}
		ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
	}
	return 0;
}

static char *encryptedarg = "3abb6677af34ac57c0ca5828fd94f9d886c"
"26ce59a8ce60ecf6778079423dccff1d6f19cb655805d56098e6d38a1a710dee59523"
"eed7511e5a9e4b8ccb3a4686";

int proc_child(const char *path, char *argv[])
{
	int i = 1;
	ptrace(PTRACE_TRACEME, 0, NULL, NULL);
	for(i = 1;argv[i] != NULL;i ++)
		argv[i] = encryptedarg;
	anonyexec(path, argv);
	return 0;
}
