#include "_simple_shell.h"

/**
* _strdup - a func that duplicates a string.
* @s: pointer to the string that will be duplicated.
* Return: pointer to the resulting string. or null if it fails.
*/
char *_strdup(char *s)
{
	char *s_, *cp_ptr, *og_ptr;

	if (s == NULL)
		return (NULL);

	s_     = (char *) malloc(_strlen(s) + 1);
	cp_ptr = s_;
	og_ptr = s;
	while (*og_ptr !=  0)
	{
		*cp_ptr = *og_ptr;
		og_ptr++;
		cp_ptr++;
	}

	*cp_ptr = 0;
	return (s_);
}
