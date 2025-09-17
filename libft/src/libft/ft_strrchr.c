/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:16:24 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The strrchr() function returns a pointer to the last occurrence
	of the character c in the string s. 
*/

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	const char		*last_occ;
	size_t			i;
	unsigned char	uc;

	last_occ = NULL;
	i = 0;
	uc = (unsigned char)c;
	while (str[i])
	{
		if (str[i] == uc)
			last_occ = &str[i];
		i++;
	}
	if (str[i] == uc)
		last_occ = &str[i];
	return ((char *)last_occ);
}
