#include "_simple_shell.h"
/**
* main - entry point.
* @_: the argument
* @argv: the argument
* Return: always 0.
*/
int main(int _, char **argv)
{
	(void) _;
	init_environment(argv[0]);
	start_shell();
	uinit_environment();
	return (get_status());
}

int _main()
{
	char *some  = strdup("Hossin ");	
	char *other = "azmoud!";

	some = _strcat(some, other);

	printf("some: %s\n", some);
	free(some);
	return (0);
}
