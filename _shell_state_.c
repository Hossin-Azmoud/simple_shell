#include "_simple_shell.h"

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
			return state.line_idx;
		} break;
		case SET_STATUS: {
			state.latest_status = payload;
		} break;
		case GET_STATUS: {
			return state.latest_status;
		} break;
	}

	return 0;
}

int get_line_index()
{
	return shell_state_manager(GET_INDEX, 0);
}

void inc_line_index()
{
	shell_state_manager(INCR_INDEX, 0);
}

int get_status()
{
	return shell_state_manager(GET_STATUS, 0);
}

void set_status(int payload)
{
	shell_state_manager(SET_STATUS, payload);
}

void init_state_manager()
{
	shell_state_manager(INIT_STATE, 0);
}
