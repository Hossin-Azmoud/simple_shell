#include "_simple_shell.h"
/**
* _strlen2d - a function that gets the size of a string
*				in 2 dimention
* @array: the array want to strlen
* Return: the size
*/
int _strlen2d(char **array)
{
	int sz = 0;

	if (array == NULL)
		return (sz);

	while (array[sz] != NULL)
		sz++;

	return (sz);
}

/**
* _strcmp - function that compares two strings
* @s1: string
* @s2: string
* Return: 0 if s1 == s2 and 1 otherwise
*/
int _strcmp(char *s1, char *s2)
{
	int it = 0;

	while (s1[it] && s2[it])
	{
		if (s1[it] != s2[it])
			break;

		it++;
	}

	if (s1[it] == '\0' && s2[it] == '\0')
		return (0);

	return (s1[it] - s2[it]);
}


/**
* _strlen - a function that gets the size of a string.
* @s: pointer to string to be processed.
* Return: int size of the passed string.
*/
int _strlen(char *s)
{
	int it = 0;

	if (s == NULL)
		return (0);

	while (s[it] != '\0')
		it++;

	return (it);
}
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
	return (tokens);
}

