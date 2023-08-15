#include "_simpe_shell.h"
/**
* get_status - function that get the status 
* Return: shell state manager with the status of the line
*/
int get_status(void)
{
	return (shell_state_manager(GET_STATUS, 0));
}

void set_status(int payload)
{
	shell_state_manager(SET_STATUS, payload);
}

void init_state_manager(void)
{
	shell_state_manager(INIT_STATE, 0);
}
