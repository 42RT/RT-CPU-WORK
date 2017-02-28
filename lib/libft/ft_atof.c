#include <libft.h>
#include <math.h>

float	ft_atof_ext(char *str, int i, float a, int sign)
{
	int j;

	j = 0;
	if (str[i] == '.')
	{
		++i;
		while (ft_isdigit(str[i + j]))
			++j;
		if (sign == 0)
			a = a + (float)ft_atoi(str + i) / pow(10, j);
		else
			a = a - (float)ft_atoi(str + i) / pow(10, j);
	}
	return (a);
}

float	ft_atof(char *str)
{
	float a;
	int i;
	int sign;

	i = 0;
	sign = 0;
	a = 0.0;
	while (!ft_isdigit(str[i]) && str[i] != '-')
		++i;
	if (str[i] == '-')
		sign = 1;
	a = (float)ft_atoi(str + i);
	while (str[i] != '.' && (ft_isdigit(str[i]) || str[i] == ' ' ||
				str[i] == '-'))
		++i;
	a = ft_atof_ext(str, i, a, sign);
	return (a);
}
