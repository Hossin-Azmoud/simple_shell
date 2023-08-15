#include "_simple_shell.h"

void terminate_incoming_str(char *s, int *size)
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


int _fputs(char *s, int fd)
{
	if (s == NULL)
		return _puts("(null)");
	else
		return (write(fd, s, strlen(s)));
}

int _puts(char *s)
{
	return (_fputs(s, STDOUT_FILENO));
}

int _putchar(char c)
{
	return (_fputs(&c, STDOUT_FILENO));
}

int trim(char **s)
{
	char   *tmp  = *s;
	size_t it  = 0;
	int    len = strlen(tmp);
	char   *buff = malloc(len + 1);
	
	if (tmp == NULL || buff == NULL)
		return 0;

	if (!isspace(*tmp))
	{
		free(buff);
		return len;
	}

	while(isspace(*tmp))
		tmp++;

	while(*tmp) 
		buff[it++] = *tmp++;

	buff[it] = '\0';

	free(*s);

	*s = buff;
	return it;
}
