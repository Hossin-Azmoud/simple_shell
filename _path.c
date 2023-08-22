#include "_simple_shell.h"
/**
* path_manager - function that manage the path
* @action: the action of the argument
* @cmd_loc: check the argument
* @res: the result of the arguments
*/
void path_manager(path_action_t action, char **cmd_loc, int *res)
{
	static char **path_ = { 0 };

	switch (action)
	{
		case PRINT_PATH: {
			print_2d(path_);
		} break;
		case INIT_PATH: {
			path_ = get_tokenized_path();
		} break;
		case FIND_CMD: {
			find_cmd(cmd_loc, path_, res);
		} break;
		case CLEAR_PATH: {
			free_2d(path_);
		} break;
		default:
			printf("UNREACHABLE.! `path_manager`\n");
			break;
	}
}

/**
* print_path - function that print the path
*
*/
void  print_path(void)
{
	path_manager(PRINT_PATH, NULL, NULL);
}

/**
 * is_relative - checks if a path (p) is relative or not.
 * @p: path.
 * Return: (1) if relative else (0)
 */
static int is_relative(char *p)
{
	char *ptr = p;

	if (ptr == NULL)
		return (0);

	switch (*ptr)
	{
		case '.': {
			ptr++;
			if (*ptr == '/')
			{
				return (1);
			}

			if (*ptr == '.') /* .. */
			{
				ptr++;
				if (*ptr == '/')
				{
					return (1);
				}
			}

			return (0);
		} break;
		case '/': {
			return (1);
		} break;
		default: {

		} break;
	}

	return (0);

}

/**
* find_cmd - function that find the path
* @cmd_loc: check the argument
* @paths: the path or the argument
* @result_: the result of the arguments
*/
void find_cmd(char **cmd_loc, char **paths, int *result_)
{
	int i = 0, res;
	char *copy = NULL;

	if (is_relative(*cmd_loc))
	{
		res = access(*cmd_loc, X_OK);
		if (res != -1)
		{
			*result_ = 1;
			return;
		}
		*result_ = 0;
		return;
	}

	if (paths == NULL)
	{
		*result_ = 0;
		return;
	}

	for (i = 0; paths[i] != NULL; ++i, copy = NULL)
	{
		copy = _join_with_path(paths[i], *cmd_loc);
		res  = access(copy, X_OK);
		if (res != -1)
		{
			free(*cmd_loc);
			*cmd_loc = copy;
			*result_ = 1;
			return;
		}
		free(copy);
	}
	*result_ = 0;
}
