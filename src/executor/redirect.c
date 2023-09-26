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

int	redirect_input(t_cmds *ls_cmds)
{
	int	fd;
	char	*file;

	if (ls_cmds->ls_lexers->types == LESS)
		file = ls_cmds->ls_lexers->str;
	else
		file = ls_cmds->hd_filename;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: infile: No such file or directory\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_append_outfile(t_lexers *ls_lexers)
{
	int	fd;

	if (ls_lexers->types == GREAT_GREAT)
		fd = open(ls_lexers->str,
				O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(ls_lexers->str,
				O_CREAT | O_RDWR | O_TRUNC, 0644);
	return (fd);
}

int	redirect_output(t_lexers *ls_lexers)
{
	int	fd;

	fd = check_append_outfile(ls_lexers);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: outfile: ERROR\n",
			STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
	{
		ft_putstr_fd("minishell: pipe error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (fd > 0)
		close(fd);
	return (EXIT_SUCCESS);
}

int	check_redirect(t_cmds *ls_cmds)
{
	t_lexers *start;

	start = ls_cmds->ls_lexers;
	while (ls_cmds->ls_lexers)
	{
		if (ls_cmds->ls_lexers->types == LESS
			|| ls_cmds->ls_lexers-> types == LESS_LESS)
		{
			if (redirect_input(ls_cmds))
				return (EXIT_FAILURE);
		}
		else if (ls_cmds->ls_lexers->types == GREAT
			|| ls_cmds->ls_lexers-> types == GREAT_GREAT)
		{
			if (redirect_output(ls_cmds->ls_lexers))
				return (EXIT_FAILURE);
		}
		ls_cmds->ls_lexers = ls_cmds->ls_lexers->next;
	}
	ls_cmds->ls_lexers = start;
	return (EXIT_SUCCESS);
}
