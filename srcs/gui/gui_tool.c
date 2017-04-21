#include <gui.h>

char	*str_tolower(char *str)
{
	unsigned int	i;
	char			*tmp;

	i = 0;
	if (!(tmp = (char *)malloc(sizeof(char) * 10)))
		error(1);
	while (i < ft_strlen(str))
	{
		if (str[i] >= 65 && str[i] <= 90)
			tmp[i] = str[i] + 32;
		else
			tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
