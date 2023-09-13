/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:08:27 by caunhach          #+#    #+#             */
/*   Updated: 2023/03/02 11:32:07 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/libft.h"

int	print_args(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == 'c')
		i += print_char(va_arg(args, int));
	else if (c == 's')
		i += print_str(va_arg(args, char *));
	else if (c == 'p')
		i += print_ptr(va_arg(args, unsigned long long));
	else if (c == 'd' || c == 'i')
		i += print_int(va_arg(args, int));
	else if (c == 'u')
		i += print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x')
		i += print_hex(va_arg(args, unsigned int), 'a');
	else if (c == 'X')
		i += print_hex(va_arg(args, unsigned int), 'A');
	return (i);
}

int	ft_printf(const char *s, ...)
{
	int		i;
	va_list	args;

	i = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%' && *(s + 1))
		{
			if (ft_strchr("cspdiuxX", *(s + 1)))
				i += print_args(*(s + 1), args);
			else if (*(s + 1) == '%')
				i += print_char('%');
			s += 2;
		}
		else if (*s == '%' && !*(s + 1))
			break ;
		else
		{
			i += print_char(*s);
			s++;
		}
	}
	va_end(args);
	return (i);
}
