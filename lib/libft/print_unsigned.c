/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:19:00 by caunhach          #+#    #+#             */
/*   Updated: 2023/03/01 12:20:34 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/libft.h"

int	print_unsigned(unsigned int arg)
{
	int	i;

	i = 0;
	if (arg > 9)
	{
		i += print_unsigned(arg / 10);
		i += print_unsigned(arg % 10);
	}
	else
	{
		i += print_char(arg + '0');
	}
	return (i);
}
