#include "inc.h"

char *ft_strdup(const char *s1)
{
	char *s2;

	if ((s2 = (char *)malloc((sizeof(char) * ft_strlen(s1)) + 1)) == NULL)
		return (NULL);
	return (ft_strcpy(s2, s1));
}