/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 13:56:02 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The strcmp() function compares the two strings s1 and s2.
	The locale is not taken into account (for a locale-aware comparison,
	see strcoll(3)). The comparison is done using un‐signed characters.

		strcmp() returns an integer indicating the result of the comparison,
		as follows:

		•  0, if the s1 and s2 are equal;
		•  a negative value if s1 is less than s2;
		•  a positive value if s1 is greater than s2.

		The strncmp() function is similar, except it compares only
		the first (at most) n bytes of s1 and s2.
 */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while ((i < (n - 1)) && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	return (us1[i] - us2[i]);
}
