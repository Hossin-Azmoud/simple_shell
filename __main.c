#include "_simple_shell.h"
/**
* main - entry point.
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
