#include "_simple_shell.h"

/**
 * get_envp_map - function that return the env
 *                      map and manage it
 * Return: env manager function
 */

map_t *get_envp_map(void)
{
	return ((map_t *) env_manager(GET_MAP, NULL, NULL));
}

/**
 * _get_env - function get the enviromnent
 * @key: argument
 * Return: the enviromnent manager function
 */
char *_get_env(char *key)
{
	return ((char *) env_manager(
		GET_VALUE,
		key,
		NULL
	));
}

/**
 * get_builtin - function that get built
 * @name: check the arg
 * Return: the function of builtins
 */
builtin_func_t *get_builtin(char *name)
{
	return (builtins_manager(GET_BUILTN, name, NULL));
}

/**
 * get_value - function that get the value of map
 * @m : the map
 * @key: the argument key
 * Return: the value we want
 */
char *get_value(const map_t *m, char *key)
{
	int iter = 0;

	while ((m)->keys[iter])
	{
		if (_strcmp((m)->keys[iter], key) == 0)
		{
			if (((m)->values[iter]))
				return (_strdup((m)->values[iter]));
			return (NULL);
		}

		iter++;
	}

	return (NULL);
}
