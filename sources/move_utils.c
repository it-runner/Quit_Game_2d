/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 00:55:33 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:26:11 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// handle player collecting an item and update game state
static void	ft_collect_item(t_game *game, int dy, int dx, int tile_size)
{
	game->map.map[game->player.y_char + dy][game->player.x_char + dx] = '0';
	ft_update_display_after_move(game, dy, dx, tile_size);
	game->player.inventory++;
	ft_display_info_panel(game);
	if (game->player.inventory == game->map.item_count)
		ft_load_exit(game);
}

// move player onto exit tile and update the game window
static void	ft_move_player_to_exit(t_game *game, int dy, int dx, int tile_size)
{
	int	offset_x;
	int	offset_y;

	offset_x = game->map_offset_x;
	offset_y = game->map_offset_y;
	mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
		game->hero.img, offset_x + (game->player.x_char + dx) * tile_size,
		offset_y + (game->player.y_char + dy) * tile_size);
	mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
		game->floor.img, offset_x + (game->player.x_char) * tile_size,
		offset_y + (game->player.y_char) * tile_size);
	game->player.x_char += dx;
	game->player.y_char += dy;
	game->player.move_count++;
	ft_printf("Move number %d\n", game->player.move_count);
}

// handle player movement based on the type of the next tile
void	ft_move_player(t_game *game, int dy, int dx, char dir)
{
	int		tile_size;
	char	next_tile;

	tile_size = game->current_tile_size;
	next_tile = game->map.map[game->player.y_char + dy]
	[game->player.x_char + dx];
	ft_handle_exit_tile(game, next_tile, dir, tile_size);
	if (next_tile == '0')
		ft_update_display_after_move(game, dy, dx, tile_size);
	else if (next_tile == 'C')
		ft_collect_item(game, dy, dx, tile_size);
	else if (next_tile == 'E' && game->player.inventory != game->map.item_count)
		ft_move_player_to_exit(game, dy, dx, tile_size);
}
