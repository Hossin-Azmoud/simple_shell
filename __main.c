#include "_simple_shell.h"
/**
* main - entry point.
* @argc: the argument
* @argv: the argument
* Return: always 0.
*/
int main(int argc, char **argv)
{
	int fd = STDIN_FILENO;
	char *file_name;

	init_environment(argv[0]);
	if (argc > 1)
	{
		file_name = argv[1];
		fd = open(file_name, O_RDONLY);

		if (fd == -1)
		{
			fprintf(stderr,
				"%s: 0: cannot open %s: No such file\n",
				argv[0],
				file_name
			);

			uinit_environment();
			return (2);
		}
	}

	reader(SET_FD, fd);
	start_shell();
	uinit_environment();
	if (fd != STDIN_FILENO)
		close(fd);
	return (get_status());
}
