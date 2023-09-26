/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 23:58:47 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/10 23:58:51 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int		ft_heredoc(t_cmds *ls_cmds, t_lexers *heredoc, char *file_name)
{
	delete_quotes()
}

char	*generate_hd_filename(void)
{
	static	int	i;
	char		*num;
	char		*file_name;

	i = 0;
	num = ft_itoa(i++);
	file_name = ft_strjoin("build/.tmp_heredoc_file_", num);
	free(num);
	return (file_name);
}

int	heredoc_main(t_cmds *ls_cmds, t_lexers *ls_lexers)
{
	t_lexers	*head;
	int			exit_status;

	head = ls_lexers;
	while (ls_lexers)
	{
		if (ls_lexers->types == LESS_LESS)
		{
			if (ls_cmds->hd_filename)
				free(ls_cmds->hd_filename);
			ls_cmds->hd_filename = generate_hd_filename();
			exit_status = ft_heredoc(ls_cmds, ls_cmds->ls_lexers, ls_cmds->hd_filename);
		}
		ls_lexers = ls_lexers->next;
	}
	ls_lexers = head;
	return (EXIT_SUCCESS);
}
