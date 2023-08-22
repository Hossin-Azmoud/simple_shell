#include "_simple_shell.h"
/**
* _join_with_path - joins a path with a name.
* @path: the path that will be joined.
* @file_name: the file that will be joined with path
* Return: ({path}/{file_name}) if success, else NULL
*/
char *_join_with_path(char *path, char *file_name)
{
	int   sz   = (strlen(path) + strlen(file_name) + 2);
	char *full = (char *) malloc(sz);

	if (full == NULL)
		return (NULL);

	full = strcpy(full, path);
	full = strcat(full, "/");
	full = strcat(full, file_name);

	return (full);
}
