/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:26:24 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/13 20:26:26 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	is_builtin2(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd, "export", 6))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd, "env", 3))
		return (1);
	else if (!ft_strncmp(cmd, "export", 6))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	return (0);
}

int	exec_builtin(t_cmds *ls_cmds)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strncmp(ls_cmds->cmds[0], "echo", 4))
		exit_status = ft_echo(ls_cmds);
	else if (!ft_strncmp(ls_cmds->cmds[0], "pwd", 3))
		exit_status = ft_pwd(ls_cmds->ls_envs);
	else if (!ft_strncmp(ls_cmds->cmds[0], "cd", 2))
		exit_status = ft_cd(ls_cmds->cmds, ls_cmds->ls_envs);
	else if (!ft_strncmp(ls_cmds->cmds[0], "env", 3))
		exit_status = ft_env(ls_cmds->ls_envs);
	else if (!ft_strncmp(ls_cmds->cmds[0], "export", 6))
		exit_status = ft_export(ls_cmds, ls_cmds->ls_envs);
	else if (!ft_strncmp(ls_cmds->cmds[0], "unset", 5))
		exit_status = ft_unset(ls_cmds);
	// print_pwd(ls_cmds->ls_envs);
	return (exit_status);
}
