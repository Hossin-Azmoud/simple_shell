#include "_simple_shell.h"

/**
 * create_map - function that create map
 * @size: size of the map
 * Return: it return the map with m
 */
map_t *create_map(size_t size)
{
	int storage = (sizeof(char *) * size);
	map_t *m = malloc(sizeof(map_t));

	m->keys    = (char **)malloc(storage);
	m->all     = (char **)malloc(storage);
	m->values  = (char **)malloc(storage);
	m->cap     = size;
	m->size    = 0;

	return (m);
}
/**
 * append_entry - the function appends the entry
 * @m: the map
 * @entry: the entry want to append
 * @key: check the argument
 * @value: the value of key
 */
void append_entry(map_t *m, char *entry, char *key, char *value)
{
	char **kv;
	int idx = (m)->size;

	if (!key && !value && entry)
	{
		kv  = split_by_delim(entry, "=");
		(m)->all[idx]    = malloc(_strlen(entry) + 1);
		(m)->all[idx]    = _strcpy((m)->all[idx], entry);
		(m)->keys[idx]   = malloc(_strlen(kv[0]) + 1);
		(m)->keys[idx]   = _strcpy((m)->keys[idx], kv[0]);

		if (kv[1])
		{
			(m)->values[idx] = malloc(_strlen(kv[1]) + 1);
			(m)->values[idx] = _strcpy((m)->values[(m->size)], kv[1]);
		} else
		{
			(m)->values[idx] = NULL;
		}

		free_2d(kv);
		(m)->size++;
		return;

	} else if (!entry && key && value)
	{
		(m)->keys[idx]   = _strdup(key);
		(m)->values[idx] = _strdup(value);
		(m)->all[idx]    = malloc(_strlen(key) + _strlen(value) + 2);
		(m)->all[idx]    = _strcpy((m)->all[idx], key);
		(m)->all[idx]    = _strcat((m)->all[idx], "=");
		(m)->all[idx]    = _strcat((m)->all[idx], value);
		(m)->size++;

		return;
	}
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
