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

char	*fill_result(char *str, int taille)
{
	int		i;
	int		y;
	char	*result;

	y = 0;
	i = 0;
	result = malloc(sizeof(char *) * taille + 1);
	if (result == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '"' || str[i] == '\'')
			result = fill_result_bis(result, str, &i, &y);
		else
		{
			result[y] = str[i];
			y++;
			i++;
		}
	}
	result[y] = '\0';
	return (result);
}

char	*ft_echo_result(char **str, int *i, char *result)
{
	int		taille;
	char	*tmp2;
	char	*tmp;

	taille = malloc_result(str[*i]);
	tmp = fill_result(str[*i], taille);
	if (tmp == NULL)
		return (NULL);
	tmp2 = result;
	result = ft_strjoin(tmp2, tmp);
	if (result == NULL)
	{
		free(tmp2);
		free(tmp);
		return (NULL);
	}
	free(tmp2);
	free(tmp);
	return (result);
}

char	*ft_echo_bis(char *result, char **str, int *i)
{
	char	*tmp;

	result = ft_echo_result(str, i, result);
	if (result == NULL)
		return (result);
	*i = *i + 1;
	if (str[*i] != 0)
	{
		tmp = result;
		result = ft_strjoin_char(tmp, ' ');
		if (result == NULL)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	return (result);
}

char	*ft_echo_backslash(char *result, int n)
{
	char	*tmp;

	if (n != 1)
	{
		tmp = result;
		result = ft_strjoin_char(tmp, '\n');
		if (result == NULL)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	return (result);
}

char	*ft_echo(char **str, int i)
{
	char	*result;
	int		n;

	i = 1;
	n = 0;
	result = NULL;
	while (str[i] != 0)
	{
		if (ft_option_n(str[i]) == 1 && i == 1)
		{
			while (ft_option_n(str[i]) == 1)
				i = i + 1;
			n = 1;
		}
		else
		{
			result = ft_echo_bis(result, str, &i);
			if (result == NULL)
				return (NULL);
		}
	}
	result = ft_echo_backslash(result, n);
	return (result);
}
