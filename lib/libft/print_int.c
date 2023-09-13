/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:26:22 by caunhach          #+#    #+#             */
/*   Updated: 2023/03/01 12:27:44 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/libft.h"

int	print_int(int arg)
{
	int	i;

	i = 0;
	if (arg == -2147483648)
	{
		i += print_char('-');
		i += print_char('2');
		i += print_int(147483648);
	}
	else if (arg < 0)
	{
		i += print_char('-');
		arg *= -1;
		i += print_int(arg);
	}
	else if (arg > 9)
	{
		i += print_int(arg / 10);
		i += print_int(arg % 10);
	}
	else
		i += print_char(arg + 48);
	return (i);
}
