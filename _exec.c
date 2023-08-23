#include "_simple_shell.h"
/**
 * _exec__internal - private func to execute commands and return code.
 * @argv: commands args.
 * @env:  shell environment.
 * Return: command exit code.
 */
static int _exec__internal(char **argv, char **env)
{
	int   pid, code, stat = 0, res = 0;
	builtin_func_t *func = get_builtin(argv[0]);
	char *shell;

	if (func != NULL)
	{
		func->f(argv);
		return (get_status());
	}

	path_manager(FIND_CMD, &argv[0], &res);
	if (res)
	{
		pid = fork();
		if (pid == 0)
		{
			code = execve(argv[0], argv, env);
			if (code == -1)
			{
				perror("[ERROR]");
				reader(FREE);
				distroy_path();
				distroy_env_();
				exit(1);
			}
			exit(code);
		}
		waitpid(pid, &stat, 0);
		set_status(WEXITSTATUS(stat));
		return (WEXITSTATUS(stat));
	}

	shell = get_shell_name();
	fprintf(stderr, "%s: %i: %s: not found\n", shell, get_line_index(), argv[0]);
	set_status(COMMAND_NOT_FOUND_STATUS);
	return (COMMAND_NOT_FOUND_STATUS);
}

/**
 * _exec - function that manage the executing of
 *		the simple shell
 */
void _exec(void)
{
	input_buffer_t *uinput = (input_buffer_t *) reader(GET_ALL);
	size_t idx = 0;
	int prev_code = 0;
	char **argv = uinput->tokens;
	map_t *m     = get_envp_map();

	for (; uinput->commands[idx]; idx++)
	{
		prev_code = _exec__internal(argv, m->all);
		if (uinput->ctx == NULL || (uinput->ctx + idx) == NULL)
			return;

		switch (uinput->ctx[idx])
		{
			case END: {
				return;
			} break;
			case OR: {
				while (uinput->ctx[idx] == OR && prev_code == 0)
				{
					argv = (char **) reader(TOKENIZE);
					idx++;
				}
			} break;
			case AND: {
				if (prev_code != 0)
					return;
			} break;
			case JOIN: {
			} break;
		}
		argv = (char **) reader(TOKENIZE);
	}
}
