/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:36:49 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The calloc() function allocates memory for an array of nmemb elements
	of size bytes each and returns a pointer to the allocated memory.
	The memory is set to zero.

	If nmemb or size is 0, then calloc() returns a unique pointer value
	that can later be successfully passed to free().
	If the multiplication of nmemb and size would result in integer overflow,
	then calloc() returns an error.

	By contrast, an integer overflow would not be detected in the following
	call to malloc(), with the result that an incorrectly sized block
	of memory would be allocated:

		malloc(nmemb * size);
*/

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	total_size = nmemb * size;
	if (total_size / nmemb != size)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
