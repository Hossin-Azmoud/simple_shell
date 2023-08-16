#include "_simple_shell.h"

/**
 * _exec - function that manage the executing of
 *		the simple shell
 */
void _exec(void)
{
	int   pid, code, stat = 0, res = 0;
	char  **argv = reader(GET_TOKENS);
	map_t *m    = get_envp_map();
	builtin_func_t *func;
	char  *shell;

	func = get_builtin(argv[0]);
	if (func != NULL)
	{
		func->f(argv);
		set_status(0);
		return;
	}

	resolve_command_path(&argv[0], &res);
	if (res)
	{
		pid = fork();
		if (pid == 0)
		{
			code = execve(argv[0], argv, m->all);
			if (code == -1)
			{
				perror("[ERROR]");
				reader(FREE);
				release_env_();
				release_path();
				exit(1);
			}
			exit(code);
		}
		waitpid(pid, &stat, 0);
		set_status(WEXITSTATUS(stat));
		return;
	}

	shell = _get_env("_");
	fprintf(stderr, "%s: %i: %s: not found\n", shell, get_line_index(), argv[0]);
	free(shell);
}
