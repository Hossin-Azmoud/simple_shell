#include "_simple_shell.h"
/**
* set__env - builtin function for the set command.
* Return: Void
*/
void set__env(void)
{
	/* setenv VARIABLE VALUE */
	char **args = reader(GET_TOKENS);
	int  count  = _strlen2d(args);

	if (count >= 3)
	{
		_set_env(args[1], args[2]);
		return;
	}

	fprintf(stderr, "Error! \n");
}

/**
* unset__env - builtin function for the unset command.
* Return: Void
*/
void unset__env(void)
{
	char **args = reader(GET_TOKENS);
	int  count  = _strlen2d(args);
	/* unsetenv VARIABLE */

	if (count >= 2)
	{
		env_manager(DELETE_ENTRY, args[1], NULL);
		return;
	}

	fprintf(stderr, "Error!\n");
}
