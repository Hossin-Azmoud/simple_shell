#include "_simple_shell.h"

/**
 * init_environment - function that initial
 *		the environment
 * @shell_: the argument
 */
void init_environment(char *shell_)
{
	struct sigaction sa;
	/* Init a signal handler. */
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	init_builtins();
	init_env_manager();
	init_path_manager();
	init_state_manager();
	set_shell_name(&shell_);
}

/**
 * uinit_environment - function uinitial of the env
 */
void uinit_environment(void)
{
	release_path();
	release_env_();
	reader(FREE);
}

