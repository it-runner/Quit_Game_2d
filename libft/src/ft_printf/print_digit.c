/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:01:36 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_digit(int n)
{
	int		len;
	char	num;

	len = 0;
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		return (print_digit(n) + 1);
	}
	if (n < 10)
	{
		num = n + '0';
		write(1, &num, 1);
		return (1);
	}
	else
	{
		len = print_digit(n / 10);
		return (len + print_digit(n % 10));
	}
}
