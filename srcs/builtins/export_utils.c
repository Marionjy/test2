#include "../../includes/minishell.h"

char	*ft_strdup_egal(char *export)
{
	int		i;
	char	*str;

	i = 0;
	while (export[i] != '=')
		i++;
	str = malloc(sizeof(char) * i + 1);
	i = 0;
	while (export[i] != '=')
	{
		str[i] = export[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strdup_egal2_bis(char *export)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (export[i] != '=')
		i++;
	i++;
	while (export[i] != '\0')
	{
		i++;
		y++;
	}
	return (y);
}

char	*ft_strdup_egal2(char *export)
{
	int		i;
	int		y;
	char	*str;

	y = ft_strdup_egal2_bis(export);
	str = malloc(sizeof(char) * y + 1);
	i = 0;
	y = 0;
	while (export[i] != '=')
		i++;
	i++;
	while (export[i] != '\0')
	{
		str[y] = export[i];
		i++;
		y++;
	}
	str[y] = '\0';
	return (str);
}
