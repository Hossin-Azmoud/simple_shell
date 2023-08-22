#include "_simple_shell.h"

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
			(m)->all[idx] = strcat((m)->all[idx], "=");
			(m)->all[idx] = strcat((m)->all[idx], value);

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

/**
* distroy_map - function distroying the map
* @m: the argument of the map
*/
void distroy_map(map_t *m)
{
	free_n2d((m)->keys,   (m)->size);
	free_n2d((m)->values, (m)->size);
	free_n2d((m)->all,	  (m)->size);
	free((m));
}

/**
* map_cpy - function that copy the map
* @m: the map
* @src: the source we want to copy
*/
void map_cpy(map_t *m, char **src)
{
	int it;

	for (it = 0; src[it]; ++it)
		append_entry(m, src[it], NULL, NULL);

	/* terminate the map. */
	(m)->all[(m)->size]    = NULL;
	(m)->keys[(m)->size]   = NULL;
	(m)->values[(m)->size] = NULL;
}
