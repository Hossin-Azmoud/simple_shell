#include "_simple_shell.h"

/**
 * init_env_manager - function manage the init
 * Return: void
 */
void  init_env_manager(void)
{
	env_manager(INIT_ENV, NULL, NULL);
}
/**
* init_path_manager - function that initial the path
* Return: void
*/
void init_path_manager(void)
{
	path_manager(INIT_PATH, NULL, NULL);
}
/**
 * init_builtins - function that manage init in builts
 * Return: Void
 */
void init_builtins(void)
{
	builtins_manager(INIT_BUILTN, NULL, NULL);

	set_builtin("exit", __exit_shell);
	set_builtin("env",  print_env);
	set_builtin("path", print_path);
	set_builtin("cd", change_dir);
	set_builtin("clear", clear);
	set_builtin("unsetenv", unset__env);
	set_builtin("setenv", set__env);
}

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
 * uinit_environment - function that frees the environment
 */
void uinit_environment(void)
{
	distroy_path();
	distroy_env_();
	reader(FREE);
}
