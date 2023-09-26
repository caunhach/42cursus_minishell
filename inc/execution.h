/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:57:30 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/16 14:57:35 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/uio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/inc/libft.h"

typedef enum s_types
{
	PIPE = 1,
	LESS = 2,
	LESS_LESS = 3,
	GREAT = 4,
	GREAT_GREAT = 5,
}	t_types;

typedef struct s_lexers
{
	char			*str;
	t_types			types;
	struct s_lexers	*previous;
	struct s_lexers	*next;
}	t_lexers;

typedef struct s_envs
{
	char	**envs;
	char	**path;
	char	*pwd;
	char	*old_pwd;
}	t_envs;

typedef struct s_cmds
{
	char			**cmds;
	char			*hd_filename;
	int				len_cmd;
	int				pipes[2];
	pid_t			pid;
	t_lexers		*ls_lexers;
	t_envs			*ls_envs;
	struct s_cmds	*previous;
	struct s_cmds	*next;
}	t_cmds;

/* builtin */
/* builtin_utils.c */
int		check_valid_identifier(char c);
int		equal_sign(char *str);
int		env_len(char **arr);
void	sort_env(char **tab, int len);
void	print_sorted_env(t_envs *ls_envs);

/* builtin.c */
int		is_builtin(char *cmd);
int		is_builtin2(char *cmd);
int		exec_builtin(t_cmds *ls_cmds);

/* ft_cd.c */
char	*get_env_var(t_envs *ls_envs, char *var);
int		go_to_path(t_envs *ls_envs, char *var);
int		ch_dir(char *cmds);
int		update_pwd(t_envs *ls_envs);
int		ft_cd(char **cmds, t_envs *ls_envs);

/* ft_echo.c */
int		ft_echo(t_cmds *ls_cmds);

/* ft_env.c */
int		ft_env(t_envs *ls_envs);

/* ft_export.c */
int		is_in_env(t_cmds *ls_cmds);
char	**loop_add_env(char **arr, char **rtn, char *str);
int		ft_export(t_cmds *ls_cmds, t_envs *ls_envs);

/* ft_pwd.c */
int		ft_pwd(t_envs *ls_envs);

/* ft_unset.c */
char	**loop_del_var(char **envs, char **rtn, char *var);
char	**del_var(char **envs, char *var);
int		check_unset_cmds(char *cmd);
int		check_unset(char **cmds);
int		ft_unset(t_cmds *ls_cmds);

/* executor */
/* redirect.c */
int		redirect_input(t_cmds *ls_cmds);
int		check_append_outfile(t_lexers *ls_lexers);
int		redirect_output(t_lexers *ls_lexers);
int		check_redirect(t_cmds *ls_cmds);

/* free.c */
void	free_lexers(t_lexers *ls_lexers);
void	free_envs(t_envs *ls_envs);
void	free_all(t_cmds *ls_cmds);

/* heredoc.c */
int		exec_heredoc(t_cmds *ls_cmds, char *filename);
int		ft_heredoc(t_cmds *ls_cmds, t_lexers *heredoc, char *file_name);
char	*generate_hd_filename(void);
int		heredoc_main(t_cmds *ls_cmds, t_lexers *ls_lexers);

/* main.c */
int		parse_arg(t_cmds **ls_cmds, char *args, t_envs *env);
int		cmds_push(t_cmds **ls_cmds, char *args, t_envs *env);
int		cmds_add(t_cmds *ls_cmds, char *args);
int		cmds_first(t_cmds **ls_cmds);

/* error.c */
int		exit_fatal(void);
int		cmd_not_found(char *str);
int		export_error(char *c);

/* exec_expand.c */
int		expand_cmd_and_lexers(t_cmds *ls_cmds);

/* exec_main.c */
void	pre_exec_cmd(t_cmds *ls_cmds);
int		parent_fork(t_cmds *ls_cmds, int *fd_in);
int		child_fork(t_cmds *ls_cmds, int fd_in);
int		ft_fork(t_cmds *ls_cmds, int *fd_in);
int		execution(t_cmds *ls_cmds);

/* exec_single_main.c*/
int		single_execution(t_cmds *ls_cmds);

/* exec_cmd.c */
char	*get_path_cmd(char *cmd, char **ls_path);
int		exec_cmd(t_cmds *ls_cmds);

/* utils.c */
void	free_array(char **arr);
char	**dup_array(char **env);
void	print_array(char **arr, char *str);
void	print_cmds(t_cmds *ls_cmds);
void	print_pwd(t_envs *ls_envs);

/* parse_env.c */
int		parse_env(t_envs **ls_envs, char **env);
char	*get_path(char **envp);
char	*get_pwd(char **envp);
char	*get_old_pwd(char **envp);
int		update_dir(t_envs *ls_envs, char *new_pwd);

/* utils_env.c */
void	print_env(t_envs *ls_envs);
int		update_env(t_envs *ls_envs);

/* expander */
/* expander_utils.c */
char	*char_to_str(char c);
size_t	dollar_sign(char *str);
char	*delete_quotes(char *str, char c);
/* expander.c */
int		handle_digit_after_dollar(int j, char *str);
char	*expand_variable(t_cmds *ls_cmds, char *str);
char	**expander_arr(t_cmds *ls_cmds, char **arr);
char	*expander_str(t_cmds *ls_cmds, char *str);

/* lexer */
/* utils_lexer.c */
int		is_redirect(char *args);
int		lexers_add(t_lexers *ls_lexers, char *args);
int		lexers_push(t_cmds *ls_cmds, char *args);
int		is_pipe(t_lexers *ls_lexers);
int		lexer_first(t_cmds *ls_cmds);

#endif
