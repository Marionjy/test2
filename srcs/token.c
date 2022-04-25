/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 03:20:50 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/13 05:35:32 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	assigne le type pour les fichiers (ce qui suit les redir) //! du coup attention aux erreurs de syntaxe, a revoir
*/
int	assign_file(t_token *list)
{
	t_token	*tmp;

	tmp = list->next;
	while (tmp)
	{
		if (tmp->type == ARG && tmp->prev && tmp->prev->type == REDIR_IN)
			tmp->type = IN_FILE;
		else if (tmp->type == ARG && tmp->prev && tmp->prev->type == REDIR_OUT)
			tmp->type = OUT_FILE;
		else if (tmp->type == ARG && tmp->prev
			&& tmp->prev->type == REDIR_OUT_APP)
			tmp->type = OUT_FILE_APP;
		else if (tmp->type == ARG && tmp->prev && tmp->prev->type == HEREDOC)
			tmp->type = LIMITOR;
		tmp = tmp->next;
	}
	return (0);
}

/*
	assigne le type a un maillon de la liste de commande pour les redir
*/
int	ft_assign_type(char *str)
{
	if (!str || !*str)
		return (-1);
	if (str[0] == '"')
		return (DB_QUOTE);
	else if (str[0] == '\'')
		return (SG_QUOTE);
	else if (is_same(">", str))
		return (REDIR_OUT);
	else if (is_same("<", str))
		return (REDIR_IN);
	else if (is_same("<<", str))
		return (HEREDOC);
	else if (is_same(">>", str))
		return (REDIR_OUT_APP);
	else if (str[0] == '|')
		return (PIPE);
	else
		return (ARG);
}

/*
	cree un nouveau token
*/
t_token	*new_token(char *str)
{
	t_token	*new;

	// dprintf(2, "NEW TOKEN\n");
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = ft_strdup(str);	//? a proteger
	new->type = ft_assign_type(new->str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

/*
	enleve un token
*/
int	pop_token(t_token *elem)
{
	// dprintf(2, "POP TOKEN\n");
	if (!elem)
		return (-1);
	if (elem->prev)
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	free(elem->str);
	elem->str = NULL;
	free(elem);
	elem = NULL;
	return (0);
}

/*
	detruit la liste de token
*/
void	destroy_l_token(t_token *list)
{
	t_token	*tmp;

	// dprintf(2, "DESTROY TOKEN\n");
	tmp = list;
	while (tmp && tmp->next)
	{
		pop_token(get_last_token(tmp));
	}
	pop_token(list);
	list = NULL;
}

/*
	renvoie le dernier token de la liste
*/
t_token	*get_last_token(t_token	*list)
{
	t_token	*tmp;

	// dprintf(2, "GET LAST TOKEN\n");
	if (!list)
		return (NULL);
	tmp = list;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

/*
	affiche la liste de tokens
*/
void	display_list_token(t_token *list)
{
	t_token	*tmp;

	dprintf(2, "\nDISPLAY LIST TOKEN\n");
	tmp = list;
	while (tmp)
	{
		dprintf(2, "|%s|, type : |%i|,\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

void	ndisplay_list_w_op(t_token *list, int len)
{
	t_token	*tmp;

	tmp = list;
	while (tmp && len)
	{
		dprintf(2, "|%s|, type : |%i|\n", tmp->str, tmp->type);
		tmp = tmp->next;
		len--;
	}
}

/*
	ajoute un nouveau token a la fin de la liste
*/
int	push_back_token(t_data *data, char *str)
{
	t_token	*new;
	t_token	*tmp;

	// dprintf(2, "PUSH_BACK TOKEN\n");
	new = new_token(str);
	if (!new)
		return (-1);
	tmp = *(data->list_token);
	if (tmp == NULL)
	{
		*(data->list_token) = new;
	}
	else
	{
		tmp = get_last_token(*(data->list_token));
		new->prev = tmp;
		tmp->next = new;
	}
	return (0);
}

/*
	cree la liste de token	//?void?
*/
void	create_list_token(t_data *data, char **arr_token)
{
	int	i;

	// dprintf(2, "CREATE LIST TOKEN\n");
	i = 0;
	while (arr_token[i])
	{
		push_back_token(data, arr_token[i]);
		i++;
	}
	assign_file(*(data->list_token));
	// display_list_token(*(data->list_token));
}
