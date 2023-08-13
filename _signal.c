#include "_simple_shell.h"

int _sig_int(int sig)
{
	static int internal_sig = 0;

	if (sig == -1)
		return (internal_sig);

	internal_sig = sig;
	return (0);
}

void handle_signal(int signal)
{
	_sig_int(signal);
}
