#include "_simple_shell.h"

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

