#include "_simple_shell.h"
void init_environment()
{
	struct sigaction sa;

	/* Init a signal handler. */
	sa.sa_handler = _sig_int;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

	init_builtins();
	init_env_manager();
	init_path_manager();
	init_state_manager();
}
	
void uinit_environment()
{
	release_path();
	release_env_();
	reader(FREE);
}

