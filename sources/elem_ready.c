/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_ready.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 07:18:54 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:24:06 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// set player positions
static void	ft_set_player_pos(int i, int j, t_game *game)
{
	game->player.x_char = j;
	game->player.y_char = i;
}

// set exit positions
static void	ft_set_exit_pos(int i, int j, t_game *game)
{
	game->exit.x_tile = j;
	game->exit.y_tile = i;
}

// set player and exit positions
static t_game	*ft_set_elem_pos(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.col_size - 1)
	{
		j = 0;
		while (game->map.map[i][j] != '\n')
		{
			if (game->map.map[i][j] == 'P')
				ft_set_player_pos(i, j, game);
			if (game->map.map[i][j] == 'E')
				ft_set_exit_pos(i, j, game);
			j++;
		}
		i++;
	}
	return (game);
}

// check if game can be started (there is a player, exit and items)
int	ft_mission_ready(t_game *game)
{
	if (game->map.hero_count == 0)
	{
		ft_error(game, "    No game participants");
		return (0);
	}
	if (game->map.exit_count == 0)
	{
		ft_error(game, "    No exit");
		return (0);
	}
	if (game->map.item_count == 0)
	{
		ft_error(game, "    No item to hunt");
		return (0);
	}
	game = ft_set_elem_pos(game);
	return (1);
}
