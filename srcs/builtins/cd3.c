#include "../../includes/minishell.h"

int	ft_modif_env_bis(t_elem_env *li, t_data *data, char *str)
{
	char	*tmp2;

	if (ft_strncmp(str, "..", 2) == 0)
	{
		while (li != NULL)
		{
			if (li->name)
			{
				if (ft_strncmp(li->name, "PWD", 3) == 0)
				{
					tmp2 = ft_pwd();
					li->value = tmp2;
					return (1);
				}
			}
			li = li->next;
		}
		tmp2 = ft_pwd();
		data->pwd_value = tmp2;
	}
	return (1);
}

int	modif_env(char *str, t_elem_env *li, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	if (ft_modif_env_bis(li, data, str) == -1)
		return (-1);
	else
	{
		while (li != NULL)
		{
			if (li->name)
			{
				if (ft_strncmp(li->name, "PWD", 3) == 0)
				{
					tmp = ft_pwd();
					if (tmp == NULL)
						return (-1);
					li->value = tmp;
				}
				return (1);
			}
			li = li->next;
		}
	}
	return (1);
}

char	*change_pwd(t_elem_env *li, char *tmp, t_data *data)
{
	char	*result;

	result = ft_strjoin_char(tmp, '\n');
	if (result == NULL)
		return (NULL);
	while (li != NULL)
	{
		if (li->name)
		{
			if (ft_strncmp(li->name, "PWD", 3) == 0)
			{
				tmp = ft_pwd();
				li->value = tmp;
				return (result);
			}
		}
		li = li->next;
	}
	data->pwd_value = ft_strdup(tmp);
	free(tmp);
	return (result);
}

char	*find_last_bis(t_elem_env *li2, char *tmp)
{
	while (li2 != NULL)
	{
		if (li2->name)
		{
			if (ft_strncmp(li2->name, "OLDPWD", 6) == 0)
			{
				tmp = ft_strdup(li2->value);
				return (tmp);
			}
		}
		li2 = li2->next;
	}
	printf("OLDPWD not set\n");
	return (NULL);
}

char	*find_last(t_elem_env *li)
{
	char		*tmp;
	t_elem_env	*li2;

	li2 = li;
	tmp = NULL;
	tmp = find_last_bis(li2, tmp);
	if (tmp == NULL)
		return (NULL);
	chdir(tmp);
	return (tmp);
}
