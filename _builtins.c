#include "_simple_shell.h"
/**
 * __exit_shell - function that exit shell
 */

void __exit_shell(void)
{
	int size = 0, code = (get_status());
	void *code_ptr;
	char **argv = reader(GET_TOKENS);

	size = _strlen2d(argv);
	if (size > 1)
	{
		code_ptr = shell_atoi(argv[1]);
		if (code_ptr == NULL)
		{
			fprintf(stderr, "[ERROR] invalid number given to exit `%s`\n", argv[1]);
			set_status(2);
			return;
		}

		code = *(int *) code_ptr;
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
 * change_dir - function that change directory
 * Return: Always 0
 */
void change_dir(void)
{
	char **args    = reader(GET_TOKENS);
	int res, count = _strlen2d(args);
	char cwd[PATH_MAX];
	char *pwd = _get_env("PWD");

	if (count == 1)
	{
		res = chdir(ROOT);
		if (res != 0)
		{
			perror("[ERROR (CD)]");
			set_status(1);
			return;
		}

		_set_env("PWD", ROOT);
		_set_env("OLDPWD", pwd);
		set_status(0);
		return;
	}

	res = chdir(args[1]);
	if (res != 0)
	{
		_puts(args[1]);
		_putchar(' ');
		perror(":");
		set_status(1);
		return;
	}

	getcwd(cwd, PATH_MAX);
	_set_env("PWD",    cwd);
	_set_env("OLDPWD", pwd);
	set_status(0);
}
