#include "_simple_shell.h"

void __exit_shell()
{
	int size = 0;
	void *code_ptr;
	int code = (get_status());
	char **argv = reader(GET_TOKENS);

	while (argv[size] != NULL)
		size++;

	if (size > 1)
	{
		code_ptr = shell_atoi(argv[1]);
		if (code_ptr == NULL)
		{
			fprintf(stderr, "[ERROR] invalid number given to exit `%s`\n", argv[1]);
			return;
		}
		else 
		{
			code = *(int *) code_ptr;
			free(code_ptr);
		}
	}

	uinit_environment();
	exit(code);
}

void change_dir()
{
	_fputs("`change_dir` NOT IMPLEMENTED\n", STDERR_FILENO);
}

void clear()
{
	_puts(CLEAR_BYTES);
	_puts("\033[0;0H\n"); /* Go to the starting col and row of the term. */
}
