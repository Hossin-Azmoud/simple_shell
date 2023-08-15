#include "_simple_shell.h"
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
* free_n2d - function free the array
* @Array: the array will be free
*/
void free_2d(char **Array)
{
	int	it = 0;

	if (Array == NULL)
		return;

	while (Array[it]) /* VALGRIND COMPLAINS */
	{
		free(Array[it]);
		it++;
	}

	free(Array);
}

