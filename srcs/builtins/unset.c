/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:45:05 by redarnet          #+#    #+#             */
/*   Updated: 2022/04/03 17:24:25 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset_not_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '?' || str[i] == '=')
		{
			printf("minishell: unset: %s: not a valid identifier\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_cmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (s1)
	{
		while (s1[i] != '\0' && s1[i] != '=')
		{
			if (s2[i] != s1[i])
				return (0);
			i++;
		}
	}
	if (i != ft_strlen(s2))
		return (0);
	return (1);
}

t_elem_env	*ft_unset_bis(t_elem_env *temp, char *comp, t_data *data)
{
	t_elem_env	*before;
	char	*tmp;
	char	*tmp2;

	before = data->l_env;
	tmp = NULL;
	tmp2 = NULL;
	while (temp->next != NULL)
	{
		if (temp->next->name)
		{
			if (ft_cmp(temp->next->name, comp) == 1)
			{
				if (ft_strncmp(comp, "PWD", 3) == 0 && ft_strlen(comp) == 3)
				{
					tmp = temp->next->name;
					tmp2 = temp->next->value;
					data->pwd_name = ft_strdup(tmp);
					data->pwd_value = ft_strdup(tmp2);
					data->pwd = 1;
				}
				before = temp->next;
				temp->next = temp->next->next;
				free(before);
				free(tmp);
				free(tmp2);
				return (data->l_env);
			}
		}
		temp = temp->next;
	}
	free(tmp);
	free(tmp2);
	free(before);
	return (data->l_env);
}

t_elem_env	*ft_unset(t_data *data, char *comp)
{
	t_elem_env	*temp;
	t_elem_env	*before;

	temp = data->l_env;
	if (data->l_env == NULL)
		return (NULL);
	if (data->l_env->next == NULL)
	{
		if (ft_cmp(temp->name, comp) == 1)
		{
			if (ft_strncmp(comp, "PWD", 3) == 0 && ft_strlen(comp) == 3)
			{
				data->pwd_name = ft_strdup(temp->next->name);
				data->pwd_value = ft_strdup(temp->next->value);
				data->pwd = 1;
			}
			before = temp->next;
			free(data->l_env);
			data->l_env = NULL;
		}
		return (data->l_env);
	}
	data->l_env = ft_unset_bis(temp, comp, data);
	return (data->l_env);
}