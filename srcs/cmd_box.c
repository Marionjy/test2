/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_box.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:34:20 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/07 17:24:43 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	fonctions de gestion des cmd_box
*/

void	disp_l_cmd(t_cmd_box *cmd)
{
	t_cmd_box	*tmp;

	tmp = cmd;
	while (tmp)
	{
		dprintf(2, "an elem : pt = %p, len = %d, fdin = %d, fdout = %d\n",
			tmp, tmp->len, tmp->fd_in, tmp->fd_out);
		dprintf(2, "it contains a list :\n");
		ndisplay_list_w_op(tmp->args, tmp->len);
		dprintf(2, "tis all\n\n");
		tmp = tmp->next;
	}
}

/*
	cree un nouvel elem cmd
*/
t_cmd_box	*new_cmd(t_token *list, int len)
{
	t_cmd_box	*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_cmd_box));
	new->fd_in = -1;
	new->fd_out = -1;
	new->next = NULL;
	new->args = list;
	new->len = len;
	return (new);
}

int	push_back_cmd(t_data *stf, t_token *list, int len)
{
	t_cmd_box	*new;
	t_cmd_box	*tmp;

	if (!stf || !list || len < 1)
		return (-1);
	new = new_cmd(list, len);
	if (!new)
		return (-1);
	tmp = *(stf->l_cmd);
	if (tmp == NULL)
	{
		tmp = new;
		*(stf->l_cmd) = tmp;
	}
	else
	{
		tmp = get_last_cmd(*(stf->l_cmd));
		tmp->next = new;
	}
	return (0);
}

t_cmd_box	*get_last_cmd(t_cmd_box *cmd)
{
	t_cmd_box	*tmp;

	if (cmd == NULL)
		return (NULL);
	tmp = cmd;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	destroy_lcmd(t_cmd_box *cmd_list)
{
	t_cmd_box	*tmp;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free(tmp);
	}
}
