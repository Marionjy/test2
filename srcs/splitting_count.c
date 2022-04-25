/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redarnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:34:15 by redarnet          #+#    #+#             */
/*   Updated: 2022/03/18 19:34:19 by redarnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_deli(char *str)
{
	int	i;
	int	nb_elem;

	i = 0;
	nb_elem = 0;
	while (str[i] != '\0')
	{
		if (ft_is_deli(str[i]) == 1)
		{
			if (str[i] == '>')
			{
				if (str[i + 1] == '>')
					i++;
			}
			if (str[i] == '<')
			{
				if (str[i + 1] == '<')
					i++;
			}
			nb_elem++;
		}
		i++;
	}
	return (nb_elem);
}

int	ft_error_quote(char c)
{
	if (c == '\0')
	{
		printf("ERROR, unclosed sg quote\n");
		return (-1);
	}
	return (0);
}

int	suppr_deli_quote(char *str, int *nb_elem, int i, char c)
{
	i++;
	while (str[i] != c && str[i] != '\0')
	{
		if (ft_is_deli(str[i]) == 1)
		{
			if (str[i] == '>')
			{
				if (str[i + 1] == '>')
					i++;
			}
			if (str[i] == '<')
			{
				if (str[i + 1] == '<')
					i++;
			}
			*nb_elem = *nb_elem - 1;
		}
		i++;
	}
	if (ft_error_quote(str[i]) == -1)
		return (-1);
	return (i);
}

int	count_nb_elem_bis(char *str, int *i, int nb_elem)
{
	if (str[*i] == ' ')
	{
		while (str[*i] == ' ')
			*i = *i + 1;
		if (ft_is_deli(str[*i]) != 1)
			nb_elem++;
		*i = *i - 1;
	}
	else if (ft_is_deli(str[*i]) == 1)
	{
		if (ft_is_deli(str[*i + 1]) != 1 && str[*i + 1] != ' '
			&& str[*i + 1] != '\0')
			nb_elem++;
	}
	else if (str[*i] == '\'')
		*i = suppr_deli_quote(str, &nb_elem, *i, '\'');
	else if (str[*i] == '"')
		*i = suppr_deli_quote(str, &nb_elem, *i, '"');
	if (*i == -1)
		return (-1);
	return (nb_elem);
}

int	count_nb_elem(char *str)
{
	int	nb_elem;
	int	i;

	i = 0;
	nb_elem = count_deli(str);
	while (str[i] == ' ')
		i++;
	if (ft_is_deli(str[i]) != 1)
		nb_elem++;
	while (str[i] != '\0')
	{
		nb_elem = count_nb_elem_bis(str, &i, nb_elem);
		if (nb_elem == -1)
			return (-1);
		i++;
	}
	if (str[i - 1] == ' ')
		nb_elem--;
	return (nb_elem);
}
