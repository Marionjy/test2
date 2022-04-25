/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:10:31 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/25 20:36:40 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//TODO protection, renvoyer un truc si ca fail
void	redir_out(t_token *file)
{
	int	fd;

	dprintf(2, "open |%s|", file->str);
	fd = open(file->str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_out_app(t_token *file)
{
	int	fd;

	fd = open(file->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_in(t_token *file)
{
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

void	heredoc(t_token *del)
{
	int		fd;
	char	*str;

	(void)del;
	fd = open("/tmp/minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	dprintf(2, "in heredoc, fd = %d\n", fd);
	while (42)
	{
		str = readline("> ");
		if (str && ft_strncmp(str, del->str, ft_strlen(del->str)) != 0)
		{
			write(fd, str, strlen(str));
			write(fd, "\n", 2);
			free(str);
		}
		else
		{
			free(str);
			break ;
		}
	}
	close(fd);
	fd = open("/tmp/minishell_heredoc", O_RDONLY, 0644);
	dup2(fd, STDIN_FILENO);
	close(fd);
}

int	count_redir(t_data *data, t_cmd_box *cmd)
{
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
	t_token	*tmp;
	t_token	*tmp2;
	int		i;

	i = 0;
	tmp = cmd->args;	//proteger de partout
	while (tmp && i < nb_redir)
	{
		//TODO ca manque de close sur les redirs
		if (tmp->type >= REDIR_IN && tmp->type <= REDIR_OUT_APP)
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
		}
		else
			tmp = tmp->next;
	}
	return (0);
}
