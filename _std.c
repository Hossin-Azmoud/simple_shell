#include "_simple_shell.h"


/**
 * get_meta - get meta data for the shell
 * it gets the user name, the pwd, the prompt.
 * Return: meta data.
 */
static meta_data_t *get_meta(void)
{
	meta_data_t *meta = malloc(sizeof(meta_data_t));
	int sz;

	if (meta == NULL)
		return (NULL);

	meta->uname  = _get_env("USER");
	meta->pwd    = _get_env("PWD");
	meta->prompt = strdup("SHELL@"); /* note: free it */
	sz = (_strlen(meta->prompt) + _strlen(meta->uname) + _strlen(meta->pwd) + 7);
	meta->prompt = realloc(meta->prompt, sz);
	meta->prompt = strcat(meta->prompt, meta->uname);
	meta->prompt = strcat(meta->prompt, "(");
	meta->prompt = strcat(meta->prompt, meta->pwd);
	meta->prompt = strcat(meta->prompt, ") ");

	return (meta);
}
/**
 * prompt_user - function take the prompt of the user
 */
void prompt_user(void)
{
	meta_data_t *meta = get_meta();

	if (meta == NULL)
	{
		_puts("SHELL -> ");
		return;
	}

	_puts(meta->prompt);
	free(meta->prompt);
	free(meta->pwd);
	free(meta->uname);
	free(meta);
}

/**
* _getline - the function get the line
* @buff: the buffer use
* @size: the size of the buffer
* @fd: the argument
* Return: in condition -1 or the line
*/
int _getline(char **buff, size_t *size, int fd)
{
	int consume = 1, nread = 0;
	size_t it = 0;
	char c;

	*size = 16;
	*buff = malloc(*size);
	while (consume)
	{
		if (it == *size - 2)
		{
			*size *= 2;
			*buff = realloc(*buff, *size);
			if (buff == NULL)
				return (-1);
		}
		nread = read(fd, &c, 1);
		if (nread <= 0)
			break;
		switch (c)
		{
			case '\r':
			case '\n': {
				(*buff)[it] = 0;
				consume = 0;
			} break;
			case EOF: {
				return (-1);
			} break;
			default: {
				(*buff)[it] = c;
				it++;
			} break;
		}
	}
	if (it == 0 && nread == 0)
		return (-1);

	if (_sig_int(-1) == SIGINT)
		return (INTRPT_CODE);
	return (it);
}
