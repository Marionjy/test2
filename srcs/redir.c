/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:10:31 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/25 18:07:51 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO protection, renvoyer un truc si ca fail
void	redir_out(t_token *file)
{
	dprintf(2, "	REDIR OUT	\n");
	int	fd;

	dprintf(2, "open |%s|", file->str);
	fd = open(file->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_out_app(t_token *file)
{
	dprintf(2, "	REDIR OU T APP	\n");
	int	fd;

	fd = open(file->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_in(t_token *file)
{
	dprintf(2, "	REDIR IN	\n");
	int	fd;

	fd = open(file->str, O_RDONLY, 0644);
	if (fd == -1)
		printf("minishell: %s: No such file or directory\n", file->str);
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

/*
	open le file, brancher l'input, write dedans jusqu a recevoir le del, close, re open en read brancher la sortie
*/

void	heredoc(t_token *del)
{
	(void)del;
	// int		fd;
	// char	*str;

	// //TODO si quotes dans delimiteur, heredoc sans expansion
	// dup2(fd, STDIN_FILENO);
	// close(fd);
	// str = NULL;
	// str = ft_strdup(NULL);
	// fd = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC);
	// while (ft_strncmp(str, del->str, ft_strlen(del->str)) != 0)
	// {
	// 	str = readline("> ");
	// 	if (!str)
	// 		exit(0);
	// }
	// fd = dup(1);
}

int	count_redir(t_data *data, t_cmd_box *cmd)
{
	dprintf(2, "	COUNT REDIR	\n");
	int			i;
	t_token		*tmp;
	int			ret;

	i = 0;
	ret = 0;
	tmp = cmd->args;
	while (i < cmd->len && tmp)
	{
		if (tmp->type >= REDIR_IN && tmp->type <= REDIR_OUT_APP)
			ret++;
		i++;
		tmp = tmp->next;
	}
	make_redir(data, cmd, ret);
	return (ret);
}

int make_redir(t_data *data, t_cmd_box *cmd, int nb_redir)
{
	dprintf(2, "	MAKE REDIR	\n");
	t_token	*tmp;
	t_token	*tmp2;
	int		i;

	i = 0;
	tmp = cmd->args;	//proteger de partout
	while (tmp && i < nb_redir)
	{
		//TODO gerer les heredocs ailleurs
		//TODO ca manque de close sur les redirs

		if (tmp->type >= REDIR_IN && tmp->type <= REDIR_OUT_APP)	//selon le type de redirection
		{
			if (is_same(tmp->str, "<<"))
				heredoc(tmp->next);
			if (is_same(tmp->str, ">"))
				redir_out(tmp->next);
			if (is_same(tmp->str, ">>"))
				redir_out_app(tmp->next);
			if (is_same(tmp->str, "<"))
				redir_in(tmp->next);
			i++;
			// disp_l_cmd(cmd);
			if (tmp == *(data->list_token))
			{
				*(data->list_token) = tmp->next->next;
			}
			if (cmd->args == tmp)
			{
				cmd->args = tmp->next->next;
			}
			tmp2 = tmp;
			tmp = tmp->next->next;
			pop_token(tmp2->next);
			pop_token(tmp2);
			cmd->len = cmd->len - 2;	//? voir si = 0 apres

			// tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	// disp_l_cmd(cmd);
	//delete_redir(cmd, i); Uncomment pour gerer echo > a > b TEXTE
	// mais double free a fix
	dprintf(2, "	end make redir	\n");
	return (0);
}
