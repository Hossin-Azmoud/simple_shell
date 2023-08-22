#include "_simple_shell.h"
/**
* terminate_incoming_ - function that terminate incoming string
* @s: the ing or the argument
* @size: the size
*/
void terminate_incoming_(char *s, int *size)
{
	if (*size >= 2)
	{
		if (s[*size - 2] == '\r')
		{
			s[*size - 2] = 0;
			*size -= 1;
			return;
		}

		s[*size - 1] = 0;
		*size -= 1;
	}
}

/**
* _fputs - function that put the ing
* @s: the ing or the argument
* @fd: the argument
* Return: the ing
*/
int _fputs(char *s, int fd)
{
	if (s == NULL)
		return (_puts("(null)"));
	else
		return (write(fd, s, _strlen(s)));
}
/**
* _puts - function that put the ing
* @s: the ing or the argument
* Return: the ing
*/
int _puts(char *s)
{
	return (_fputs(s, STDOUT_FILENO));
}
/**
* _putchar - function that put the ing
* @c: the character or the argument
* Return: the character
*/
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
* trim - function that put the ing
* @s: the ing or the argument
* Return: the ing
*/
int trim(char **s)
{
	char   *tmp  = *s;
	size_t it  = 0;
	int    len = _strlen(tmp);
	char   *buff = malloc(len + 1);

	if (tmp == NULL || buff == NULL)
		return (0);

	if (!isspace(*tmp))
	{
		free(buff);
		return (len);
	}

	while (isspace(*tmp))
		tmp++;

	while (*tmp)
		buff[it++] = *tmp++;

	buff[it] = '\0';

	free(*s);

	*s = buff;
	return (it);
}
