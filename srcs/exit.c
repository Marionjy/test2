#include "../includes/minishell.h"

void	ft_exit(t_data *data, int i)
{
	destroy_env(data);
	destroy_l_token(*(data->list_token));
	destroy_lcmd(*(data->l_cmd));
	*(data->list_token) = NULL;
	*(data->l_cmd) = NULL;
	data->l_env = NULL;
	free(data->list_token);
	free(data->l_cmd);
	rl_clear_history();

	exit(i);
}