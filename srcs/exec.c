/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 04:14:43 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/07 17:27:55 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mk_cmd_box(t_data *stf)
{
	t_token		*tmp;
	t_token		*tmp_start_cmd;
	int			nb_cmd;
	int			len_cmd;

	nb_cmd = 0;
	tmp = *(stf->list_token);
	while (tmp && nb_cmd <= stf->nb_pipes)
	{
		len_cmd = 0;
		tmp_start_cmd = tmp;
		while (tmp && tmp->type != PIPE)
		{
			tmp = tmp->next;
			len_cmd++;
		}
		push_back_cmd(stf, tmp_start_cmd, len_cmd);
		nb_cmd++;
		if (tmp && tmp->type == PIPE)
			if (tmp->next)
				tmp = tmp->next;
	}
	return (0);
}

// void	close_fds(int *pipefd, int fd_in)
// {
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	close(fd_in);
// }

// void	close_fds2(int fd1, int fd2)
// {
// 	close(fd1);
// 	close(fd2);
// }
