/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 10:54:41 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The memset() function fills the first n bytes of the memory area
	pointed to by s with the constant byte c.

	The memset() function returns a pointer to the memory area s.
*/

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*s;

	if (!ptr)
		return (NULL);
	if (num == 0)
		return (ptr);
	i = 0;
	s = (unsigned char *)ptr;
	while (i < num)
	{
		s[i] = (unsigned char)value;
		i++;
	}
	return (ptr);
}
