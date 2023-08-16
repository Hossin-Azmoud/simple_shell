#include "_simple_shell.h"

builtin_func_t *builtins_manager(builtins_action_t action, char *name, void (*f)())
{
	builtin_func_t *temp_func;
	int it = 0;
	static builtin_func_t funcs[BUILTINS_MAX_SIZE];
	static int size;

	switch(action)
	{
		case INIT_BUILTN: {
			size = 0;
		} break;

		case GET_BUILTN: {
			while (it < size)
			{
				temp_func = (funcs + it);
				if (_strcmp(temp_func->name, name) == 0)
					return temp_func;
				it++;
			}

			return NULL;
		} break;
		case SET_BUILTN: {

			if (name == NULL)
				return NULL;

			if (f == NULL)
				return NULL;

			if (size == BUILTINS_MAX_SIZE)
				return NULL;

			temp_func       = (funcs + size);
			strcpy(temp_func->name, name);
			temp_func->f    = f;
			size++;

		} break;
		default:
			break;
	}

	return NULL;
}

void init_builtins()
{
	builtins_manager(INIT_BUILTN, NULL, NULL);

	set_builtin("exit", __exit_shell);
	set_builtin("env",  print_env);
	set_builtin("path", print_path);
	set_builtin("cd", change_dir);
	set_builtin("clear", clear);
}

builtin_func_t *get_builtin(char *name)
{
	return builtins_manager(GET_BUILTN, name, NULL);
}

void set_builtin(char *name, void (*f)())
{
	builtins_manager(SET_BUILTN, name, f);
}
