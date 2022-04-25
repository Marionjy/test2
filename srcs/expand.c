/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 04:37:56 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/22 18:55:39 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_count(char *str, char c)
{
	char	*ptr;
	int		ret;

	if (!str)
		return (-1);
	ptr = str;
	ret = 0;
	while (ptr && *ptr)
	{
		if (*ptr == c)
			ret++;
		ptr++;
	}
	return (ret);
}

int	expand_a_var(t_data *data, t_sublist *sublist)
{
	// dprintf(2, "	expand a var	\n");
	char		*name;
	char		*ptr;
	int			len;
	t_elem_env	*tmp_env;
	char		*ptr2;
	char		*ptr3;
	int			i;

	len = 0;
	//on cherche le $
	ptr = ft_strchr(sublist->str, '$') + 1;
	while (ptr && ptr[len] && (isalnum(ptr[len]) || ptr[len] == '_'))
		len++;
	if (len < 1)
		return (1);
	name = ft_strndup(ft_strchr(sublist->str, '$') + 1, len);
	// on cherche la var d'env correspondant a name
	tmp_env = ft_get_var(data, name);
	free(name);

	if (tmp_env)
		len = get_new_len(sublist) + ft_strlen(tmp_env->value);
	else
		len = get_new_len(sublist);
	ptr = sublist->str;
	ptr3 = ptr;

	sublist->str = malloc(sizeof(char) * (len + 1));	//!proteger
	ptr2 = sublist->str;
	i = 0;

	while (ptr && *ptr && *ptr != '$')
		*ptr2++ = *ptr++;
	ptr++;	//!a proteger
	while (ptr && *ptr && isalnum(*ptr))
		ptr++;

	while (tmp_env && tmp_env->value[i])
	{
		*ptr2++ = tmp_env->value[i++];
	}
	while (ptr && *ptr)
		*ptr2++ = *ptr++;
	*ptr2 = '\0';
	free(ptr3);
	// dprintf(2, "end expand a var, sublist str = |%s| \n", sublist->str);
	return (0);
}

size_t	get_new_len(t_sublist *sublist)
{
	// dprintf(2, "	get new len	\n");
	size_t	len;
	char	*ptr;

	len = 0;
	ptr = sublist->str;
	while (sublist && ptr && *ptr && *ptr != '$')
	{
		ptr++;
		len++;
	}
	//ici on a la len jusqu'a un $ potentiel
	if (ptr && *ptr && *ptr == '$')
	{
		ptr++;
		while (ptr && *ptr && isalnum(*ptr))
			ptr++;
	}
	if (ptr && *ptr)
	{
		len = len + 1;
		while (ptr && *ptr)
		{
			ptr++;
			len++;
		}
	}
	return (len);
}

	// rm les "",  expand les $, rejoin, * -1 les espaces
int	expand_db_quote(t_data *data, t_sublist *sublist)
{
	dprintf(2, "	expand db quote	str = %s\n", sublist->str);
	char	*str;
	int		nb_dollar;

	str = sublist->str;
	sublist->str = ft_strndup(sublist->str + 1, ft_strlen(sublist->str) - 2);
	free(str);
	nb_dollar = ft_count(sublist->str, '$');
	// while (ft_strchr(sublist->str, '$'))
	while (nb_dollar > 0)
	{
		expand_a_var(data, sublist);
		nb_dollar--;	//!
	}
	// dprintf(2, "end exp db q str = |%s|", sublist->str);
	return (0);
}

	// expand les $ et enlever les espaces donc resplit
int	expand_arg(t_data *data, t_sublist *sublist)
{
	int	nb_dollar;
	
	// dprintf(2, "	expand arg	\n");
	nb_dollar = ft_count(sublist->str, '$');
	// while (ft_strchr(sublist->str, '$'))
	while (nb_dollar > 0)
	{
		expand_a_var(data, sublist);
		nb_dollar--;
	}
	return (0);
}

	// juste retirer les quotes
int	expand_sg_quote(t_data *data, t_sublist *sublist)
{
	// dprintf(2, "	expand sg quote	\n");
	char	*str;

	(void)data;
	str = sublist->str;
	sublist->str = ft_strndup(sublist->str + 1, ft_strlen(sublist->str) - 2);
	free(str);
	return (0);
}


int	expand_sublist(t_token *token, t_data *data, t_sublist *sublist)
{
	// dprintf(2, "	expand sublist	\n");
	t_sublist	*tmp;

	(void)token;
	tmp = sublist;
	while (tmp)
	{
		if (tmp->type == DB_QUOTE)
			expand_db_quote(data, tmp);
		else if (tmp->type == SG_QUOTE)
			expand_sg_quote(data, tmp);
		else if (tmp->type == ARG)
			expand_arg(data, tmp);
		tmp = tmp->next;
	}
	return (0);
}

/*
	split un token en sublist, en fonction des quotes
*/
t_sublist	*sublist_quote(t_token *token)
{
	// dprintf(2, "	sublist quote	\n");
	t_sublist	*sublist;
	int			i;
	char		*ptr;

	sublist = NULL;
	i = 0;
	ptr = token->str;
	while (ptr && ptr[i])
	{
		while (ptr && ptr[i] && ptr[i] != '"' && ptr[i] != '\'')
			i++;
		push_back_sublist(&sublist, ptr, i, ARG);
		ptr = ptr + i;
		i = 0;
		if (ptr[i] == '"')
		{
			i++;
			while (ptr && ptr[i] && ptr[i] != '"')
				i++;
			push_back_sublist(&sublist, ptr, i + 1, DB_QUOTE);
			ptr = ptr + i + 1;
			i = 0;
		}
		else if (ptr[i] == '\'')
		{
			i++;
			while (ptr && ptr[i] && ptr[i] != '\'')
				i++;
			push_back_sublist(&sublist, ptr, i + 1, SG_QUOTE);
			ptr = ptr + i + 1;
			i = 0;
		}
	}
	return (sublist);
}
