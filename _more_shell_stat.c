#include "_simple_shell.h"
/**
* get_status - function that get the status
* Return: shell state manager with the status of the line
*/
int get_status(void)
{
	return (*(int *)shell_state_manager(GET_STATUS, 0, NULL));
}
/**
* set_status - function that set the status in of index
* @payload: the arguments
*/
void set_status(int payload)
{
	shell_state_manager(SET_STATUS, payload, NULL);
}
/**
* init_state_manager - function that initial the state manage
*
*/
void init_state_manager(void)
{
	shell_state_manager(INIT_STATE, 0, NULL);
}
/**
* set_shell_name - function that initial the state manage
* @name: the name
*/
void set_shell_name(char **name)
{
	shell_state_manager(SET_SHELL_NAME, 0, name);
}
/**
* get_shell_name - function that initial the state manage
* Return: the shell state manager
*/
char *get_shell_name(void)
{
	return ((char *) shell_state_manager(GET_SHELL_NAME, 0, NULL));
}
