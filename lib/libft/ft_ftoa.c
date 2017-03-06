#include <math.h>
#include "includes/libft.h"

char	*ft_ftoa(float nb, int precision)
{
	char	*str;

	str = ft_itoa((int)nb);
	nb = nb - (int)nb;
	nb = nb * pow(10, precision);
	str = ft_strjoin(str, ".");
	str = ft_strjoin(str, ft_itoa((int)nb));
	return (str);
}
