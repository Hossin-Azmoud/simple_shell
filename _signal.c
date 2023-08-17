#include "_simple_shell.h"
/**
 * _sig_int - function that take the signal of a int
 * @sig: the argument or the signal
 * Return: internal_signal or 0
 */
int _sig_int(int sig)
{
	static int internal_sig = -1;

	if (sig == -1)
		return (internal_sig);

	internal_sig = sig;
	return (0);
}

/**
 * handle_signal - function that handle the signal which
 *			manage the function _sig_int
 * @signal: the argument or the signal
 */
void handle_signal(int signal)
{
	_sig_int(signal);
}
