#include "../includes/minishell.h"

int	ft_atoi_exit(char *nptr)
{
	int			i;
	char		signe;
	int			n;
	long long	a;

	i = 0;
	n = 0;
	a = -1;
	signe = 'p';
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\f'
		|| nptr[i] == '\n' || nptr[i] == '\r' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			a = -a;
		i++;
	}
	while (nptr[i] <= '9' && nptr[i] >= '0')
	{
		n = n * 10 + nptr[i] - 48;
		i++;
	}
	return (n * -a);
}

int	ft_builtin_exit(char *str)
{
	long long	nb;
	int			i;

	i = 0;
	nb = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) == 1)
		{
			printf("minishell:exit :numeric argument required");
			return (2);
		}
		i++;
	}
	nb = ft_atoi_exit(str);
	return (nb);
}
