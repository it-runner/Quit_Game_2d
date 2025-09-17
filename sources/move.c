/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:40:48 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:27:04 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// move player in 4 directions: up, down, left, right
void	ft_move_up(t_game *game)
{
	ft_move_player(game, -1, 0, 'u');
}

void	ft_move_down(t_game *game)
{
	ft_move_player(game, 1, 0, 'd');
}

void	ft_move_left(t_game *game)
{
	ft_move_player(game, 0, -1, 'l');
}

void	ft_move_right(t_game *game)
{
	ft_move_player(game, 0, 1, 'r');
}
