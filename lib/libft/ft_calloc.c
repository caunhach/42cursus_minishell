/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caunhach <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 20:18:44 by caunhach          #+#    #+#             */
/*   Updated: 2023/02/20 14:54:18 by caunhach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	n;
	size_t	i;

	i = 0;
	if (nmemb >= SIZE_MAX || size >= SIZE_MAX || size * nmemb >= SIZE_MAX)
		return (NULL);
	n = nmemb * size;
	ptr = (unsigned char *)malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	while (n--)
		*((unsigned char *)ptr + i++) = 0;
	return (ptr);
}
