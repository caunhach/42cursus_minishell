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

void	print_array(char **arr, char *str)
{
	int	i;

	i = -1;
	ft_printf("%s :\n", str);
	while (arr[++i])
		ft_printf("%s\n", arr[i]);
}

void	print_pwd(t_envs *ls_envs)
{
	ft_printf("PWD : %s\n", ls_envs->pwd);
	ft_printf("OLDPWD : %s\n", ls_envs->old_pwd);
}

void	print_cmds(t_cmds *ls_cmds)
{
	int		i;
	int		j;

	i = 1;
	j = -1;
	while (ls_cmds)
	{
		ft_printf("cmds %d :", i++);
		j = -1;
		while (ls_cmds->cmds[++j])
			ft_printf(" %s", ls_cmds->cmds[j]);
		ft_printf("\ntypes of cmds %d : ", i - 1);
		if (ls_cmds->types == type_pipe)
			ft_printf("PIPE\n");
		else if (ls_cmds->types == type_end)
			ft_printf("END\n");
		ls_cmds = ls_cmds->next;
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	**dup_array(char **env)
{
	size_t	i;
	size_t	len;
	char	**res;

	i = -1;
	len = 0;
	while (env[++i])
		len++;
	res = (char **)malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (env[++i])
	{
		res[i] = ft_strdup(env[i]);
		if (!res[i])
		{
			free_array(res);
			return (res);
		}
	}
	res[i] = 0;
	return (res);
}
