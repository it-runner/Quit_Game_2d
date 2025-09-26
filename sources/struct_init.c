/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:33:15 by so_long           #+#    #+#             */
/*   Updated: 2025/09/17 11:28:14 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// initialize all map fields to default values
static int	ft_init_map(t_game *game)
{
	game->map.item_count = 0;
	game->map.exit_count = 0;
	game->map.hero_count = 0;
	game->map.col_size = 0;
	game->map.line_size = 0;
	return (1);
}

// initialize tile struct
static int	ft_init_tile(t_game *game)
{
	if (!ft_init_tile_hero(game))
		return (0);
	if (!ft_init_tile_item(game))
		return (0);
	if (!ft_init_tile_exit(game))
		return (0);
	if (!ft_init_tile_floor(game))
		return (0);
	if (!ft_init_tile_wall(game))
		return (0);
	return (1);
}

// initialize char struct
int	ft_init_char(t_game *game)
{
	game->player.x_char = 0;
	game->player.y_char = 0;
	game->player.move_count = 0;
	game->player.inventory = 0;
	game->last_step_ms = 0;
	game->player.moving_up = 0;
	game->player.moving_down = 0;
	game->player.moving_left = 0;
	game->player.moving_right = 0;
	game->player.up_pressed = 0;
	game->player.down_pressed = 0;
	game->player.left_pressed = 0;
	game->player.right_pressed = 0;
	return (1);
}

// initialize show struct
int	ft_init_show(t_game *game)
{
	game->show.mlx_ptr = 0;
	game->show.win_ptr = 0;
	game->show.x_win = 0;
	game->show.y_win = 0;
	game->side_img_left = NULL;
	game->side_img_right = NULL;
	game->side_img_width = 0;
	game->side_img_height = 0;
	game->side_img_spacing = 30;
	return (1);
}

// initialize game structs
int	ft_init_game_structs(t_game *game)
{
	if (!ft_init_map(game))
		return (0);
	if (!ft_init_char(game))
		return (0);
	if (!ft_init_tile(game))
		return (0);
	if (!ft_init_show(game))
		return (0);
	if (game->current_level == 0)
		game->acc_time_ms = 0;
	game->frame_count = 0;
	game->current_time_ms = 0;
	game->total_time_ms = 0;
	game->panel.img = NULL;
	game->current_tile_size = TILE_SIZE;
	game->map_offset_x = 0;
	game->map_offset_y = 0;
	game->start_time_ms = 0;
	game->end_time_ms = 0;
	game->last_update_ms = 0;
	game->completed = 0;
	return (1);
}
