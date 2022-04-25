/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:44:35 by redarnet          #+#    #+#             */
/*   Updated: 2022/04/17 21:12:23 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_oldpwd_bis(t_elem_env *li, t_data *data, char *value)
{
	char	*tmp;
	// char	*tmp2;

	tmp = value;
	if (tmp != NULL)
	{
		if (data->pwd != 1)
			tmp = data->pwd_value;
		else
			data->pwd = 0;
	}
	while (li)
	{
		if (li->name)
		{
			if (ft_strncmp(li->name, "OLDPWD", 6) == 0)
			{
				free(li->value);
				li->value = ft_strdup(tmp);
				if (li->value == NULL)
				{
					free(tmp);
					return (-1);
				}
			}
		}
		li = li->next;
	}
	free(tmp);
	return (0);
}


int	change_oldpwd(t_elem_env *li, t_data *data)
{
	t_elem_env	*li2;

	li2 = li;
	while (li2)
	{
		if (li2->name)
		{
			if (ft_strncmp(li2->name, "PWD", 3) == 0)
				return (change_oldpwd_bis(li, data, li2->value));
		}
		li2 = li2->next;
	}
	if (change_oldpwd_bis(li, data, NULL) == -1)
		return (-1);
	return (0);
}

void	base_bis_pwd(t_elem_env *li, char *tmp2)
{
	if (ft_strncmp(li->name, "PWD", 3) == 0)
	{
		tmp2 = ft_pwd();
		free(li->value);
		li->value = tmp2;
	}
}

int	base_bis(int i, char *tmp, t_elem_env *li, t_data *data)
{
	char	*tmp2;

	tmp2 = NULL;
	if (i == -1)
	{
		printf("minishell : cd: << HOME >> non défini\n");
		return (-1);
	}
	if (chdir(tmp) != 0)
	{
		printf("minishell : cd: %s: Aucun fichier ou dossier de ce type\n", tmp);
		return (-1);
	}
	if (change_oldpwd(li, data) == -1)
		return (-1);
	while (li)
	{
		if (li->name)
			base_bis_pwd(li, tmp2);
		li = li->next;
	}
	free(tmp2);
	return (0);
}
