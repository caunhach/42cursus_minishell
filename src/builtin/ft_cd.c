/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 21:33:37 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/13 21:33:39 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

char	*get_env_var(t_envs *ls_envs, char *var)
{
	char	**envs;
	char	*ret;
	int		i;
	int		len;

	i = -1;
	envs = ls_envs->envs;
	len = ft_strlen(var);
	while (envs[++i])
	{
		if (!ft_strncmp(envs[i], var, len))
		{
			ret = ft_substr(envs[i], len, ft_strlen(envs[i]) - len);
			if (!ret)
			{
				ft_putstr_fd("Failed to get env var :",
					STDERR_FILENO);
				ft_error(var);
			}
			return (ret);
		}
	}
	return (NULL);
}

int	go_to_path(t_envs *ls_envs, char *var)
{
	char	*path;
	char	*msg;
	int		ret;

	ret = 0;
	path = get_env_var(ls_envs, var);
	ret = chdir(path);
	msg = ft_substr(var, 0, ft_strlen(var) - 1);
	if (ret)
	{
		ft_putendl_fd("minishell : cd: ",
			STDERR_FILENO);
		ft_putendl_fd(msg, STDERR_FILENO);
		ft_putendl_fd(" not set", STDERR_FILENO);
		free(msg);
	}
	return (ret);
}

int	ch_dir(char *cmds)
{
	int	ret;

	ret = chdir(cmds);
	if (ret)
	{
		ft_putendl_fd("minishell : cd: ",
			STDERR_FILENO);
		ft_putendl_fd("no such file or directory: ",
			STDERR_FILENO);
		ft_putendl_fd(cmds, STDERR_FILENO);
		ft_putendl_fd(" not set", STDERR_FILENO);
	}
	return (ret);
}

int	update_pwd(t_envs *ls_envs)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;

	if (!getcwd(cwd, PATH_MAX))
		return (EXIT_FAILURE);
	new_pwd = ft_strdup(cwd);
	if (!new_pwd)
		ft_error("Failed to updated pwd");
	free(ls_envs->old_pwd);
	ls_envs->old_pwd = ls_envs->pwd;
	ls_envs->pwd = new_pwd;
	return (EXIT_SUCCESS);
}

int	ft_cd(char **cmds, t_envs *ls_envs)
{
	int		ret;

	ret = 0;
	if (!cmds[1])
		ret = go_to_path(ls_envs, "HOME=");
	else if (!ft_strncmp(cmds[1], "-", 1))
		ret = go_to_path(ls_envs, "OLDPWD=");
	else
		ret = ch_dir(cmds[1]);
	if (ret)
		return (EXIT_FAILURE);
	if (update_pwd(ls_envs))
		ft_error("cd : Failed to updated env");
	if (update_env(ls_envs))
		ft_error("cd : Failed to updated env");
	return (EXIT_SUCCESS);
}
