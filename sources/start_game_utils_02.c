/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game_utils_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 19:40:44 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:17:51 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// draw the entire game map on the window
void	ft_render_map(t_game *game)
{
	int	x;
	int	y;

	if (!game || !game->show.mlx_ptr || !game->show.win_ptr || !game->map.map)
		return ;
	mlx_clear_window(game->show.mlx_ptr, game->show.win_ptr);
	ft_display_side_images(game);
	x = 0;
	while (x < game->map.line_size)
	{
		y = 0;
		while (y < game->map.col_size)
		{
			ft_draw_tiles(game, x, y, TILE_SIZE);
			y++;
		}
		x++;
	}
}

// clear all player data by truncating the data file
void	ft_reset_player_file(void)
{
	int	fd;

	fd = open(PLAYER_DATA_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf("Error: Could not reset player data file\n");
		return ;
	}
	close(fd);
}

// set game window size based on the current screen resolution
int	ft_set_window_resolution(t_game *game, int *w, int *h)
{
	if (!ft_get_screen_resolution(w, h))
	{
		ft_error(game, "Could not get screen resolution");
		return (0);
	}
	game->show.x_win = *w;
	game->show.y_win = *h;
	return (1);
}

// create a new game window with the specified width and height
int	ft_init_game_window(t_game *game, int w, int h)
{
	game->show.win_ptr = mlx_new_window(
			game->show.mlx_ptr, w, h, "Quit Game 2D");
	if (!game->show.win_ptr)
	{
		mlx_destroy_display(game->show.mlx_ptr);
		free(game->show.mlx_ptr);
		ft_error(game, "Could not open game window");
		return (0);
	}
	return (1);
}

// move the window to the top-left corner of the screen
void	ft_move_window_to_top_left(void *mlx_ptr, void *win_ptr)
{
	t_xvar		*xvar;
	t_win_list	*winl;

	xvar = (t_xvar *)mlx_ptr;
	winl = (t_win_list *)win_ptr;
	if (xvar && winl)
	{
		XMoveWindow(xvar->display, winl->window, 0, 0);
		XFlush(xvar->display);
	}
}
