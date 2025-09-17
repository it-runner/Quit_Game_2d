/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiles.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 01:46:02 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 21:30:28 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// draw all map tiles at specified coordinates
void	ft_draw_tiles(t_game *game, int x_map, int y_map, int tile_size)
{
	ft_draw_basic_tiles(game, x_map, y_map, tile_size);
	ft_draw_special_tiles(game, x_map, y_map, tile_size);
}

// updates the display after the player moves
void	ft_update_display_after_move(t_game *game, int next_y, int next_x,
	int tile_size)
{
	ft_draw_player(game, next_y, next_x, tile_size);
	ft_restore_previous_tile(game, tile_size);
	game->player.y_char += next_y;
	game->player.x_char += next_x;
	game->player.move_count++;
	ft_printf("Move number %d\n", game->player.move_count);
	ft_display_info_panel(game);
}

// load exit texture and render exit if successful
void	ft_load_exit(t_game *game)
{
	if (ft_draw_open_exit_texture(game))
		ft_render_exit(game);
}

// check if player can exit level and handle win condition
void	ft_handle_exit_tile(t_game *game, int tile_code, char mod,
	int tile_size)
{
	int	offset_x;
	int	offset_y;

	offset_x = game->map_offset_x;
	offset_y = game->map_offset_y;
	if (tile_code == 'E' && game->player.inventory == game->map.item_count)
	{
		ft_draw_exit(game, mod, tile_size);
		mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
			game->floor.img, offset_x + game->player.x_char * tile_size,
			offset_y + game->player.y_char * tile_size);
		ft_handle_level_win(game);
	}
}

// display optional side images (left and right)
void	ft_display_side_images(t_game *game)
{
	int	left_x;

	if (!game->side_img_left && !game->side_img_right)
		return ;
	if (game->side_img_left)
	{
		left_x = game->map_offset_x - game->side_img_width - 240;
		ft_display_left_images(game, left_x);
	}
	if (game->side_img_right)
		ft_display_right_image(game);
}
