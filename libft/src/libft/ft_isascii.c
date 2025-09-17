/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:27:58 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	isascii() checks whether c is a 7-bit unsigned char value
	that fits into the ASCII character set.

	The value returned is nonzero if the character c falls into
	the tested class, and zero if not.
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
