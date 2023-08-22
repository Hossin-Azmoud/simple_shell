#include "_simple_shell.h"

/**
* exclude_comments - functions to remove all the comments from a line.
* @buff: buff that holds the entire line.
* Return: The line that has no lines.
*/

char *exclude_comments(char *buff)
{
	char *new;
	int it = 0;

	if (!buff)
		return (buff);

	new = malloc(_strlen(buff) + 1);
	while (buff[it] && buff[it] != '#')
	{
		new[it] = buff[it];
		it++;
	}

	if (buff[it] == '#')
	{
		if (it >= 1)
		{
			if (buff[it - 1] != ' ')
			{
				free(new);
				return (buff);
			}
		}
	}

	new[it] = 0;
	free(buff);
	return (new);
}
