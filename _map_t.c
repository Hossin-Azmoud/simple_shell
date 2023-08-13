#include "_simple_shell.h"

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

void append_entry(map_t *m, const char *entry, const char *key, const char *value)
{
	char **kv;
	int idx = (m)->size;

	if (!key && !value && entry)
	{
		kv                     = split_by_delim(entry, "=");
		(m)->all[idx]    = malloc(strlen(entry) + 1);
		(m)->keys[idx]   = malloc(strlen(kv[0]) + 1);	
		(m)->values[idx] = malloc(strlen(kv[1]) + 1);

		(m)->all[idx]    = strcpy((m)->all[idx], entry);
		(m)->values[idx] = strcpy((m)->values[(m->size)], kv[1]);
		(m)->keys[idx]   = strcpy((m)->keys[idx], kv[0]);

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

char *get_value(const map_t *m, const char *key)
{
	int iter = 0;

	while((m)->keys[iter])
	{
		if (strcmp((m)->keys[iter], key) == 0)
			return strdup((m)->values[iter]);

		iter++;
	}

	return NULL;
}

void set_value(map_t *m, const char *key, const char *value)
{
	int idx = 0;

	while(m->keys[idx])
	{
		if (strcmp(m->keys[idx], key) == 0)
		{
			free((m)->values[idx]);
			
			(m)->values[idx] = malloc(strlen(value) + 1);
			(m)->values[idx] = strcpy((m)->values[idx], value);
			
			free((m)->all[idx]);
			
			(m)->all[idx] = malloc(strlen(key) + strlen(value) + 2);
			(m)->all[idx] = strcpy((m)->all[idx] , key);
			(m)->all[idx] = strcat((m)->all[idx], "=");
			(m)->all[idx] = strcat((m)->all[idx] , value);

			return;
		}

		idx++;
	}

	if (idx > (m)->cap)
	{
		fprintf(stderr, "THE CAP THAT WAS INITIALIZED FOR THE MAP IS NOT ENOUGH TO STORE NEW VALUES.\n");
		return;
	}

	append_entry(m, NULL, key, value);
}

void distroy_map(map_t *m)
{
	free_n2d((m)->keys,   (m)->size);
	free_n2d((m)->values, (m)->size);
	free_n2d((m)->all,	  (m)->size);
	free((m));
}

void map_cpy(map_t *m, char **src)
{
	int it;

	for (it = 0; src[it]; it++)
		append_entry(m, src[it], NULL, NULL);

	(m)->all[(m)->size] = NULL;
}
