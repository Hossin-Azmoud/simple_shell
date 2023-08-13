#include "_simple_shell.h"

char **parse_command(char *buff)
{		
	return split_by_delim(buff, " \t\n");
}

char **get_tokenized_path()
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
