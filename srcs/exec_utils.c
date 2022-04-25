/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:39:11 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/07 17:26:50 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**arg_maker(t_token *token, int nb_elem)
{
	t_token	*tmp;
	char	**ret;
	int		i;
	int		len;
	int		j;

	if (!token || nb_elem < 1)
		return (NULL);
	tmp = token;
	ret = NULL;
	i = 0;
	len = 0;
	while (tmp && i < nb_elem)
	{
		if (tmp->type > 0 && tmp->type < 4)
			len++;
		tmp = tmp->next;
		i++;
	}
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	j = 0;		//ON PEUT LE FAIRE EN REMONTANT DaNS L AUTRE SENS
	tmp = token;
	while (tmp && i > 0)
	{
		if (tmp->type > 0 && tmp->type < 4)
		{
			ret[j] = ft_strdup(tmp->str);
			j++;
		}
		i--;
		tmp = tmp->next;
	}
	ret[j] = NULL;
	return (ret);
}


t_elem_env	*ft_get_var(t_data *data, char *name)
{
	t_elem_env	*ptr;
	int			found;

	found = 0;
	ptr = data->l_env;
	while (name && ptr && ptr->name)
	{
		if (is_same(name, ptr->name))
		{
			found = 1;
			break ;
		}
		ptr = ptr->next;
	}
	if (found)
		return (ptr);
	return (NULL);
}

int	count_pipes(t_token *list)
{
	t_token	*tmp;
	int			ret;

	ret = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			ret++;
		tmp = tmp->next;
	}
	return (ret);
}
