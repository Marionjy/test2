/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redarnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:44:58 by redarnet          #+#    #+#             */
/*   Updated: 2022/03/26 17:31:33 by redarnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export_is_in(char *export, t_elem_env *l_env)
{
	t_elem_env	*tmp;
	char		*str;
	char		*str2;

	str = ft_strdup_egal(export);
	str2 = ft_strdup_egal2(export);
	tmp = l_env;
	while (tmp != NULL)
	{
		if (tmp->name)
		{
			if (ft_strncmp(tmp->name, str, ft_strlen(str)) == 0)
			{
				tmp->value = str2;
				free(str);
				free(str2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	free(str);
	free(str2);
	return (0);
}

int	ft_export_not_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (i == 0 && ft_isnum(str[i]) == 1)
		{
			printf("minishell: export: %s: not a valid identifier\n", str);
			return (1);
		}
		if (str[i] == '?')
		{
			printf("minishell: export: %s: not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_export_elem(char *str, t_data *data)
{
	int		i;
	char	*export;

	i = 0;
	export = NULL;
	if (ft_export_not_valid(str) == 1)
		return (1);
	export = ft_strdup(str);
	while (export[i] != '\0')
	{
		if (export[i] == '=')
		{
			if (ft_export_is_in(export, data->l_env) == 1)
				;
			else
				push_back_elem_env(data, export);
			free(export);
			return (0);
		}
		i++;
	}
	free(export);
	return (0);
}

int	ft_export(t_data *data, char **str, int i)
{
	while (str[i] != 0)
		i++;
	if (i == 1)
	{
		tri_alpha(data->l_env);
		return (0);
	}
	i = 0;
	while (str[i] != 0)
	{
		if (ft_strncmp(str[i], "export", 6) == 0)
		{
			i++;
			if (str[i] == 0)
				return (0);
			if (ft_strncmp(str[i], "export", 6) != 0)
				ft_export_elem(str[i], data);
			else
				i--;
		}
		else
			ft_export_elem(str[i], data);
		i++;
	}
	return (0);
}
