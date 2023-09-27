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

#include "../../inc/execution.h"

int	is_redirect(char *args)
{
	if (!ft_strncmp(args, "<", ft_strlen(args)))
		return (1);
	else if (!ft_strncmp(args, ">", ft_strlen(args)))
		return (1);
	else if (!ft_strncmp(args, "<<", ft_strlen(args)))
		return (1);
	else if (!ft_strncmp(args, ">>", ft_strlen(args)))
		return (1);
	return (0);
}

int	lexers_add(t_lexers *ls_lexers, char *args)
{
	ls_lexers->str = ft_strdup(args);
	if (!ls_lexers->str)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	lexers_push(t_cmds *ls_cmds, char *args)
{
	t_lexers	*new;

	new = NULL;
	new = (t_lexers *)malloc(sizeof(t_lexers));
	if (!new)
		return (EXIT_FAILURE);
	new->str = NULL;
	if (!ft_strncmp(args, "<", ft_strlen(args)))
		new->types = LESS;
	else if (!ft_strncmp(args, ">", ft_strlen(args)))
		new->types = GREAT;
	else if (!ft_strncmp(args, "<<", ft_strlen(args)))
		new->types = LESS_LESS;
	else if (!ft_strncmp(args, ">>", ft_strlen(args)))
		new->types = GREAT_GREAT;
	else if (!ft_strncmp(args, "|", ft_strlen(args)))
		new->types = PIPE;
	// ft_printf("args : %s type : %d\n", args, new->types);
	new->previous = NULL;
	new->next = NULL;
	if (ls_cmds->ls_lexers)
	{
		ls_cmds->ls_lexers->next = new;
		new->previous = ls_cmds->ls_lexers;
	}
	ls_cmds->ls_lexers = new;
	return (EXIT_SUCCESS);
}

int	lexer_first(t_cmds *ls_cmds)
{
	while (ls_cmds->ls_lexers->previous)
		ls_cmds->ls_lexers = ls_cmds->ls_lexers->previous;
	return (EXIT_SUCCESS);
}

int is_pipe(t_lexers *ls_lexers)
{
	while (ls_lexers)
	{
		if (ls_lexers->types == PIPE)
			return (1);
		ls_lexers = ls_lexers->next;
	}
	return (0);
}
