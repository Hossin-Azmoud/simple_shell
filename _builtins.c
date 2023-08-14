#include "_simple_shell.h"

void __exit_shell()
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
			return;
		}

		code = *(int *) code_ptr;
		free(code_ptr);
	}

	uinit_environment();
	exit(code);
}

void clear()
{
	_puts(CLEAR_BYTES);
	_puts("\033[0;0H\n"); /* Go to the starting col and row of the term. */
}

void change_dir()
{	
	char **args    = reader(GET_TOKENS);
	int res, count = _strlen2d(args);

	if(count == 1) 
	{
		res = chdir(ROOT);

		if(res != 0)
			perror("[ERROR (CD)]");

		return;
	}

	res = chdir(args[1]);
	if(res != 0)
	{
		_puts(args[1]);
		_putchar(' ');
		perror(":");
	}
}
