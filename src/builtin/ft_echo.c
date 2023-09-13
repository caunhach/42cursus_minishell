/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:49:41 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/13 20:49:44 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

static int	count_cmds(char **cmds)
{
	int	i;

	i = 0;
	while(cmds[i])
		i++;
	return (i);
}

int	ft_echo(t_cmds *ls_cmds)
{
	int		len_cmds;
	int		i;
	int		option;
	char	**cmds;

	i = 1;
	option = 0;
	cmds = ls_cmds->cmds;
	len_cmds = count_cmds(cmds);
	if (len_cmds > 1)
	{
		if (!ft_strncmp(cmds[i],"-n", 2))
		{
			option = 1;
			i++;
		}
		while (cmds[i])
		{
			ft_putstr_fd(cmds[i], 1);
			if (cmds[i][0] != '\0' && cmds[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (!option)
		write(1, "\n", 1);
	return (0);
}
