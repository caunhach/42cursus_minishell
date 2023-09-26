/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:55:59 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/09 14:57:04 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	free_lexers(t_lexers *ls_lexers)
{
	t_lexers	*tmp;

	while (ls_lexers)
	{
		tmp = ls_lexers;
		if (ls_lexers->str)
			free(ls_lexers->str);
		ls_lexers = ls_lexers->next;
		free(tmp);
		// ft_printf("free lexer\n");
	}
}

void	free_envs(t_envs *ls_envs)
{
	if (ls_envs->envs)
		free_array(ls_envs->envs);
	if (ls_envs->path)
		free_array(ls_envs->path);
	if (ls_envs->pwd)
		free(ls_envs->pwd);
	if (ls_envs->old_pwd)
		free(ls_envs->old_pwd);
}

void	free_all(t_cmds *ls_cmds)
{
	t_cmds	*tmp;

	tmp = ls_cmds;
	if (ls_cmds->ls_envs)
	{
		free_envs(ls_cmds->ls_envs);
		free(ls_cmds->ls_envs);
	}
	while (ls_cmds)
	{
		tmp = ls_cmds;
		if (ls_cmds->hd_filename)
			free(ls_cmds->hd_filename);
		if (ls_cmds->cmds)
			free_array(ls_cmds->cmds);
		if (ls_cmds->ls_lexers != NULL)
			free_lexers(ls_cmds->ls_lexers);
		ls_cmds = ls_cmds->next;
		free(tmp);
		// ft_printf("done\n");
	}
}
