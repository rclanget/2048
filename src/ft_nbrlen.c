#include "inc.h"

int ft_nbrlen(int n)
{
	int i;

	i = 0;
	while (n && ++i)
		n /= 10;
	return (i);
}