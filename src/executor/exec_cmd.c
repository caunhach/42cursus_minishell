/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:43:24 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/10 23:43:26 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

char	*get_path_cmd(char *cmd, char **ls_path)
{
	int		i;
	char	*tmp_path;

	i = -1;
	while (ls_path[++i])
	{
		tmp_path = ft_strjoin(ls_path[i], cmd);
		if (access(tmp_path, F_OK) == 0)
			return (tmp_path);
		free(tmp_path);
	}
	return (cmd);
}

int	exec_cmd(t_cmds *ls_cmds)
{
	char	*path;
	t_envs	*ptr_envs;

	ptr_envs = ls_cmds->ls_envs;
	path = get_path_cmd(ls_cmds->cmds[0], ptr_envs->path);
	if (execve(path, ls_cmds->cmds, ptr_envs->envs) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(ls_cmds->cmds[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
