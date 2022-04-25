/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:44:25 by redarnet          #+#    #+#             */
/*   Updated: 2022/04/19 18:20:07 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_pwd(void)
{
	char	cwd[2000];
	char	*result;

	result = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		result = ft_strjoin_char(cwd, '\n');
	else
		perror("getcwd() error");
	return (result);
}

int	ft_strlen_arr(char **str)
{
	int i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

int		ft_command(t_data *data, char **str)
{
	char	*result;
	int		i;
	int		len_str;

	result = NULL;
	i = 0;
	//affiche_arr(str);
	len_str = ft_strlen_arr(str);
	if (ft_strncmp(str[0], "exit", 4) == 0 && ft_strlen(str[0]) == 4)
	{
		i++;
		if (len_str == 1)
		{
			if (data->pwd_value)
				free(data->pwd_value);
			if (data->pwd_name)
				free(data->pwd_name);
			exit(1);
		}
		if (ft_isnum_string(str[i]) == 1 && len_str > 2)
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
		if (str[i])
		{
			while (str[i] != 0  &&(ft_isalpha_string(str[i]) == 1))
				i++;
			if (str[i] == 0)
				i--;
			if (str[i])
				i = ft_builtin_exit(str[i]);
		}
		if (data->pwd_value)
			free(data->pwd_value);
		if (data->l_env->name)
			free(data->l_env->name);
		if (data->pwd_name)
			free(data->pwd_name);
		if (data->l_env->value)
			free(data->l_env->value);
		exit(i);
	}
	else if (ft_strncmp(str[0], "pwd", 3) == 0 && ft_strlen(str[0]) == 3)
		result = ft_pwd();
	else if (ft_strncmp(str[0], "env", 3) == 0 && ft_strlen(str[0]) == 3)
		display_env(data->l_env);
	else if (ft_strncmp(str[0], "unset", 5) == 0 && ft_strlen(str[0]) == 5)
	{
		i = 1;
		while (str[i] != 0)
		{
			if (ft_unset_not_valid(str[i]) == 1)
			{
				// free_arr(str);
				return (1);
			}
			else
				data->l_env = ft_unset(data, str[i]);
			i++;
		}
	}
	else if (ft_strncmp(str[0], "echo", 4) == 0 && ft_strlen(str[0]) == 4)
		result = ft_echo(str, i);
	else if (ft_strncmp(str[0], "cd", 2) == 0 && ft_strlen(str[0]) == 2)
		result = ft_cd(str, data);
	else if (ft_strncmp(str[0], "export", 6) == 0 && ft_strlen(str[0]) == 6)
		ft_export(data, str, i);
	else
		return (0);
	if (result)
		printf("%s", result);
	free(result);
	i = 0;
	// free_arr(str);
	return (1);
}
