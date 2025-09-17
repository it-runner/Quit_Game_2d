/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 11:50:49 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 21:22:02 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// draw a basic wall or floor tile at the given map coordinates
void	ft_draw_basic_tiles(t_game *game, int x_map, int y_map, int tile_size)
{
	int	offset_x;
	int	offset_y;

	offset_x = game->map_offset_x;
	offset_y = game->map_offset_y;
	if (game->map.map[y_map][x_map] == '1')
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->wall.img, offset_x + x_map * tile_size,
			offset_y + y_map * tile_size);
	else if (game->map.map[y_map][x_map] == '0')
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->floor.img, offset_x + x_map * tile_size,
			offset_y + y_map * tile_size);
}

// draw special tiles like player, exit, and collectible on the window
void	ft_draw_special_tiles(t_game *game, int x_map, int y_map, int tile_size)
{
	int	offset_x;
	int	offset_y;

	offset_x = game->map_offset_x;
	offset_y = game->map_offset_y;
	if (game->map.map[y_map][x_map] == 'P')
	{
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->hero.img, offset_x + x_map * tile_size,
			offset_y + y_map * tile_size);
		game->map.map[y_map][x_map] = '0';
	}
	else if (game->map.map[y_map][x_map] == 'E')
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->exit.img, offset_x + x_map * tile_size,
			offset_y + y_map * tile_size);
	else if (game->map.map[y_map][x_map] == 'C')
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->item.img, offset_x + x_map * tile_size,
			offset_y + y_map * tile_size);
}

// draw the player at the next position on the window
void	ft_draw_player(t_game *game, int next_y, int next_x, int tile_size)
{
	int	offset_x;
	int	offset_y;

	offset_x = game->map_offset_x;
	offset_y = game->map_offset_y;
	mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
		game->hero.img,
		offset_x + (game->player.x_char + next_x) * tile_size,
		offset_y + (game->player.y_char + next_y) * tile_size);
}

// clear the player's previous tile and redraw floor or exit
void	ft_restore_previous_tile(t_game *game, int tile_size)
{
	int	offset_x;
	int	offset_y;
	int	x;
	int	y;

	offset_x = game->map_offset_x;
	offset_y = game->map_offset_y;
	x = game->player.x_char;
	y = game->player.y_char;
	if (game->map.map[y][x] == 'E'
		&& game->player.inventory != game->map.item_count)
	{
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->exit.img, offset_x + x * tile_size, offset_y + y * tile_size);
		game->map.map[y][x] = 'E';
	}
	else
	{
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->floor.img, offset_x + x * tile_size,
			offset_y + y * tile_size);
		game->map.map[y][x] = '0';
	}
}
