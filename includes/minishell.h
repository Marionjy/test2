/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 19:34:56 by mjacquet          #+#    #+#             */
/*   Updated: 2022/04/25 18:12:26 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

extern int	g_status;

enum e_type {
	NONE,			//0
	ARG,			//1
	SG_QUOTE,		//2
	DB_QUOTE,		//3
	REDIR_IN,		//4
	REDIR_OUT,		//5
	HEREDOC,		//6
	REDIR_OUT_APP,	//7
	IN_FILE,		//8
	OUT_FILE,		//9
	LIMITOR,		//10
	OUT_FILE_APP,	//11
	PIPE,			//12
};

typedef struct s_sublist
{
	char				*str;
	int					type;
	int					len;
	struct s_sublist	*prev;
	struct s_sublist	*next;
}				t_sublist;

typedef struct s_token
{
	char			*str;
	enum e_type		type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_elem_env
{
	char				*name;
	char				*value;
	struct s_elem_env	*next;
}				t_elem_env;


typedef struct s_cmd_box
{
	int					len;
	int					fd_in;	//a supprimer
	int					fd_out;
	t_token				*args;
	struct s_cmd_box	*next;
}				t_cmd_box;

typedef struct s_data
{
	int			nb_pipes;
	int			pwd;
	char		*pwd_value;
	char		*pwd_name;
	int			i;
	t_token		**list_token;
	// char		**arr;
	t_elem_env	*l_env;
	t_cmd_box	**l_cmd;
	pid_t		*pid;
	char		**arr_env;
	char		**av;
}				t_data;

typedef struct s_splitstf
{
	int	i;
	int	x;
	int	k;
}				t_splitstf;


//	UTILS
int			is_same(char *s1, char *s2);
size_t		ft_strlen(char *str);
char		*ft_strdup(char *str);
char		*ft_strndup(char const *s, size_t len);
int			count_nb_elem(char *str);
char		**splitting(char *str);
char		**creat_tab(char **arr, int nb_elem, char *str);
int			ft_is_deli(char c);
char		*ft_strchr(char *str, char c);
int			ft_command(t_data *data,char  **str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(const char *s1, const char *s2);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strjoin_char(const char *s1, char c);
int			freetab(char **arr);
char		**mktab(char **arr, char const *s, char c, int i);
char		**ft_split(char const *s, char c);
char		*ft_strcjoin(char *line, char *buf, char const c);
int			ft_isalpha_string(char *str);
int			ft_isalpha(char c);
int			ft_isnum(char c);
int			ft_isnum_string(char *str);
void		affiche_arr(char **arr);
void		free_arr(char **arr);

//CMD BOX
void		disp_l_cmd(t_cmd_box *cmd);
t_cmd_box	*new_cmd(t_token *list, int len);
int			push_back_cmd(t_data *stf, t_token *list, int len);
t_cmd_box	*get_last_cmd(t_cmd_box *cmd);
void		destroy_lcmd(t_cmd_box *cmd_list);

//COMMAND
char		*ft_pwd(void);
int			ft_strlen_arr(char **str);
int			ft_command(t_data *data, char **str);

//	ENV
int			pop_elem_env(t_data *data, t_elem_env *elem);
t_elem_env	*new_elem_env(char *str);
void		push_back_elem_env(t_data *data, char *str);
void		ft_create_list_env(t_data *data);
void		display_env(t_elem_env *list);
void		destroy_env(t_data *data);

int			len_env(t_elem_env *env);
char		*get_str_env(t_elem_env *env);
char		**l_env_to_array(t_elem_env *env);

//EXEC_UTILS
char		**arg_maker(t_token *token, int nb_elem);
t_elem_env	*ft_get_var(t_data *data, char *name);
int			count_pipes(t_token *list);

//EXEC
int			mk_cmd_box(t_data *stf);
void		set_sig_dft(void);
void		set_sig_hd_child(void);
void		close_fds(int *pipefd, int fd_in);
void		close_fds2(int fd1, int fd2);
int			make_redir(t_data *data, t_cmd_box *cmd, int nb_redir);
int			count_redir(t_data *data, t_cmd_box *cmd);


//EXPAND
int			expand_a_var(t_data *data, t_sublist *sublist);
size_t		get_new_len(t_sublist *sublist);
int			expand_db_quote(t_data *data, t_sublist *sublist);
int			expand_sg_quote(t_data *data, t_sublist *sublist);
int			expand_arg(t_data *data, t_sublist *sublist);
int			expand_sublist(t_token *token, t_data *data, t_sublist *sublist);
t_sublist	*sublist_quote(t_token *token);

//HANDLER
void		handler(int sig);
void		handler_child(int sig);
void		set_sig_dft(void);
void		set_sig_hd_child(void);

//MAIN
void		free_arr(char **arr);
int			ft_init(t_data *data);
// void		affiche_tab(char **arr)


//NEW EXEC
int			exec_general(t_data *data);
void		exec_without_pipes(t_data *data);
void		exec_with_pipes(t_data *data);
void		launch_exec(char **av, char **env, t_data *data);

//SPLITTING COUNT
int			count_deli(char *str);
int			ft_error_quote(char c);
int			suppr_deli_quote(char *str, int *nb_elem, int i, char c);
int			count_nb_elem_bis(char *str, int *i, int nb_elem);
int			count_nb_elem(char *str);

//SPLITTING CREATE TAB
char		**creat_tab_deli(char *str, int *y, int *i, char **arr);
void		pass_quote_tab(char *str, int *y, int *x);
char		**creat_tab(char **arr, int nb_elem, char *str);

//SPLITTING
int			fill_tab_deli(char *str, int *y, int i, char **arr);
char		**fill_quote_tab(char *str, t_splitstf *stf, char **arr, char c);
char		**fill_tab_bis(char *str, t_splitstf *stf, char **arr);
char		**fill_tab(char **arr, int nb_elem, char *str);
char		**splitting(char *str);

//SUBLIST
int			pop_sublist(t_sublist *sublist);
void		destroy_sublist(t_sublist *sublist);
t_sublist	*new_elem_sublist(char *str, int len, int type);
t_sublist	*get_last_sublist(t_sublist *sublist);
int			push_back_sublist(t_sublist **sublist, char *str, int len, int type);
int			create_sublist(t_data *data);
char		*join_sublist(t_sublist *sublist);
void		display_sublist(t_sublist *sublist);

//	TOKEN
int			assign_file(t_token *list);
int			ft_assign_type(char *str);

t_token		*new_token(char *str);
int			pop_token(t_token *elem);
void		destroy_l_token(t_token *list);
t_token		*get_last_token(t_token	*list);
void		display_list_token(t_token *list);
void		ndisplay_list_w_op(t_token *list, int len);
int			push_back_token(t_data *data, char *str);
void		create_list_token(t_data *data, char **arr_token);

//UTILS_BIS
int			ft_isalpha(char c);
int			ft_isalpha_string(char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_is_deli(char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strjoin_char(const char *s1, char c);

//	UTILS
char		*ft_strchr(char *str, char c);
int			is_same(char *s1, char *s2);
size_t		ft_strlen(char *str);
char		*ft_strdup(char *str);
char		*ft_strndup(char const *s, size_t len);
int			freetab(char **arr);
char		**mktab(char **arr, char const *s, char c, int i);
char		**ft_split(char const *s, char c);
char		*ft_strcjoin(char *line, char *buf, char const c);

// bultins
char		*ft_cd(char **str, t_data *data);
t_elem_env	*ft_unset(t_data *data, char *comp);
int			ft_export(t_data *data, char **str, int i);
char		*ft_strdup_egal2(char *export);
char		*ft_strdup_egal(char *export);
void		tri_alpha(t_elem_env *data);
char		*ft_echo(char **str, int i);
int			malloc_result_bis(char *str, int *i, int taille);
int			malloc_result(char *str);
char		*fill_result_bis(char *result, char *str, int *i, int *y);
int			ft_option_n(char *str);
int			ft_builtin_exit(char *str);
int			ft_unset_not_valid(char *str);
//int	ft_modif_env_bis(t_elem_env *li, t_data *data);
int			modif_env(char *str, t_elem_env *li, t_data *data);
char		*change_pwd(t_elem_env *li, char *tmp, t_data *data);
char		*find_last_bis(t_elem_env *li2, char *tmp);
char		*find_last(t_elem_env *li);
int			change_oldpwd_bis(t_elem_env *li, t_data *data, char *value);
int			change_oldpwd(t_elem_env *li, t_data *data);
int			base_bis(int i, char *tmp, t_elem_env *li, t_data *data);
char		*ft_pwd();

// new_exec
int			exec_general(t_data *data);
void		exec_without_pipes(t_data *data);
t_elem_env	*ft_get_var(t_data *data, char *name);
void		launch_exec(char **av, char **env, t_data *data);
char		**arg_maker(t_token *token, int nb_elem);
void		exec_with_pipes(t_data *data);
//EXEC
void		handler_child(int sig);
int			count_pipes(t_token *list);
int			mk_cmd_box(t_data *stf);
void		set_sig_dft(void);
void		set_sig_hd_child(void);
void		close_fds(int *pipefd, int fd_in);
void		close_fds2(int fd1, int fd2);


void		ft_exit(t_data *data, int i);


char		*ft_cd(char **str, t_data *data);
char		*ft_echo(char **str, int i);
int			ft_builtin_exit(char *str);
int			ft_unset_not_valid(char *str);

#endif
