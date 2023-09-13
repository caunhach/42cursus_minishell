/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 23:28:52 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/13 23:28:55 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

void	print_env(t_envs *ls_envs)
{
	print_array(ls_envs->envs, "envs");
	print_array(ls_envs->path, "path");
}

int	update_env(t_envs *ls_envs)
{
	int	i;

	i = -1;
	while(ls_envs->envs[++i])
	{
		if (!ft_strncmp(ls_envs->envs[i], "PWD=", 4))
		{
			free(ls_envs->envs[i]);
			ls_envs->envs[i] = ft_strjoin("PWD=", ls_envs->pwd);
			if (!ls_envs->envs[i])
				return (1);
		}
		else if (!ft_strncmp(ls_envs->envs[i], "OLDPWD=", 7))
		{
			free(ls_envs->envs[i]);
			ls_envs->envs[i] = ft_strjoin("OLDPWD=", ls_envs->old_pwd);
			if (!ls_envs->envs[i])
				return (1);
		}
	}
	return (0);
}
