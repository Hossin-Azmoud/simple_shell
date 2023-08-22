#include "_simple_shell.h"
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

