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
		tmp2 = char_to_str(str[i++]);
		tmp3 = ft_strjoin(tmp, tmp2);
		free(tmp);
		free(tmp2);
		tmp = tmp3;
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
		if (arr[i][dollar_sign(arr[i]) - 2] != '\'' && dollar_sign(arr[i])
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
		i++;
	}
	return (arr);
}

char	*expander_str(t_cmds *ls_cmds, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (str[dollar_sign(str) - 2] != '\'' && dollar_sign(str)
		&& str[dollar_sign(str)])
	{
		tmp = expand_variable(ls_cmds, str);
		free(str);
		str = tmp;
	}
	str = delete_quotes(str, '\"');
	str = delete_quotes(str, '\'');
	return (str);
}
