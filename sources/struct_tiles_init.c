/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tiles_init.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 07:23:07 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// initializes hero tile to default values
int	ft_init_tile_hero(t_game *game)
{
	game->hero.x_tile = 0;
	game->hero.y_tile = 0;
	game->hero.img = NULL;
	game->hero.addr = NULL;
	game->hero.bits_per_pixel = 0;
	game->hero.size_line = 0;
	game->hero.endian = 0;
	return (1);
}

// initializes item tile to default values
int	ft_init_tile_item(t_game *game)
{
	game->item.x_tile = 0;
	game->item.y_tile = 0;
	game->item.img = NULL;
	game->item.addr = NULL;
	game->item.bits_per_pixel = 0;
	game->item.size_line = 0;
	game->item.endian = 0;
	return (1);
}

// initializes exit tile to default values
int	ft_init_tile_exit(t_game *game)
{
	game->exit.x_tile = 0;
	game->exit.y_tile = 0;
	game->exit.img = NULL;
	game->exit.addr = NULL;
	game->exit.bits_per_pixel = 0;
	game->exit.size_line = 0;
	game->exit.endian = 0;
	return (1);
}

// initializes floor tile to default values
int	ft_init_tile_floor(t_game *game)
{
	game->floor.x_tile = 0;
	game->floor.y_tile = 0;
	game->floor.img = NULL;
	game->floor.addr = NULL;
	game->floor.bits_per_pixel = 0;
	game->floor.size_line = 0;
	game->floor.endian = 0;
	return (1);
}

// initializes wall tile to default values
int	ft_init_tile_wall(t_game *game)
{
	game->wall.x_tile = 0;
	game->wall.y_tile = 0;
	game->wall.img = NULL;
	game->wall.addr = NULL;
	game->wall.bits_per_pixel = 0;
	game->wall.size_line = 0;
	game->wall.endian = 0;
	return (1);
}
