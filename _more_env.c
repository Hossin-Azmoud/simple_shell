#include "_simple_shell.h"

/**
 * print_env - function that print the env
 */

void print_env(void)
{
	env_manager(PRINT_ENV, NULL, NULL);
}


/**
 * get_envp_map - function that return the env
 *                      map and manage it
 * Return: env manager function
 */

map_t *get_envp_map(void)
{
	return ((map_t *) env_manager(GET_MAP, NULL, NULL));
}

/**
 * init_env_manager - function manage the init
 */

void  init_env_manager(void)
{
	env_manager(INIT_ENV, NULL, NULL);
}
