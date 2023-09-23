/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 21:48:17 by caunhach          #+#    #+#             */
/*   Updated: 2023/09/08 21:54:37 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execution.h"

int	cmds_first(t_cmds **ls_cmds)
{
	while (*ls_cmds && (*ls_cmds)->previous)
		*ls_cmds = (*ls_cmds)->previous;
	return (EXIT_SUCCESS);
}

int	cmds_add(t_cmds *ls_cmds, char *args)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = (char **)malloc(sizeof(char *) * (ls_cmds->len_cmd + 2));
	if (!tmp)
		return (exit_fatal());
	while (++i < ls_cmds->len_cmd)
		tmp[i] = ls_cmds->cmds[i];
	if (ls_cmds->len_cmd)
		free(ls_cmds->cmds);
	ls_cmds->cmds = tmp;
	ls_cmds->cmds[i++] = ft_strdup(args);
	ls_cmds->cmds[i] = 0;
	ls_cmds->len_cmd++;
	return (EXIT_SUCCESS);
}

int	cmds_push(t_cmds **ls_cmds, char *args, t_envs *env)
{
	t_cmds	*new;

	new = (t_cmds *)malloc(sizeof(t_cmds));
	if (!new)
		return (exit_fatal());
	new->cmds = NULL;
	new->hd_filename = NULL;
	new->len_cmd = 0;
	new->previous = NULL;
	new->next = NULL;
	new->ls_envs = env;
	new->ls_lexers = NULL;
	if (*ls_cmds)
	{
		(*ls_cmds)->next = new;
		new->previous = *ls_cmds;
	}
	*ls_cmds = new;
	return (cmds_add(new, args));
}

int	parse_arg(t_cmds **ls_cmds, char *args, t_envs *env)
{
	if (!*ls_cmds || is_pipe((*ls_cmds)->ls_lexers))
		return (cmds_push(ls_cmds, args, env));
	else if (ft_strncmp("|", args, 1) == 0)
	{
		lexers_push(*ls_cmds, args);
		lexer_first(*ls_cmds);
		return (0);
	}		
	else if (is_redirect(args))
		return (lexers_push(*ls_cmds, args));
	else if ((*ls_cmds)->ls_lexers && !(*ls_cmds)->ls_lexers->str)
		return (lexers_add((*ls_cmds)->ls_lexers, args));
	else
		return (cmds_add(*ls_cmds, args));
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	int		ret;
	t_envs	*ls_envs;
	t_cmds	*ls_cmds;

	ret = EXIT_SUCCESS;
	ls_cmds = NULL;
	ls_envs = NULL;
	parse_env(&ls_envs, env);
	update_dir(ls_envs, NULL);
	i = 1;
	while (i < argc)
		parse_arg(&ls_cmds, argv[i++], ls_envs);
	// lexer_first(&ls_cmds->ls_lexers);
	cmds_first(&ls_cmds);
	// print_cmds(ls_cmds);
	// print_env(ls_envs);
	// print_pwd(ls_envs);
	if (ls_cmds->next == NULL)
		single_execution(ls_cmds);
	else
		execution(ls_cmds);
	// print_env(ls_envs);
	// print_pwd(ls_envs);
	// if (ls_cmds)
	free_all(ls_cmds);
	return (ret);
}
