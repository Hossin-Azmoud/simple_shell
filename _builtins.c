#include "_simple_shell.h"

/**
 * __exit_shell - function that exit shell
 */
void __exit_shell(void)
{
	int size = 0, code = (get_status()), ln = get_line_index();
	void *code_ptr;
	char **argv = reader(GET_TOKENS), *shell;

	size = _strlen2d(argv);
	if (size > 1)
	{
		code_ptr = shell_atoi(argv[1]);
		shell = get_shell_name();

		if (code_ptr == NULL)
		{
			fprintf(stderr, "%s: %i: exit: Illegal number: %s\n", shell, ln, argv[1]);
			set_status(2);
			return;
		}

		code = *(int *) code_ptr;
		if (code < 0)
		{
			fprintf(stderr, "%s: %i: exit: Illegal number: %i\n", shell, ln, code);
			set_status(2);
			free(code_ptr);
			return;
		}

		free(code_ptr);
	}

	uinit_environment();
	exit(code);
}

/**
 * clear - function that clear bytes
 */
void clear(void)
{
	_puts(CLEAR_BYTES); /* Clear the terminal */
	_puts("\033[0;0H\n"); /* Go to the starting col and row of the term. */
	set_status(0);
}
/**
 * check_errno - function to log cd error.
 * @dst_failure: path in which failed to cd to.
 * Return: void
 */
static void check_errno(char *dst_failure)
{
	/*fmt! ./hsh: 1: cd: can't cd to /root*/
	char *shell = get_shell_name();
	int idx = get_line_index();

	fprintf(stderr, "%s: %i: cd: can\'t cd to %s\n", shell, idx, dst_failure);
}

/**
 * _cd_internal - core function that changes directory.
 * @arg: the dir path or env key to go to.
 * @is_path: wether is the arg is a path or a key.
 * Return: the return value is (void)
 */
static void _cd_internal(char *arg, int is_path)
{
	char *abs_path = malloc(PATH_MAX + 1);
	char *dist     = NULL;
	char *pwd      = _get_env("PWD");

	if (is_path)
		dist = _strdup(arg);
	else
	{
		dist = _get_env(arg);
		if (!dist)
		{
			if (_strcmp(arg, "OLDPWD") == 0)
			{
				dist = _strdup(pwd);
			} else
			{
				free(pwd);
				free(abs_path);
				return;
			}
		}
	}
	if (chdir(dist) == -1)
	{
		check_errno(dist);
	} else
	{
		abs_path = getcwd(abs_path, PATH_MAX + 1);
		_set_env("PWD",    abs_path);
		_set_env("OLDPWD", pwd);
		if (_strcmp(arg, "OLDPWD") == 0)
		{
			_puts(abs_path);
			_putchar('\n');
		}
	}
	free(pwd);
	free(dist);
	free(abs_path);
}
/**
 * change_dir - function that change directory
 * Return: Always 0
 */
void change_dir(void)
{
	char **args = reader(GET_TOKENS);
	int  count  = _strlen2d(args);
	char *dist  = NULL;

	if (count == 1)
	{
		_cd_internal("HOME", 0);
		return;
	}

	dist = args[1];
	if (_strcmp(dist, "-") == 0)
		_cd_internal("OLDPWD", 0);
	else if (_strcmp(dist, "~") == 0)
		_cd_internal("HOME", 0);
	else
		_cd_internal(dist, 1);
}

