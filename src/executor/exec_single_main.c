/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_main.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 14:03:11 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/16 14:03:12 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	single_execution(t_cmds *ls_cmds)
{
	int	pid;
	int	status;
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (is_builtin2(ls_cmds->cmds[0]))
	{
		exit_status = exec_builtin(ls_cmds);
		return (exit_status);
	}
	heredoc_main(ls_cmds, ls_cmds->ls_lexers);
	pid = fork();
	if (pid < 0)
		ft_error("Failed to fork\n");
	else if (pid == 0)
		pre_exec_cmd(ls_cmds);
	waitpid(pid, &status, 0);
	return (exit_status);
}
