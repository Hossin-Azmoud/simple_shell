#include "_simple_shell.h"

/**
 * env_manager - function that manage the enviromnent
 * @action: check the arg
 * @key: check the arg
 * @value: check the arg
 * Return: for any case you have
 */
void *env_manager(env_action_t action, char *key, char *value)
{
	static map_t *env_map;

	switch (action)
	{
		case PRINT_ENV: {
			print_2d(env_map->all);
			return (NULL);
		} break;
		case INIT_ENV: {
			env_map = create_map(ENV_MAX);
			if (__environ != NULL)
			{
				map_cpy(env_map, __environ);
				return (NULL);
			}
			set_value(env_map, "SHLVL", "0");
		} break;
		case SET_ENTRY: {
			set_value(env_map, key, value);
		} break;
		case GET_VALUE: {
			return (get_value(env_map, key));
		} break;
		case GET_KEYS: {
			return (env_map->keys);
		} break;
		case DELETE_ENTRY: {
			printf("UNREACHABLE, not implemented..\n");
		} break;
		case CLEAR_ENV: {
			distroy_map(env_map);
		} break;
		case GET_MAP: {
			return (env_map);
		} break;
		default:
			printf("UNREACHABLE.\n");
			break;
	}
	return (NULL);
}

/**
 * release_env_ - function that release enviromnent
 *
 */

void release_env_(void)
{
	env_manager(
		CLEAR_ENV,
		NULL,
		NULL
	);
}

/**
 * _get_env - function get the enviromnent
 * @key: argument
 * Return: the enviromnent manager function
 *
 */

char *_get_env(char *key)
{
	return ((char *) env_manager(
		GET_VALUE,
		key,
		NULL
	));
}

/**
 * _set_env - function that set the enviromnent
 * @key: check the argument
 * @value: check the argument
 *
 */

void _set_env(char *key, char *value)
{
	env_manager(
		SET_ENTRY,
		key,
		value
	);
}
