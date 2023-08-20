#include "_simple_shell.h"
/**
* print_path - function that print the path
*
*/
void  print_path(void)
{
	path_manager(PRINT_PATH, NULL, NULL);
}
/**
* resolve_command_path - function that resolve the path
* @old_path: the old path of the command
* @res: the result of the command
*/
void resolve_command_path(char **old_path, int *res)
{
	path_manager(FIND_CMD, old_path, res);
}
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
