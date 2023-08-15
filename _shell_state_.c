#include "_simple_shell.h"
/**
* shell_state_manager - function that manage the shell
* @action: the action or the argument
* @payload: the argument
* Return: the return in switch cases
*/
int shell_state_manager(shell_state_action_t action, int payload)
{
	static shell_state_t state;

	switch (action)
	{
		case INIT_STATE: {
			state.latest_status = 0;
			state.line_idx      = 0;
		} break;

		case INCR_INDEX: {
			state.line_idx++;
		} break;
		case GET_INDEX: {
			return (state.line_idx);
		} break;
		case SET_STATUS: {
			state.latest_status = payload;
		} break;
		case GET_STATUS: {
			return (state.latest_status);
		} break;
	}

	return (0);
}
/**
* get_line_index - function that get the line in of index
* Return: shell state manager with the index of the line
*/
int get_line_index(void)
{
	return (shell_state_manager(GET_INDEX, 0));
}
/**
* inc_line_index - function that incrementate the line in of index
* Return: shell state manager with the index of the line in file
*/
void inc_line_index(void)
{
	shell_state_manager(INCR_INDEX, 0);
}
