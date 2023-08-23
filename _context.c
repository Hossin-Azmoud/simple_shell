#include "_simple_shell.h"

/**
* check_context - function that checks the context of a buuf_cmmand.
* @buff: the buff that will be checked for context.
* Return: return context if found else.. NONE
*/
ctx_t *check_context(char *buff)
{
	size_t i = 0;
	size_t ctx_idx = 0;
	ctx_t *ctx_array = malloc(sizeof(ctx_t) * CTX_MAX);

	while (buff[i])
	{
		switch (buff[i])
		{
			case ';': {
				ctx_array[ctx_idx++] = JOIN;
			} break;
			case '&': {
				if (buff[i + 1] == buff[i])
				{
					ctx_array[ctx_idx++] = AND;
				}
			} break;
			case '|': {
				if (buff[i + 1] == buff[i])
				{
					ctx_array[ctx_idx++] = OR;
				}
			}
			default: {
			} break;
		}

		i++;
	}

	if (ctx_idx == 0)
	{
		free(ctx_array);
		return (NULL);
	}

	ctx_array[ctx_idx++] = END;
	ctx_array = realloc(ctx_array, sizeof(ctx_t) * ctx_idx);
	return (ctx_array);
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

	if (context == END)
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
		case END: {
			return ("NONE");
		} break;
		default: {
		} break;
	}

	return ("NONE");
}
