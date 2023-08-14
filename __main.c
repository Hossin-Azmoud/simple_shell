#include "_simple_shell.h"

/**
* main - entry point.
* Return: always 0.
*/
int main()
{
	init_environment();
	start_shell();
	uinit_environment();
	return (get_status());
}

int main_()
{
	size_t cap = 0;
	char *buff = NULL, **toks = NULL;

	_getline(&buff, &cap, STDIN_FILENO);
	toks = split_by_delim(buff, " ");

	print_2d(toks);
	free_2d(toks);
	free(buff);
	return (0);
}
