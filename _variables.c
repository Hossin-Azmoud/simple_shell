#include "_simple_shell.h"

/**
* check_variables - func that replaces variables with their values.
* @tokens: buff that holds command tokens.
* Return: new token array.
*/
char **check_variables(char **tokens)
{
	size_t len = (_strlen2d(tokens) + 1);
	size_t it  = 0;
	char **new = malloc(len * sizeof(char *));

	for (; it < len && (tokens[it] != NULL); ++it)
	{
		switch (tokens[it][0])
		{
			case '$': {
				if (tokens[it][1] == '$')
				{
					new[it] = __itoa((int)getpid());
					continue;
				}

				if (tokens[it][1] == '?')
				{
					new[it] = __itoa(get_status());
					continue;
				}

				new[it] = _get_env(tokens[it] + 1);
				if (!new[it])
				{
					new[it] = _strdup("");
				}
			} break;
			default: {
				new[it] = _strdup(tokens[it]);
			} break;
		}
	}

	free_2d(tokens);
	new[it] = NULL;
	return (new);
}
