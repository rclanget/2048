#include "inc.h"

int		ft_countnbr(int n)
{
	int		len;
	int		positive;

	len = 1;
	positive = 0;
	if (n < 0)
	{
		n *= -1;
		positive = 1;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len + positive);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		i;
	int		len;

	i = 0;
	len = ft_countnbr(n);
	if (!(dest = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	dest[len] = '\0';
	if (n == -2147483648)
		return (strdup("-2147483648"));
	if (n < 0)
	{
		n *= -1;
		dest[i++] = '-';
	}
	i = (len - 1);
	while (n > 9)
	{
		dest[i--] = ((n % 10) + 48);
		n /= 10;
	}
	if (n < 10)
		dest[i--] = (n + 48);
	return (dest);
}