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
	meta->prompt = _strdup("SHELL@"); /* note: free it */
	sz = (_strlen(meta->prompt) + _strlen(meta->uname) + _strlen(meta->pwd) + 7);
	meta->prompt = realloc(meta->prompt, sz);
	meta->prompt = _strcat(meta->prompt, meta->uname);
	meta->prompt = _strcat(meta->prompt, "(");
	meta->prompt = _strcat(meta->prompt, meta->pwd);
	meta->prompt = _strcat(meta->prompt, ") ");

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
