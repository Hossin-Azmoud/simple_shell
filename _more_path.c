#include "_simple_shell.h"

void  print_path(void)
{
	path_manager(PRINT_PATH, NULL, NULL);
}

void resolve_command_path(char **old_path, int *res)
{
	path_manager(FIND_CMD, old_path, res);
}

char **get_tokenized_path(void)
{
	char *path     = _get_env("PATH");
	char **out;
	
	if (!path)
	{
		_puts("err: path not found.\n");
		return NULL;
	}

	out = split_by_delim(path, ":");
	free(path);
	return out;
}
