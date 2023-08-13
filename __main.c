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
