#include "_simple_shell.h"

/**
* _strdup - a func that duplicates a string.
* @s: pointer to the string that will be duplicated.
* Return: pointer to the resulting string. or null if it fails.
*/
char *_strdup(char *s)
{
	char *s_   = malloc(_strlen(s) + 1);
	char *ptr_;

	for (ptr = s; (*s); s++, s_++)
		*s_ = *s;

	return (s_);
}
