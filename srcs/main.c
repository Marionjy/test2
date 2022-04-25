/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 21:07:30 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/25 17:50:14 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status = 0;

void	free_arr(char **arr)	//? a revoir?
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/*
	init la structure data
*/
int	ft_init(t_data *data)
{
	data->nb_pipes = 0;
	data->pwd = 0;
	data->pwd_value = NULL;
	data->pwd_name = NULL;
	data->i = 0;
	data->list_token = malloc(sizeof(data->list_token));
	if (!data->list_token)
		return (-1);
	*(data->list_token) = NULL;
	// data->arr = NULL;
	data->l_env = NULL;
	data->l_cmd = malloc(sizeof(data->l_cmd));
	if (!data->l_cmd)
		return (-1);
	*(data->l_cmd) = NULL;
	data->pid = NULL;
	data->arr_env = NULL;
	data->av = NULL;
	ft_create_list_env(data);
	return (0);
}

int	check_type(t_token *token)
{
	int	type;

	if (!token)
		return (-1);
	type = token->type;
	if (type == REDIR_IN || type == REDIR_OUT || type == HEREDOC
		|| type == REDIR_OUT_APP || type == PIPE)
		return (1);
	else
		return (0);
}

int	ft_check_syntax(t_data *data)
{
	t_token	*tmp;

	tmp = *(data->list_token);
	while (tmp)
	{
		if (check_type(tmp))
		{
			if (!tmp->next || check_type(tmp->next))
				return (-1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	main(void)
{
	char	*cmd;
	char	**tmp_tab;
	t_data data;

	ft_init(&data);
	while (1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("\033[1mMinishell-1.0$>\033[0m ");
		if (!cmd)
		{
			dprintf(2, "ERROR, no cmd\n");
			// destroy_env(&data);
			// destroy_l_token(*(data.list_token));
			// destroy_lcmd(*(data.l_cmd));
			// *(data.list_token) = NULL;
			// *(data.l_cmd) = NULL;
			// data.l_env = NULL;
			// free(data.list_token);
			// free(data.l_cmd);
			// rl_clear_history();
			// exit(0);	//TODO faire une fonction d'exit propre
			ft_exit(&data, 1);	//?int aleatoire 
		}
		add_history(cmd);	//TODO clear history a la fin/dans l'exit

		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);

		while (cmd && *cmd)	//! voir comportement si !*cmd
		{
			tmp_tab = splitting(cmd);

			if (!tmp_tab)
				break ;		//! gerer ca correctement, attention au segfault

			create_list_token(&data, tmp_tab);
			freetab(tmp_tab);
			if (ft_check_syntax(&data))
			{
				dprintf(2, "syntax error\n");		//!a changer
				destroy_l_token(*(data.list_token));
				*(data.list_token) = NULL;
				free(cmd);
				cmd = NULL;
				break;
			}
			// dprintf(2, "si on arrive ici, syntaxe ok\n");
			create_sublist(&data);

			// dprintf(2, "list token post sublist: \n");
			// display_list_token(*(data.list_token));

			data.nb_pipes = count_pipes(*(data.list_token));
			mk_cmd_box(&data);
			// disp_l_cmd(*(data.l_cmd));
			exec_general(&data);

			//*voir les frees
			free(cmd);
			cmd = NULL;
			destroy_l_token(*(data.list_token));
			destroy_lcmd(*(data.l_cmd));
			*(data.list_token) = NULL;
			*(data.l_cmd) = NULL;
		}
	}
	return (0);
}
