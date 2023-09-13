/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:59:38 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/09 17:00:23 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

void	pre_exec_cmd(t_cmds *ls_cmds)
{
	int	exit_status;

	exit_status = 0;
	if (ls_cmds->cmds[0][0] != '\0')
		exit_status = exec_cmd(ls_cmds);
	exit (exit_status);
}

int	parent_fork(t_cmds *ls_cmds, int *fd_in)
{
	if (ls_cmds->next)
	{
		close(ls_cmds->pipes[1]);
		*fd_in = ls_cmds->pipes[0];
	}
	return (EXIT_SUCCESS);
}

int	child_fork(t_cmds *ls_cmds, int fd_in)
{
	if (ls_cmds->previous && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error("Failed to dup2\n");
	close(ls_cmds->pipes[0]);
	if (ls_cmds->next && dup2(ls_cmds->pipes[1], STDOUT_FILENO) < 0)
		ft_error("Failed to dup2\n");
	close(ls_cmds->pipes[1]);
	if (ls_cmds->previous)
		close(fd_in);
	pre_exec_cmd(ls_cmds);
	return (EXIT_SUCCESS);
}

int	ft_fork(t_cmds *ls_cmds, int *fd_in)
{
	int		status;

	if (ls_cmds->next)
	{
		if (pipe(ls_cmds->pipes) < 0)
			ft_error("Failed to pipe\n");
	}
	ls_cmds->pid = fork();
	if (ls_cmds->pid < 0)
		ft_error("Failed to fork\n");
	else if (ls_cmds->pid == 0)
		child_fork(ls_cmds, *fd_in);
	else
	{
		waitpid(ls_cmds->pid, &status, 0);
		parent_fork(ls_cmds, fd_in);
	}
	return (EXIT_SUCCESS);
}

int	execution(t_cmds *ls_cmds)
{
	int		fd_in;

	// fd_in = open("mini_a.txt", O_RDONLY);
	fd_in = STDIN_FILENO;
	while(ls_cmds)
	{
		ft_fork(ls_cmds, &fd_in);
		ls_cmds = ls_cmds->next;
	}
	return (EXIT_SUCCESS);
}
