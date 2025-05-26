#include "../../include/conway.h"

static bool	strict_atoll(const char *s, long long *result)
{
	long long	nbr;
	int			sign;

	nbr = 0;
	sign = 1;
	while (*s && ft_isspace(*s))
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s || !ft_isdigit(*s))
		return (false);
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		nbr = nbr * 10 + (*s - '0');
		s++;
	}
	*result = nbr * sign;
	return (true);
}

bool	strict_atoi(const char *s, int *result)
{
	long long	tmp;

	if (!strict_atoll(s, &tmp))
		return (false);
	if (tmp < INT_MIN || tmp > INT_MAX)
		return (false);
	*result = (int)tmp;
	return (true);
}
