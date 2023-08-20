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
		(m)->all[idx]    = malloc(strlen(entry) + 1);
		(m)->all[idx]    = strcpy((m)->all[idx], entry);
		(m)->keys[idx]   = malloc(strlen(kv[0]) + 1);
		(m)->keys[idx]   = strcpy((m)->keys[idx], kv[0]);
	
		if (kv[1])
		{
			(m)->values[idx] = malloc(strlen(kv[1]) + 1);
			(m)->values[idx] = strcpy((m)->values[(m->size)], kv[1]);
		} else
		{
			(m)->values[idx] = NULL; 
		}

		free_2d(kv);
		(m)->size++;
		return;

	} else if (!entry && key && value)
	{
		(m)->keys[idx]   = strdup(key);
		(m)->values[idx] = strdup(value);
		(m)->all[idx]    = malloc(strlen(key) + strlen(value) + 2);
		(m)->all[idx]    = strcpy((m)->all[idx], key);
		(m)->all[idx]    = strcat((m)->all[idx], "=");
		(m)->all[idx]    = strcat((m)->all[idx], value);
		(m)->size++;
		
		return;
	}

	fprintf(stderr, "invalid input was supplied to `append_entry` function.\n");
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
				return (strdup((m)->values[iter]));
			return (NULL);
		}

		iter++;
	}

	return (NULL);
}
