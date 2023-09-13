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

#include "../inc/execution.h"

void	print_array(char **arr, char *str)
{
	int	i;

	i = -1;
	ft_printf("%s :\n", str);
	while (arr[++i])
		ft_printf("%s\n", arr[i]);
}

void	print_env(t_envs *ls_envs)
{
	print_array(ls_envs->envs, "envs");
	print_array(ls_envs->path, "path");
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
