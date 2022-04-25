/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redarnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:34:38 by redarnet          #+#    #+#             */
/*   Updated: 2022/03/18 19:34:39 by redarnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	fill_tab_deli(char *str, int *y, int i, char **arr)
{
	while (ft_is_deli(str[*y]) == 1)
	{
		if ((str[*y] == '>' && str[*y + 1] == '>') 
		|| (str[*y] == '<' && str[*y + 1] == '<'))
		{
			arr[i][0] = str[*y];
			arr[i][1] = str[*y];
			arr[i][2] = '\0';
			*y = *y + 1;
			*y = *y + 1;
			i++;
		}
		else
		{
			arr[i][0] = str[*y];
			arr[i][1] = '\0';
			*y = *y + 1;
			i++;
		}
		while (str[*y] == ' ')
			*y = *y + 1;
	}
	return (i);
}

char	**fill_quote_tab(char *str, t_splitstf *stf, char **arr, char c)
{
	arr[stf->i][stf->x] = str[stf->k];
	stf->k = stf->k + 1;
	stf->x = stf->x + 1;
	while (str[stf->k] != c)
	{
		arr[stf->i][stf->x] = str[stf->k];
		stf->k = stf->k + 1;
		stf->x = stf->x + 1;
	}
	arr[stf->i][stf->x] = str[stf->k];
	return (arr);
}

char	**fill_tab_bis(char *str, t_splitstf *stf, char **arr)
{
	if (str[stf->k] == '"')
		arr = fill_quote_tab(str, stf, arr, '"');
	else if (str[stf->k] == '\'')
		arr = fill_quote_tab(str, stf, arr, '\'');
	else
		arr[stf->i][stf->x] = str[stf->k];
	stf->k++;
	stf->x++;
	return (arr);
}

char	**fill_tab(char **arr, int nb_elem, char *str)
{
	t_splitstf	stf;

	stf.i = 0;
	stf.k = 0;
	while (str[stf.k] == ' ')
		stf.k++;
	if (nb_elem >= 1)
		stf.i = fill_tab_deli(str, &stf.k, stf.i, arr);
	while (stf.i != nb_elem)
	{
		stf.x = 0;
		while (ft_is_deli(str[stf.k]) != 1
			&& str[stf.k] != '\0' && str[stf.k] != ' ')
			fill_tab_bis(str, &stf, arr);
		while (str[stf.k] == ' ')
			stf.k++;
		arr[stf.i][stf.x] = '\0';
		stf.i++;
		stf.i = fill_tab_deli(str, &stf.k, stf.i, arr);
	}
	arr[stf.i] = 0;
	return (arr);
}

char	**splitting(char *str)
{
	char	**arr;
	int		nb_elem;

	arr = NULL;
	if ((nb_elem = count_nb_elem(str)) == -1)
		return (NULL);
	arr = malloc(sizeof(char*) * nb_elem + 10);
	if (arr == NULL)
		return (NULL);
	arr = creat_tab(arr, nb_elem, str);
	arr = fill_tab(arr, nb_elem, str);
	return (arr);
}
