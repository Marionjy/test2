/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sublist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:46:38 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/17 14:06:39 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	fonctions de gestion des sublists
*/

int	pop_sublist(t_sublist *sublist)
{
	if (!sublist)
		return (-1);
	if (sublist->prev)
		sublist->prev->next = sublist->next;
	if (sublist->next)
		sublist->next->prev = sublist->prev;
	free(sublist->str);
	sublist->str = NULL;
	free(sublist);
	sublist = NULL;
	return (0);
}

void	destroy_sublist(t_sublist *sublist)
{
	t_sublist	*tmp;

	tmp = sublist;
	while (tmp && tmp->next)
		pop_sublist(get_last_sublist(tmp));
	pop_sublist(tmp);
	sublist = NULL;
}

t_sublist	*new_elem_sublist(char *str, int len, int type)
{
	t_sublist	*new;

	new = malloc(sizeof(t_sublist));
	if (!new)
		return (NULL);
	new->str = ft_strndup(str, len);
	new->type = type;
	new->len = len;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_sublist	*get_last_sublist(t_sublist *sublist)
{
	t_sublist	*tmp;

	if (!sublist)
		return (NULL);
	tmp = sublist;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	push_back_sublist(t_sublist **sublist, char *str, int len, int type)
{
	t_sublist	*new;
	t_sublist	*tmp;

	if (len == 0)
		return (1);
	new = new_elem_sublist(str, len, type);
	if (!new)
		return (-1);
	tmp = *sublist;
	if (!tmp)
		*sublist = new;
	else
	{
		tmp = get_last_sublist(*sublist);
		new->prev = tmp;
		tmp->next = new;
	}
	return (0);
}

int	create_sublist(t_data *data)
{
	// dprintf(2, "create sublist\n");
	t_token		*tmp;
	t_sublist	*sublist;
	char		*ptr;

	tmp = *(data->list_token);
	while (tmp)
	{
		if (tmp->type == ARG || tmp->type == DB_QUOTE || tmp->type == SG_QUOTE)
		{
			sublist = sublist_quote(tmp);
			expand_sublist(tmp, data, sublist);
			ptr = tmp->str;
			tmp->str = join_sublist(sublist);
			destroy_sublist(sublist);
			free(ptr);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	*join_sublist(t_sublist *sublist)
{
	t_sublist	*tmp;
	char		*output;
	char		*ptr;

	if (!sublist)
		return (NULL);
	output = ft_strdup(sublist->str);
	tmp = sublist->next;
	while (tmp)
	{
		ptr = output;
		output = ft_strjoin(output, tmp->str);
		tmp = tmp->next;
		free(ptr);
	}
	return (output);
}

void	display_sublist(t_sublist *sublist)
{
	t_sublist	*tmp;

	tmp = sublist;
	while (tmp)
	{
		dprintf(2, "|%s|, type = |%d|, len = |%d|\n", tmp->str, tmp->type, tmp->len);
		tmp = tmp->next;
	}
}
