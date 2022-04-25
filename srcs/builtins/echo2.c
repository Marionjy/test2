/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redarnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:44:42 by redarnet          #+#    #+#             */
/*   Updated: 2022/03/26 17:29:15 by redarnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_option_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (ft_strlen(str) < 2)
		return (0);
	if (str[i] == '-')
		i++;
	if (str[i] == 'n')
		i++;
	if (i != 2)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	malloc_result_bis(char *str, int *i, int taille)
{
	if (str[*i] == '"')
	{
		while (str[*i] != '"')
		{
			taille++;
			*i = *i + 1;
		}
		taille = taille - 1;
	}
	else if (str[*i] == '\'')
	{
		while (str[*i] != '\'')
		{
			taille++;
			*i = *i + 1;
		}
		taille = taille - 1;
	}
	return (taille);
}

int	malloc_result(char *str)
{
	int	taille;
	int	i;

	taille = 0;
	i = 0;
	while (str[i] != '\0')
	{
		taille = malloc_result_bis(str, &i, taille);
		i++;
		taille++;
	}
	return (taille);
}

char	*fill_result_bis(char *result, char *str, int *i, int *y)
{
	if (str[*i] == '"')
	{
		*i = *i + 1;
		while (str[*i] != '"')
		{
			result[*y] = str[*i];
			*y = *y + 1;
			*i = *i + 1;
		}
		*i = *i + 1;
	}
	else if (str[*i] == '\'')
	{
		*i = *i + 1;
		while (str[*i] != '\'')
		{
			result[*y] = str[*i];
			*y = *y + 1;
			*i = *i + 1;
		}
		*i = *i + 1;
	}
	return (result);
}
