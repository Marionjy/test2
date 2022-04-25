#include "../../includes/minishell.h"

int	taille_list(t_elem_env *data)
{
	int	i;

	i = 0;
	while (data != NULL)
	{
		data = data->next;
		i++;
	}
	return (i);
}

char	*ft_toupper_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] <= 'z' && str[i] >= 'a')
			str[i] = str[i] - 32;
		i++;
	}
	return (str);
}

void	affiche_tab_export(char **tab1, char **tab2)
{
	int	i;

	i = 0;
	while (tab1[i] != 0)
	{
		printf("declare -x %s=%s\n", ft_toupper_str(tab1[i]), tab2[i]);
		i++;
	}
}

char	**tri_bull(char **tab1)
{
	int		y;
	int		i;
	char	*tmp;

	i = 0;
	while (tab1[i + 1] != 0)
	{
		y = 0;
		while (tab1[y + 1] != 0)
		{
			if (ft_strcmp(tab1[y], tab1[y + 1]) >= 0)
			{
				tmp = tab1[y];
				tab1[y] = ft_strdup(tab1[y + 1]);
				tab1[y + 1] = ft_strdup(tmp);
			}
			y++;
		}
		i++;
	}
	return (tab1);
}

void	tri_alpha(t_elem_env *data)
{
	char		**tab1;
	char		**tab2;
	int			i;
	t_elem_env	*tmp;

	tmp = data;
	i = taille_list(data);
	tab1 = (char **)malloc(sizeof(char *) * i + 1);
	tab2 = (char **)malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tmp != NULL)
	{
		tab1[i] = ft_strdup(tmp->value);
		tab2[i] = ft_strdup(tmp->name);
		tmp = tmp->next;
		i++;
	}
	tab1[i] = 0;
	tab1 = tri_bull(tab1);
	affiche_tab_export(tab1, tab2);
	free(tab1);
	free(tab2);
}
