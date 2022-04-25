/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 03:39:29 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/17 20:08:14 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	pop un element de l_env
*/
int	pop_elem_env(t_data *data, t_elem_env *elem)
{
	t_elem_env	*tmp;
	t_elem_env	*tmp2;

	if (!data || !elem)
		return (-1);
	tmp = data->l_env;
	if (elem == data->l_env)
		data->l_env = data->l_env->next;
	else
	{
		while (tmp && tmp->next != elem)
			tmp = tmp->next;
		if (tmp->next != elem)
			return (-1);
		tmp2 = tmp;
		tmp = tmp->next;
		tmp2->next = tmp->next;
	}
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	tmp = NULL;
	return (0);
}

/*
	cree un nouvel elem d'environnement
*/
t_elem_env	*new_elem_env(char *str)
{
	t_elem_env	*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_elem_env));	//!a proteger
	while (str && str[i] && str[i] != '=')
		i++;
	new->name = ft_strndup(str, i);
	new->value = ft_strdup(str + i + 1);
	new->next = NULL;
	return (new);
}

/*
	ajoute un nouvel elem d'environnement a la fin de la liste
*/
void	push_back_elem_env(t_data *data, char *str)
{
	t_elem_env	*new;
	t_elem_env	*tmp;

	new = new_elem_env(str); //?proteger
	if (!data->l_env)
		data->l_env = new;
	else
	{
		tmp = data->l_env;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

/*
	cree la liste d'environnement
*/
void	ft_create_list_env(t_data *data)
{
	char		*tmp;
	char		*tmp2;
	extern char	**environ;

	tmp = NULL;
	tmp2 = NULL;
	while (environ && *environ)
		push_back_elem_env(data, *environ++);
	// display_env(data->l_env);
}

/*
	affiche la liste d'environnement (!c'est pas protege)
*/
void	display_env(t_elem_env *list)
{
	t_elem_env	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

/*
	detruit et free la liste d'environnement
*/
void	destroy_env(t_data *data)
{
	t_elem_env	*tmp;
	t_elem_env	*tmp2;

	while (data->l_env)
	{
		tmp = data->l_env;
		while (tmp && tmp->next != NULL)
		{
			tmp2 = tmp;
			tmp = tmp->next;
		}
		tmp2->next = NULL;
		if (tmp == data->l_env)
			data->l_env = NULL;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
}

//! CES FCTS SONT A REVOIR
int	len_env(t_elem_env *env)
{
	t_elem_env	*tmp;
	int			len;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	*get_str_env(t_elem_env *env)
{
	int		len;
	char	*output;
	char	*ptr;
	int		i;

	len = 2;
	i = 0;
	len += ft_strlen(env->name);
	len += ft_strlen(env->value);
	output = malloc(sizeof(char) * len);
	if (!output)
		return (NULL);
	ptr = output;
	while (env->name && env->name[i])
		*ptr++ = env->name[i++];
	*ptr++ = '=';
	i = 0;
	while (env->value && env->value[i])
		*ptr++ = env->value[i++];
	*ptr = 0;
	return (output);
}

static void	*free_arr_env(char **arr, int i)
{
	while (i > 0)
	{
		i--;
		free(arr[i]);
	}
	free(arr);
	return (NULL);
}

char	**l_env_to_array(t_elem_env *env)
{
	char		**arr;
	t_elem_env	*tmp;
	int			len;
	int			i;

	i = 0;
	len = len_env(env);
	arr = malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (0);
	tmp = env;
	while (i < len)
	{
		arr[i] = get_str_env(tmp);
		if (!arr[i])
			return (free_arr_env(arr, i));
		i++;
		tmp = tmp->next;
	}
	arr[i] = 0;
	return (arr);
}
