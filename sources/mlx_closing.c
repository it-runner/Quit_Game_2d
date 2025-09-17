/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_closing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:49:52 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 11:21:12 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// handle level transition or cleanup when destroying the map
int	ft_finish_level(t_game *game)
{
	long long	level_time;
	int			next;

	level_time = ft_get_level_time(game);
	next = ft_should_load_next_level(game);
	if (game->player.inventory == game->map.item_count && !game->completed)
		next = 0;
	if (next)
	{
		if (ft_start_next_level(game, level_time))
			return (0);
	}
	else
		ft_finalize_level(game, level_time);
	ft_free_mlx_resources(game);
	ft_cleanup_game(game, next);
	return (0);
}
