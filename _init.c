#include "_simple_shell.h"
void init_environment()
{
	init_builtins();
	init_env_manager();
	init_path_manager();
	init_state_manager();
}
	
void uinit_environment()
{
	release_path();
	release_env_();
	reader(FREE);
}

