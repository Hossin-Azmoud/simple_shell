#include "_simple_shell.h"
/**
* path_manager - function that manage the path
* @action: the action of the argument
* @cmd_loc: check the argument
* @res: the result of the arguments
*/
void path_manager(path_action_t action, char **cmd_loc, int *res)
{
	static char **path_;

	switch (action)
	{
		case PRINT_PATH: {
			print_2d(path_);
		} break;
	    case INIT_PATH: {
			path_ = get_tokenized_path(void);
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
* find_cmd - function that find the path
* @cmd_loc: check the argument
* @paths: the path or the argument
* @result_: the result of the arguments
*/
void find_cmd(char **cmd_loc, char **paths, int *result_)
{
	int i = 0;
	int res;
	char *copy = NULL;
	int path_size;

	res = access(*cmd_loc, X_OK);

	if (res != -1)
	{
		*result_ = 1;
		return;
	}

	while (paths[i] != NULL)
	{
		path_size = (strlen(paths[i]) + strlen(*cmd_loc) + 2);
		copy      = (char *) malloc(path_size);

		strcpy(copy, paths[i]);
		strcat(copy, "/");
		strcat(copy, *cmd_loc);

		res = access(copy, X_OK);

		if (res != -1)
		{
			free(*cmd_loc);
			*cmd_loc = malloc(path_size);
			strcpy(*cmd_loc, copy);
			free(copy);
			*result_ = 1;
			return;
		}

		i++;
		free(copy);
		copy = NULL;
	}

	*result_ = 0;
}
/**
* init_path_manager - function that initial the path
*
*/
void init_path_manager(void)
{
	path_manager(INIT_PATH, NULL, NULL);
}
/**
* release_path - function that release the path
*
*/
void  release_path(void)
{
	path_manager(CLEAR_PATH, NULL, NULL);
}

