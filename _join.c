#include "_simple_shell.h"
/**
* _join_with_path - joins a path with a name.
* @path: the path that will be joined.
* @file_name: the file that will be joined with path
* Return: ({path}/{file_name}) if success, else NULL
*/
char *_join_with_path(char *path, char *file_name)
{
	int   sz   = (_strlen(path) + _strlen(file_name) + 2);
	char *full = (char *) malloc(sz);

	if (full == NULL)
		return (NULL);

	full = _strcpy(full, path);
	full = _strcat(full, "/");
	full = _strcat(full, file_name);

	return (full);
}
