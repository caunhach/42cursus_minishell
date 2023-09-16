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
# include "../lib/libft/inc/libft.h"

typedef enum s_types
{
	type_pipe,
	type_end,
}	t_types;

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
	int				len_cmd;
	int				pipes[2];
	pid_t			pid;
	t_types			types;
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

/* ft_pwd.c*/
int		ft_pwd(t_envs *ls_envs);

/* executor */
/* main.c */
int		parse_arg(t_cmds **ls_cmds, char *args, t_envs *env);
int		cmds_push(t_cmds **ls_cmds, char *args, t_envs *env);
int		cmds_add(t_cmds *ls_cmds, char *args);
int		cmds_first(t_cmds **ls_cmds);

/* error.c */
int		exit_fatal(void);
int		cmd_not_found(char *str);
int		export_error(char *c);

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
char	*delete_quotes(char *str, char c);

#endif
