#include "_simple_shell.h"
/**
 * prompt_user - function take the prompt of the user
 */
void prompt_user(void)
{
	char *header = get_shell_header();

	_puts(header);
	_puts("\n-> ");

	free(header);
}
/*
typedef struct meta_data_s
{
	char *uname;
	char *pwd;
	char *prompt;
} meta_data_t;
*/
char *get_shell_header(void)
{
	/* SHELL@USER :: (PWD)*/
	char *first_con	= "SHELL :: ";
	char *user_name = _get_env("USER");
	char *header    = malloc(strlen(first_con) + strlen(user_name) + 1);

	header = strcpy(header, first_con);
	header = strcat(header, user_name);

	return (header);
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
