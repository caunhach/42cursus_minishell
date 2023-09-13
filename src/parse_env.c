/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 01:39:21 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/11 01:39:23 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execution.h"

char	*get_path(char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5));
	}
	return (ft_strdup("\0"));
}

int	parse_env(t_envs **ls_envs, char **env)
{
	char	*path_env;
	char	*tmp;
	int		i;

	*ls_envs = (t_envs *)malloc(sizeof(t_envs));
	if (!*ls_envs)
		ft_error("Failed to parse env\n");
	(*ls_envs)->envs = dup_array(env);
	path_env = get_path((*ls_envs)->envs);
	(*ls_envs)->path = ft_split(path_env, ':');
	free(path_env);
	i = -1;
	while ((*ls_envs)->path[++i])
	{
		if (ft_strncmp(&(*ls_envs)->path[i]
			[ft_strlen((*ls_envs)->path[i]) - 1], "/", 1) != 0)
		{
			tmp = ft_strjoin((*ls_envs)->path[i], "/");
			free((*ls_envs)->path[i]);
			(*ls_envs)->path[i] = tmp;
		}
	}
	return (EXIT_SUCCESS);
}
