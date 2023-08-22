#include "_simple_shell.h"

/**
 * _strcat - function that concats 2 strings
 * @dst: destination string.
 * @src: the src that will be concated.
 * Return: pointer to concated string.
 */
char *_strcat(char *dst, char *src)
{
	size_t dst_sz, src_sz, it = 0;

	if (!dst && !src)
		return (NULL);

	dst_sz = _strlen(dst);
	src_sz = _strlen(src);
	dst    = realloc(dst, dst_sz + src_sz + 1);

	while (src[it])
	{
		dst[dst_sz + it] = src[it]; /* dst_sz is an offset. */
		it++;
	}
	dst[dst_sz + it] = 0;
	return (dst);
}
