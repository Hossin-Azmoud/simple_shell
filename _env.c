#include "_simple_shell.h"


void *env_manager(env_action_t action, char *key, char *value)
{

	static map_t *env_map;
	switch(action)
	{
		case PRINT_ENV: {
			print_env_internal(env_map);
			return NULL;
		} break;
		case INIT_ENV: {
			env_map = create_map(ENV_MAX);
			map_cpy(env_map, __environ);
		} break;
		case SET_ENTRY: {
			set_value(env_map, key, value);
		} break;
		case GET_VALUE: {
			return get_value(env_map, key);
		} break;
		case GET_KEYS: {
			return env_map->keys;
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


void release_env_()
{
	env_manager(
		CLEAR_ENV, 
		NULL, 
		NULL
	);
}

char *_get_env(char *key)
{
	return (char *) env_manager(
		GET_VALUE, 
		key, 
		NULL
	);
}

void _set_env(char *key, char *value)
{
	env_manager(
		SET_ENTRY, 
		key, 
		value
	);
}

void print_env()
{
	env_manager(PRINT_ENV, NULL, NULL);
}

void print_env_internal(map_t *m)
{
	char **env = m->all;
	print_2d(env);
}

map_t *get_envp_map()
{
	return (map_t *) env_manager(GET_MAP, NULL, NULL);
}

void  init_env_manager()
{
	env_manager(INIT_ENV, NULL, NULL);
}
