#include "_simple_shell.h"
/**
 * _set_env - function that set the enviromnent
 * @key: check the argument
 * @value: check the argument
 * Return: Void!
 */
void _set_env(char *key, char *value)
{
	env_manager(
		SET_ENTRY,
		key,
		value
	);
}

/**
 * set_builtin - function that set builtins
 * @name: check the arg
 * @f: check the arg
 * Return: Void
 */
void set_builtin(char *name, void (*f)())
{
	builtins_manager(SET_BUILTN, name, f);
}

/**
 * set_value - function that get the value of map
 * @m : the map
 * @key: the argument key
 * @value: the value we want to set
 */
void set_value(map_t *m, char *key, char *value)
{
	int idx = 0;

	while (m->keys[idx])
	{
		if (_strcmp(m->keys[idx], key) == 0)
		{
			free((m)->values[idx]);

			(m)->values[idx] = malloc(_strlen(value) + 1);
			(m)->values[idx] = _strcpy((m)->values[idx], value);

			free((m)->all[idx]);

			(m)->all[idx] = malloc(_strlen(key) + _strlen(value) + 2);
			(m)->all[idx] = _strcpy((m)->all[idx], key);
			(m)->all[idx] = _strcat((m)->all[idx], "=");
			(m)->all[idx] = _strcat((m)->all[idx], value);
			return;
		}

		idx++;
	}

	if (idx > (m)->cap)
	{
		fprintf(stderr, "Map was exauhsted..\n");
		return;
	}

	append_entry(m, NULL, key, value);
}

