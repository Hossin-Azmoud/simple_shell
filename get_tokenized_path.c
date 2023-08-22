#include "_simple_shell.h"
/**
* get_tokenized_path - function that get the token of the path
* Return: ou tor null
*/
char **get_tokenized_path(void)
{
	char *path     = _get_env("PATH");
	char **out;

	if (!path)
		return (NULL);

	out = split_by_delim(path, ":");
	free(path);
	return (out);
}
