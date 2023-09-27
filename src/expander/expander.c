/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 22:31:19 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/26 22:31:21 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int		loop_for_dollar_sign(t_cmds *ls_cmds, char *str, char **tmp, int i)
{
	int		j;
	char	**envs;
	char	*tmp2;
	char	*tmp3;
	int		ret;
	
	j = 0;
	ret = 0;
	envs = ls_cmds->ls_envs->envs;
	while (envs[j])
	{
		if (!ft_strncmp(str + i + 1, envs[j], equal_sign(envs[j]) - 1)
			&& len_no_specific(str, i) - i == (int)equal_sign(envs[j]))
		{
			tmp2 = ft_strdup(envs[j] + equal_sign(envs[j]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = equal_sign(envs[j]);
		}
		j++;
	}
	if (!ret)
		ret = len_no_specific(str, i) - i;
	ft_printf("done");
	return (ret);
}

int		handle_digit_after_dollar(int j, char *str)
{
	int	i;

	i = j;
	if (str[i] == '$')
	{
		if (ft_isdigit(str[i + 1]))
			i += 2;
	}
	return (i - j);
}

char	*expand_variable(t_cmds *ls_cmds, char *str)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = 0;
	tmp = ft_strdup("\0");
	ls_cmds = NULL;
	while (str[i])
	{
		i += handle_digit_after_dollar(i, str);
		if (str[i] == '$' && (str[i + 1] != ' ' && (str[i + 1] != '"'
			|| str[i + 2])) && str[i + 1])
			i += loop_for_dollar_sign(ls_cmds, str, &tmp, i);
		else
		{
			tmp2 = char_to_str(str[i++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	ls_cmds = ls_cmds->next;
	return (tmp);
}

char	**expander_arr(t_cmds *ls_cmds, char **arr)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (arr[i])
	{
		if (dollar_sign(arr[i])
			&& arr[i][dollar_sign(arr[i])])
		{
			tmp = expand_variable(ls_cmds, arr[i]);
			free(arr[i]);
			arr[i] = tmp;
		}
		if (ft_strncmp(arr[0], "export", ft_strlen(arr[0]) - 1))
		{
			arr[i] = delete_quotes(arr[i], '\"');
			arr[i] = delete_quotes(arr[i], '\'');
		}
		// ft_printf("ls_cmd %d : %s len : %d\n", i, arr[i], ft_strlen(arr[i]));
		i++;
	}
	return (arr);
}

char	*expander_str(t_cmds *ls_cmds, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (dollar_sign(str)
		&& str[dollar_sign(str)])
	{
		tmp = expand_variable(ls_cmds, str);
		free(str);
		str = tmp;
	}
	str = delete_quotes(str, '\"');
	str = delete_quotes(str, '\'');
	ft_printf("done");
	return (str);
}
