/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:38:15 by redarnet          #+#    #+#             */
/*   Updated: 2022/04/03 16:54:34 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnum(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isnum_string(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isnum(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_isalpha(char c)
{
	if ((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A'))
		return (1);
	return (0);
}

int	ft_isalpha_string(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isalpha(str[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] !=  '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_is_deli(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	else if (c == '\'' || c == '"')
		return (2);
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		if (str1[i] == '\0' && str2[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	if (!s1 && !s2)
		return (NULL);
	if ((str = (char*)malloc(sizeof(char) * ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1)) == NULL)
		return (0);
	if (s1)
		while (s1[x] != '\0')
		{
			str[x] = s1[x];
			x++;
		}
	if (s2)
		while (s2[y] != '\0')
		{
			str[x + y] = s2[y];
			y++;
		}
	str[x + y] = '\0';
	return (str);
}

char	*ft_strjoin_char(const char *s1, char c)
{
	char	*str;
	size_t	x;

	x = 0;
	if (!s1)
		return (NULL);
	if ((str = (char*)malloc(sizeof(char) * ft_strlen((char *)s1)
				+ 2)) == NULL)
		return (0);
	if (s1)
		while (s1[x] != '\0')
		{
			str[x] = s1[x];
			x++;
		}
	str[x] = c;
	str[x + 1] = '\0';
	return (str);
}
