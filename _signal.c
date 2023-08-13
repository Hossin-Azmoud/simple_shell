#include "_simple_shell.h"

int _sig_int(int sig)
{
	static int internal_sig = 0;

	if (signal == SIGINT)
        internal_sig = 1;

	else if (signal == -1)
		return (internal_sig);
}
