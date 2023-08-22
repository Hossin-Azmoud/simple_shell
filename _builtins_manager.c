#include "_simple_shell.h"

/**
 * builtins_manager - function that manage builtins functions
 * @action: argument
 * @name: Check the arg
 * @f: check the arg
 * Return: function or null
 */
builtin_func_t
*builtins_manager(builtins_action_t action, char *name, void (*f)())
{
	builtin_func_t *temp_func;
	int it = 0;
	static builtin_func_t funcs[BUILTINS_MAX_SIZE];
	static int size;

	switch (action)
	{
		case INIT_BUILTN: {
			size = 0;
		} break;

		case GET_BUILTN: {
			while (it < size)
			{
				temp_func = (funcs + it);
				if (_strcmp(temp_func->name, name) == 0)
					return (temp_func);
				it++;
			}

			return (NULL);
		} break;
		case SET_BUILTN: {

			if (name == NULL)
				return (NULL);


			if (f == NULL)
				return (NULL);


			if (size == BUILTINS_MAX_SIZE)
				return (NULL);

			temp_func       = (funcs + size);
			_strcpy(temp_func->name, name);
			temp_func->f    = f;
			size++;

		} break;
		default:
			break;
	}

	return (NULL);
}
