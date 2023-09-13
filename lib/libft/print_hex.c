/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:17:13 by caunhach          #+#    #+#             */
/*   Updated: 2023/03/01 12:26:00 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/libft.h"

int	print_hex(unsigned int arg, char asc)
{
	int	i;

	i = 0;
	if (arg > 15)
	{
		i += print_hex(arg / 16, asc);
		i += print_hex(arg % 16, asc);
	}
	else if (arg > 9)
	{
		i += print_char(arg - 10 + asc);
	}
	else
	{
		i += print_char(arg + '0');
	}
	return (i);
}
