
#ifndef EXECUTION_H
# define EXECUTION_H

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <limits.h>
#include "../lib/libft/inc/libft.h"

typedef enum s_types
{
	type_pipe,
	type_end,
}	t_types;

typedef	struct	s_envs
{
	char	**envs;
	char	**path;
	char	*pwd;
	char	*old_pwd;
}	t_envs;

typedef struct	s_cmds
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
/* builtin.c */
int		is_builtin(char *cmd);
int		exec_builtin(t_cmds *ls_cmds);

/* ft_echo.c*/
int		ft_echo(t_cmds *ls_cmds);

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

/* execution.c */
void	pre_exec_cmd(t_cmds *ls_cmds);
int		parent_fork(t_cmds *ls_cmds, int *fd_in);
int		child_fork(t_cmds *ls_cmds, int fd_in);
int		ft_fork(t_cmds *ls_cmds, int *fd_in);
int		execution(t_cmds *ls_cmds);

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

#endif
