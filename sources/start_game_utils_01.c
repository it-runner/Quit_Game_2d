/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_utils_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:15:22 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 19:50:44 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// record the game's start time in milliseconds
void	ft_set_game_start_time(t_game *game)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	game->start_time_ms = (long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000;
}

// initialize the MLX library and store the pointer in the game structure
int	ft_init_mlx(t_game *game)
{
	game->show.mlx_ptr = mlx_init();
	if (!game->show.mlx_ptr)
	{
		ft_error(game, "Could not start mlx");
		return (0);
	}
	return (1);
}

// set up and display the game window
int	ft_init_window(t_game *game)
{
	int	screen_width;
	int	screen_height;

	if (!ft_set_window_resolution(game, &screen_width, &screen_height))
		return (0);
	if (!ft_init_game_window(game, screen_width, screen_height))
		return (0);
	ft_move_window_to_top_left(game->show.mlx_ptr, game->show.win_ptr);
	return (1);
}

// retrieve the usable screen resolution (width and height) in pixels.
int	ft_get_screen_resolution(int *width, int *height)
{
	Display	*display;
	int		screen;
	int		usable_w;
	int		usable_h;

	display = XOpenDisplay(NULL);
	if (!display)
		return (0);
	screen = DefaultScreen(display);
	if (ft_get_screen_workarea(display, screen, &usable_w, &usable_h))
	{
		*width = usable_w;
		*height = usable_h;
	}
	else
	{
		*width = DisplayWidth(display, screen);
		*height = DisplayHeight(display, screen) - 70;
	}
	XCloseDisplay(display);
	return (1);
}

// calculate map offsets to center it within the window
void	ft_center_map_on_screen(t_game *game)
{
	game->map_offset_x = (game->show.x_win
			- (game->map.line_size * TILE_SIZE)) / 2;
	game->map_offset_y = (game->show.y_win - INFO_PANEL_HEIGHT
			- (game->map.col_size * TILE_SIZE)) / 2;
	game->current_tile_size = TILE_SIZE;
}
