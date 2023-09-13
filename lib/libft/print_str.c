/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:15:19 by caunhach          #+#    #+#             */
/*   Updated: 2023/03/01 12:16:19 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/libft.h"

int	print_str(char *arg)
{
	int	i;

	if (arg == NULL)
	{
		ft_putstr_fd("(null)", 1);
		i = 6;
		return (i);
	}
	i = ft_strlen(arg);
	ft_putstr_fd(arg, 1);
	return (i);
}
