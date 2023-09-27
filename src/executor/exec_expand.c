/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 23:19:27 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/26 23:19:30 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	expand_cmd_and_lexers(t_cmds *ls_cmds)
{
	t_lexers	*start;

	start = ls_cmds->ls_lexers;
	ls_cmds->cmds = expander_arr(ls_cmds, ls_cmds->cmds);
	while (ls_cmds->ls_lexers)
	{
		if (ls_cmds->ls_lexers->types != LESS_LESS && ls_cmds->ls_lexers->str)
			ls_cmds->ls_lexers->str
				= expander_str(ls_cmds, ls_cmds->ls_lexers->str);
		ls_cmds->ls_lexers = ls_cmds->ls_lexers->next;
	}
	ls_cmds->ls_lexers = start;
	// ft_printf("done");
	return (EXIT_SUCCESS);
}
