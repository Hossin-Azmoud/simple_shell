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

/**
* _strlen - a function that gets the size of a string.
* @s: pointer to string to be processed.
* Return: int size of the passed string.
*/
int _strlen(const char *s)
{
	int it = 0;
	
	if (s == NULL)
		return (0);

	while (s[it] != '\0')
		it++;

	return (it);
}

char **split_by_delim(const char *buffer, const char *delim)
{
	int  cap = 2;
	int  it  = 0;
	char *tmp;
	char **tokens;
	char *bcopy;

	tokens  = malloc(sizeof(char *) * cap);
	bcopy   = malloc(_strlen(buffer) + 1);
	bcopy = strcpy(bcopy, buffer);
	tmp   = strtok(bcopy, delim);

	while (tmp != NULL)
	{
		if (it == cap - 1)
		{
			tokens = realloc(tokens, sizeof(char *) * cap * 2);
			cap *= 2;
		}

		(tokens)[it] = malloc(strlen(tmp) + 1);
		(tokens)[it] = strcpy((tokens)[it], tmp);
		tmp          = strtok(NULL, delim);
		it++;
	}

	tokens     =  realloc(tokens, sizeof(char *) * (it + 1));
	tokens[it] =  NULL;
	free(bcopy);
	return tokens;
}
