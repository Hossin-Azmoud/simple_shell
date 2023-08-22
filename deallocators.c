#include "_simple_shell.h"

/**
* distroy_map - function distroying the map
* @m: the argument of the map
* Return: void
*/
void distroy_map(map_t *m)
{
	free_n2d((m)->keys,   (m)->size);
	free_n2d((m)->values, (m)->size);
	free_n2d((m)->all,	  (m)->size);
	free((m));
}

/**
 * distroy_env_ - function that release enviromnent
 * Return: void
 */
void distroy_env_(void)
{
	env_manager(
		CLEAR_ENV,
		NULL,
		NULL
	);
}

/**
* free_n2d - function free the array
* @Array: the array will be free
* @n: the argument or index
*/
void  free_n2d(char **Array, int n)
{
	int	it = 0;

	if (Array == NULL)
		return;

	while (it < n)
	{
		if (Array[it])
			free(Array[it]);

		it++;
	}

	free(Array);
}

/**
* free_2d - function free the array
* @Array: the array will be free
*/
void free_2d(char **Array)
{
	int	it = 0;

	if (Array == NULL)
		return;

	while (Array[it])
	{
		free(Array[it]);
		it++;
	}

	free(Array);
}

/**
* distroy_path - function that release the path
* Return: void
*/

void distroy_path(void)
{
	path_manager(CLEAR_PATH, NULL, NULL);
}

