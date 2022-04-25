/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 04:06:08 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/14 05:41:16 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strchr(char *str, char c)
{
	while (str && *str && *str != c)
		str++;
	if (str && *str && *str == c)
		return (str);
	else
		return (NULL);
}

int	is_same(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2 || ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] || s2[i])//? a check
		return (0);
	return (1);
}

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_strdup(char *str)
{
	char	*output;
	char	*ptr;

	output = malloc(sizeof(char) * (ft_strlen(str) + 1));
	ptr = output;
	while (str && *str)
		*ptr++ = *str++;
	*ptr = 0;
	return (output);
}

char	*ft_strndup(char const *s, size_t len)
{
	char	*str;
	size_t	i;

	if (len < 0)
		return (NULL);
	i = 0;
	if (ft_strlen((char *)s) < len)
		str = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	else
		str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s[i] && (i < len))
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	freetab(char **arr)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
	return (0);
}

char	**mktab(char **arr, char const *s, char c, int i)
{
	int		j;
	int		x;

	x = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			j = i;
		else
			break ;
		while ((s[i]) && (s[i] != c))
			i++;
		arr[x] = ft_strndup(&s[j], i - j);
		if (!(arr[x]))
		{
			freetab(arr);	//!protection si un malloc rate a refaire
			return (NULL);
		}
		x++;
	}
	arr[x] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	t_splitstf	stf;
	char		**arr;

	stf.i = 0;
	stf.x = 0;
	if (s == NULL)
		return (NULL);
	while ((s[stf.i] == c) && (c != '\0'))
		stf.i++;
	stf.k = stf.i;
	while (s[stf.i])
	{
		while (s[stf.i] == c)
			stf.i++;
		if (s[stf.i])
			stf.x++;
		while (s[stf.i] && s[stf.i] != c)
			stf.i++;
	}
	arr = malloc(sizeof(char *) * (stf.x + 1));
	if (!(arr))
		return (NULL);
	arr = mktab(arr, s, c, stf.k);
	return (arr);
}

char	*ft_strcjoin(char *line, char *buf, char const c)
{
	char	*output;
	size_t	len;
	char	*ptr;

	len = 0;
	if (line)
		len = ft_strlen(line);
	if (buf)
		len += ft_strlen(buf);
	output = malloc(sizeof(char) * (len + 1));
	if (!output)
		return (NULL);
	ptr = output;
	while (line && *line && *line != c)
		*ptr++ = *line++;
	while (buf && *buf && *buf != c)
		*ptr++ = *buf++;
	*ptr = '\0';
	return (output);
}

size_t	ft_strclen(char *str, char c)
{
	size_t	len;

	len = 0;
	while (str && str[len] && str[len] != c)
		len++;
	return (len);
}
