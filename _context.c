#include "_simple_shell.h"

/**
* check_context - function that checks the context of a buuf_cmmand.
* @buff: the buff that will be checked for context.
* Return: return context if found else.. NONE
*/
ctx_t check_context(char *buff)
{
	size_t i = 0;
	while (buff[i])
	{
		switch (buff[i])
		{
			case ';': {
				return (JOIN);
			} break;
			case '&': {
				if (buff[i + 1] == buff[i])
				{
					return (AND);
				}
			} break;
			case '|': {
				if (buff[i + 1] == buff[i])
				{
					return (OR);
				}
			}

			default: {} break;
		}

		i++;
	}
	return (NONE);
}
/**
* context_based_split - split using given context delimeter.
* @context: the context.
* @buff: buffer to split.
* Return: An array of commands or NULL
*/
char **context_based_split(ctx_t context, char *buff)
{
	char *delim = NULL;

	if (context == JOIN)
		delim = ";";

	if (context == OR)
		delim = "||";

	if (context == AND)
		delim = "&&";

	if (context == NONE)
		return (NULL);

	return (split_by_delim(buff,  delim));
}
/**
* ctx_str - function that returns a context as a str.
* @context: the context.
* Return: return any context as a stack string.
*/
char *ctx_str(ctx_t context)
{
	switch (context)
	{
		case JOIN: {
			return ("JOIN");
		} break;
		case OR: {
			return ("OR");
		} break;
		case AND: {
			return ("AND");
		} break;
		case NONE: {
			return ("NONE");
		} break;
		default: {
		} break;
	}

	return ("NONE");
}
