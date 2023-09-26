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

#include "../../inc/execution.h"

void	pre_exec_cmd(t_cmds *ls_cmds)
{
	int	exit_status;

	exit_status = EXIT_SUCCESS;
	if (ls_cmds->ls_lexers)
		if (check_redirect(ls_cmds))
			exit(1);
	if (is_builtin(ls_cmds->cmds[0]))
		exit_status = exec_builtin(ls_cmds);
	else if (ls_cmds->cmds[0][0] != '\0')
		exit_status = exec_cmd(ls_cmds);
	exit (exit_status);
}

int	parent_fork(t_cmds *ls_cmds, int *fd_in)
{
	if (ls_cmds->next)
		close(ls_cmds->pipes[1]);
	if (ls_cmds->next)
		*fd_in = ls_cmds->pipes[0];
	return (EXIT_SUCCESS);
}

int	child_fork(t_cmds *ls_cmds, int fd_in)
{
	if (ls_cmds->previous && dup2(fd_in, STDIN_FILENO) < 0)
		ft_error("Failed to dup2\n");
	if (ls_cmds->next && dup2(ls_cmds->pipes[1], STDOUT_FILENO) < 0)
		ft_error("Failed to dup2\n");
	if (ls_cmds->previous)
		close(fd_in);
	pre_exec_cmd(ls_cmds);
	return (EXIT_SUCCESS);
}

int	ft_fork(t_cmds *ls_cmds, int *fd_in)
{
	int		status;

	ls_cmds->pid = fork();
	if (ls_cmds->pid < 0)
		ft_error("Failed to fork\n");
	else if (ls_cmds->pid == 0)
	{
		child_fork(ls_cmds, *fd_in);
	}
	else
	{
		waitpid(ls_cmds->pid, &status, 0);
		parent_fork(ls_cmds, fd_in);
		// ft_printf("done bot child and parent\n");
	}
	return (EXIT_SUCCESS);
}

int	execution(t_cmds *ls_cmds)
{
	int		fd_in;

	fd_in = STDIN_FILENO;
	if (ls_cmds->next != NULL)
	{
		while (ls_cmds)
		{
			if (ls_cmds->next)
			{
				if (pipe(ls_cmds->pipes) < 0)
					ft_error("Failed to pipe\n");
			}
			heredoc_main(ls_cmds, ls_cmds->ls_lexers);
			ft_fork(ls_cmds, &fd_in);
			ls_cmds = ls_cmds->next;
		}
	}
	return (EXIT_SUCCESS);
}
