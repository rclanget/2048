#include "inc.h"

char *ft_strcpy(char *dest, const char *src)
{
	char *p;

	if ((p = dest) == NULL)
		return (NULL);
	while ((*p++ = *src++) != 0)
		continue ;
	return (dest);
}