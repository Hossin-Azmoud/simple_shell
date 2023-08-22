#include "_simple_shell.h"
/**
* split_by_delim - function that split by delim
* @buffer: the buffer to use
* @delim: the argument to use
* Return: the size
*/
char **split_by_delim(char *buffer,  char *delim)
{
	int  cap = 2;
	int  it  = 0;
	char *tmp;
	char **tokens;
	char *bcopy;

	tokens = malloc(sizeof(char *) * cap);
	bcopy  = malloc(_strlen(buffer) + 1);
	bcopy  = _strcpy(bcopy, buffer);
	tmp    = strtok(bcopy, delim);

	while (tmp != NULL)
	{
		if (it == cap - 1)
		{
			tokens = realloc(tokens, sizeof(char *) * cap * 2);
			cap *= 2;
		}

		(tokens)[it] = malloc(_strlen(tmp) + 1);
		(tokens)[it] = _strcpy((tokens)[it], tmp);
		tmp          = strtok(NULL, delim);
		it++;
	}

	tokens     =  realloc(tokens, sizeof(char *) * (it + 1));
	tokens[it] =  NULL;
	free(bcopy);
	return (tokens);
}

