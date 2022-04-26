/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:26:11 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/26 16:00:47 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	gere ctrl c (a finir)
*/
void	handler(int sig)
{
	if (sig == SIGINT)	// ctrl c recu
	{
		write(2, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		// g_status = 130;	//TODO gerer la globale
	}
}

void	handler_child(int sig)
{
	if (sig == SIGINT)
	{
		write(2, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 20);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	set_sig_dft(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	set_sig_hd_child(void)
{
	signal(SIGINT, handler_child);
	signal(SIGQUIT, handler_child);
}
