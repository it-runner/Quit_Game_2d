/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 22:07:36 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 23:02:22 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// create an info panel image for the game window
static void	ft_create_info_panel_image(t_game *game)
{
	game->panel.width = game->show.x_win;
	game->panel.height = INFO_PANEL_HEIGHT;
	game->panel.img = mlx_new_image(game->show.mlx_ptr,
			game->panel.width, game->panel.height);
	game->panel.addr = mlx_get_data_addr(game->panel.img,
			&game->panel.bits_per_pixel, &game->panel.size_line,
			&game->panel.endian);
}

// fill the entire panel with a solid background color
static void	ft_fill_panel_background(t_game *game, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->panel.height)
	{
		x = 0;
		while (x < game->panel.width)
		{
			ft_put_pixel_to_image(&game->panel, x, y, color);
			x++;
		}
		y++;
	}
}

// renders all HUD panel elements at the given vertical position
static void	render_panel_text(t_game *game, int panel_y)
{
	long long	current_time_ms;

	current_time_ms = ft_get_level_time_ms(game);
	ft_display_player_name(game, panel_y);
	ft_render_game_info_title(game, panel_y);
	ft_display_level_number(game, panel_y);
	ft_render_time_panel(game, panel_y, current_time_ms);
	ft_render_player_stats(game, panel_y);
	ft_display_exit_status(game, panel_y);
	ft_display_leaderboard(game, panel_y);
}

// render the bottom info panel with background, border, and text
void	ft_display_info_panel(t_game *game)
{
	int	panel_y_start;

	panel_y_start = game->show.y_win - INFO_PANEL_HEIGHT;
	if (!game->panel.img)
		ft_create_info_panel_image(game);
	ft_fill_panel_background(game, 0x1a1f27);
	ft_draw_line_on_panel(game, (t_line)
	{
		0, 0, game->panel.width, 0, 0x666666
	});
	mlx_put_image_to_window(game->show.mlx_ptr, game->show.win_ptr,
		game->panel.img, 0, panel_y_start);
	render_panel_text(game, panel_y_start);
}

// print time in hours:minutes:seconds
char	*ft_make_time_str(int hours, int minutes, int seconds)
{
	char	*h;
	char	*m;
	char	*s;
	char	*tmp;
	char	*time_str;

	h = ft_pad_zero(hours);
	m = ft_pad_zero(minutes);
	s = ft_pad_zero(seconds);
	if (!h || !m || !s)
		return (NULL);
	tmp = ft_strjoin(h, ":");
	time_str = ft_strjoin(tmp, m);
	free(tmp);
	tmp = ft_strjoin(time_str, ":");
	free(time_str);
	time_str = ft_strjoin(tmp, s);
	free(tmp);
	free(h);
	free(m);
	free(s);
	return (time_str);
}
