#include "_simple_shell.h"
#include <errno.h>

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
			uinit_environment();
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				fprintf(stderr,
					"%s: 0: cannot open %s: No such file\n",
					argv[0],
					file_name
				);
				exit(127);
			}

			return (1);
		}
	}

	reader(SET_FD, fd);
	start_shell();
	uinit_environment();

	if (fd != STDIN_FILENO)
		close(fd);

	return (get_status());
}
