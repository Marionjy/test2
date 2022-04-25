/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redarnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:44:35 by redarnet          #+#    #+#             */
/*   Updated: 2022/03/26 15:44:37 by redarnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*base_home(t_elem_env *li2, char *tmp, int *i)
{
	while (li2)
	{
		if (li2->name)
		{
			if (ft_strncmp(li2->name, "HOME", 4) == 0)
			{
				*i = ft_strlen(li2->value);
				tmp = ft_strdup(li2->value);
				if (tmp == NULL)
					return (NULL);
			}
		}
		li2 = li2->next;
	}
	return (tmp);
}

int	base(t_elem_env *li, t_data *data)
{
	t_elem_env	*li2;
	int			i;
	char		*tmp;

	tmp = NULL;
	li2 = li;
	i = -1;
	tmp = base_home(li2, tmp, &i);
	if (base_bis(i, tmp, li, data) == -1)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (1);
}

char	*ft_cd_arg(char **str, char *result, t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(str[1]);
	if (tmp == NULL)
		return (NULL);
	if (chdir(tmp) == -1)
	{
		result = ft_strdup("minishell: cd: error \n");
		free(tmp);
		return (result);
	}
	if (change_oldpwd(data->l_env, data) == -1)
	{
		free(tmp);
		return (NULL);
	}
	if (modif_env(tmp, data->l_env, data) == -1)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (result);
}

char	*ft_cd_less(char **str, t_data *data, char *result)
{
	char	*tmp;

	tmp = NULL;
	if (str[1][1])
		printf("minishell: cd : %s: No such file or directory\n", str[1]);
	tmp = find_last(data->l_env);
	if (tmp == NULL)
		return (NULL);
	change_oldpwd(data->l_env, data);
	result = change_pwd(data->l_env, tmp, data);
	free(tmp);
	return (result);
}

char	*ft_cd(char **str, t_data *data)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	while (str[i] != 0)
		i++;
	if (i > 2)
		printf("minishell: cd: too many arguments\n");
	else if (i == 1)
	{
		if (base(data->l_env, data) == -1)
			return (NULL);
	}
	else if (str[1][0] == '-')
		result = ft_cd_less(str, data, result);
	else if (str[1][0] == '.' && str[1][1] != '.')
	{
		if (str[1][1])
			printf("minishell: cd : %s: No such file or directory\n", str[1]);
		return (NULL);
	}
	else
		result = ft_cd_arg(str, result, data);
	return (result);
}
