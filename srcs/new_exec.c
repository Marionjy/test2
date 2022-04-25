/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 19:50:33 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/24 08:11:20 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_general(t_data *data)
{
	if (data->nb_pipes < 1)
		exec_without_pipes(data);
	else if (data->nb_pipes > 0)
		exec_with_pipes(data);
	return (0);
}

void	exec_without_pipes(t_data *data)
{
	// dprintf(2, "exec without pipes\n");
	t_cmd_box	*tmp;
	pid_t		pid;
	int			fd_in;

	// fd_in = 5425242;
	tmp = *(data->l_cmd);
	fd_in = dup(STDIN_FILENO);
	// dprintf(2, "fd in af dup = %d stdin = %d, stdout = %d\n", fd_in, STDIN_FILENO, STDOUT_FILENO);
	count_redir(data, tmp);
	data->av = arg_maker(tmp->args, tmp->len);
	data->arr_env = l_env_to_array(data->l_env);
	if (ft_command(data, data->av) == 1)
		;

	else
	{
		pid = fork();
		if (pid == 0)
		{
			//ici, on est dans le child

			set_sig_hd_child();
			// // signal(SIGINT, handler);
			// signal(SIGINT, SIG_DFL);
			// signal(SIGQUIT, SIG_DFL);

			// dprintf(2, "in child, before dup2, fdin = %d, stdin = %d\n", fd_in, STDIN_FILENO);
			dup2(fd_in, STDIN_FILENO);
			// dprintf(2, "in child, after dup2, fdin = %d, stdin = %d\n", fd_in, STDIN_FILENO);

			//TODO gerer les redirections
			// count_redir(data, tmp);

			close(fd_in);
			dprintf(2, "after redir, l cmd = /n");
			disp_l_cmd(*(data->l_cmd));
			//TODO a securiser
			launch_exec(data->av, data->arr_env, data);
			freetab(data->av);
			data->av = NULL;
			freetab(data->arr_env);
			data->arr_env = NULL;

			// dprintf(2, "something went wrong, child is alive\n");
			// exit(0);	//! a changer!
			ft_exit(data, 2);

		}
		wait(NULL);
	}

	freetab(data->av);
	data->av = NULL;
	freetab(data->arr_env);
	data->arr_env = NULL;

	close(fd_in);
}

void	exec_with_pipes(t_data *data)
{
	// dprintf(2, "exec with pipes\n");
	int			pipefd[2];
	t_cmd_box	*tmp;
	int			i;
	pid_t		pid;
	int			fd_in;

	i = 0;
	tmp = *(data->l_cmd);
	if (!tmp)	//TODO securiser
		return ;
	fd_in = dup(STDIN_FILENO);
	while (i <= data->nb_pipes && tmp)
	{
		pipe(pipefd); //TODO securiser pipe et fork
		pid = fork();
		if (pid == 0)
		{
			//ici on est dans le child
			
			// set_sig_hd_child();
			// // signal(SIGINT, handler);
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);

			dup2(fd_in, STDIN_FILENO);
			if (i != data->nb_pipes)
				dup2(pipefd[1], STDOUT_FILENO);
			count_redir(data, tmp);

			close(pipefd[0]);
			close(pipefd[1]);
			close(fd_in);

			// dprintf(2, "after redir, l cmd = /n");
			// disp_l_cmd(*(data->l_cmd));
			data->arr_env = l_env_to_array(data->l_env);
			data->av = arg_maker(tmp->args, tmp->len);
			if (ft_command(data, data->av) == 1)
				;
			else
				launch_exec(data->av, data->arr_env, data);

			//* si on arrive ici, il y a un pb, le child est vivant
			// dprintf(2, "something went wrong, child is alive\n");

			// dprintf(2, "cmd not found\n");
			freetab(data->av);
			data->av = NULL;
			freetab(data->arr_env);
			data->arr_env = NULL;
			exit(0);	//! A changer
		}

		close(fd_in);
		fd_in = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		i++;
		tmp = tmp->next;

	}
	close(fd_in);
	i = 0;
	while (i <= data->nb_pipes)	//? on peut decrementer peut etre
	{
		wait(NULL);
		i++;
	}
}

void	launch_exec(char **av, char **env, t_data *data)
{
	t_elem_env	*env_path;
	struct stat	buf;
	char		**paths;
	int			i;
	char		*ptr;

	env_path = ft_get_var(data, "PATH");
	if (av[0][0] == '/')
	{
		stat(av[0], &buf);
		if (!(access(av[0], F_OK) || access(av[0], X_OK) || S_ISDIR(buf.st_mode)))
			execve(av[0], av, env);
	}
	else if (env_path && av[0][0] != '.')
	{
		paths = ft_split(env_path->value, ':');
		i = 0;
		while (paths[i])
		{
			ptr = paths[i];
			paths[i] = ft_strcjoin(paths[i], "/", 0);	//!leaks a gerer ici, et verif le strcjoin
			free(ptr);
			ptr = paths[i];
			paths[i] = ft_strcjoin(paths[i], av[0], 0);
			free(ptr);
			if (!(access(paths[i], F_OK) || access(paths[i], X_OK)))
				execve(paths[i], av, env);
			free(paths[i]);
			i++;
		}
		free(paths);
	}
	else if (av[0][0] == '.')
	{
		stat(av[0], &buf);
		if (!(access(av[0], F_OK) || access(av[0], X_OK) || S_ISDIR(buf.st_mode)))
			execve(av[0], av, env);
	}
	//si on arrive ici : probleme. cmd not found etc
	dprintf(2, "cmd not found\n");	//!A CHANGER
}
