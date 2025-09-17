/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 11:15:40 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 21:01:35 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// return the elapsed level time in milliseconds
long long	ft_get_level_time_ms(t_game *game)
{
	struct timeval	tv;
	long long		current_time_ms;

	if (game->end_time_ms > 0)
		current_time_ms = game->end_time_ms - game->start_time_ms;
	else
	{
		gettimeofday(&tv, NULL);
		current_time_ms = (long long)tv.tv_sec * 1000LL
			+ tv.tv_usec / 1000
			- game->start_time_ms;
	}
	return (current_time_ms);
}

// display the current game time on the UI panel
static void	ft_render_current_time(t_game *game, int panel_y,
	long long current_time_ms)
{
	int		seconds;
	int		minutes;
	int		hours;
	char	*time_str;

	seconds = (current_time_ms / 1000) % 60;
	minutes = (current_time_ms / (1000 * 60)) % 60;
	hours = (current_time_ms / (1000 * 60 * 60));
	time_str = ft_make_time_str(hours, minutes, seconds);
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		400, panel_y + 40, 0xFF00FF, "T I M E");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		600, panel_y + 40, 0xDDDDDD, time_str);
	free(time_str);
}

// calculates and displays the total elapsed game time
static void	ft_render_total_time(t_game *game, int panel_y,
	long long current_time_ms)
{
	long long	total_time_ms;
	int			t_sec;
	int			t_min;
	int			t_hr;
	char		*total_str;

	total_time_ms = game->acc_time_ms + current_time_ms;
	t_sec = (total_time_ms / 1000) % 60;
	t_min = (total_time_ms / (1000 * 60)) % 60;
	t_hr = (total_time_ms / (1000 * 60 * 60));
	total_str = ft_make_time_str(t_hr, t_min, t_sec);
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		400, panel_y + 70, 0x44FF44, "T O T A L   T I M E");
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		600, panel_y + 70, 0xFFD799, total_str);
	free(total_str);
}

// draw the time panel showing level and total game time
void	ft_render_time_panel(t_game *game, int panel_y,
		long long current_time_ms)
{
	ft_render_current_time(game, panel_y, current_time_ms);
	ft_render_total_time(game, panel_y, current_time_ms);
}
