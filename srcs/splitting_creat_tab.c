/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_creat_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 17:56:48 by mjacquet          #+#    #+#             */
/*   Updated: 2022/03/25 17:56:49 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**creat_tab_deli(char *str, int *y, int *i, char **arr)
{
	while (ft_is_deli(str[*y]) == 1)
	{
		if (str[*y] == '>' && str[*y + 1] == '>')
		{
			arr[*i] = malloc(sizeof(char ) * 2 + 1);
			*y = *y + 1;
			*y = *y + 1;
			*i = *i + 1;
		}
		else if (str[*y] == '<' && str[*y + 1] == '<')
		{
			arr[*i] = malloc(sizeof(char ) * 2 + 1);
			*y = *y + 1;
			*y = *y + 1;
			*i = *i + 1;
		}
		else
		{
			arr[*i] = malloc(sizeof(char ) * 1 + 1);
			*y = *y + 1;
			*i = *i + 1;
		}
		while (str[*y] == ' ')
			*y = *y + 1;
	}
	return (arr);
}

void	pass_quote_tab(char *str, int *y, int *x)
{
	if (str[*y] == '"')
	{
		*y = *y + 1;
		*x = *x + 1;
		while (str[*y] != '"')
		{
			*y = *y + 1;
			*x = *x + 1;
		}
	}
	else if (str[*y] == '\'')
	{
		*y = *y + 1;
		*x = *x + 1;
		while (str[*y] != '\'')
		{
			*y = *y + 1;
			*x = *x + 1;
		}
	}
	*y = *y + 1;
	*x = *x + 1;
}

char	**creat_tab(char **arr, int nb_elem, char *str)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	y = 0;
	while (str[y] == ' ')
		y++;
	arr = creat_tab_deli(str, &y, &i, arr);
	while (i != nb_elem)
	{
		x = 0;
		while (ft_is_deli(str[y]) != 1
			&& str[y] != '\0' && str[y] != ' ')
			pass_quote_tab(str, &y, &x);
		while (str[y] == ' ')
			y++;
		arr[i] = malloc(sizeof(char ) * x + 1);
		i++;
		arr = creat_tab_deli(str, &y, &i, arr);
	}
	return (arr);
}
