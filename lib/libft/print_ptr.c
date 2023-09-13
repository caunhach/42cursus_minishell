/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:28:14 by caunhach          #+#    #+#             */
/*   Updated: 2023/03/01 12:29:50 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/libft.h"

int	put_ptr(unsigned long long arg)
{
	int	i;

	i = 0;
	if (arg > 15)
	{
		i += put_ptr(arg / 16);
		i += put_ptr(arg % 16);
	}
	else if (arg > 9)
	{
		i += print_char(arg - 10 + 'a');
	}
	else
	{
		i += print_char(arg + '0');
	}
	return (i);
}

int	print_ptr(unsigned long long arg)
{
	int	i;

	i = 0;
	i += print_str("0x");
	i += put_ptr(arg);
	return (i);
}
