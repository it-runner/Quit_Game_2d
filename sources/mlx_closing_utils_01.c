/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_closing_utils_01.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:08:18 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:29:40 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// return elapsed time in milliseconds since the level started
long long	ft_get_level_time(t_game *game)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	game->end_time_ms = (long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (game->end_time_ms - game->start_time_ms);
}

// check if conditions are met to load the next level
int	ft_should_load_next_level(t_game *game)
{
	if (game->player.inventory == game->map.item_count
		&& game->current_level < game->total_levels - 1
		&& game->completed)
	{
		game->current_level++;
		return (1);
	}
	return (0);
}

// handle initialization and start of the next game level
int	ft_start_next_level(t_game *game, long long level_time)
{
	game->acc_time_ms += level_time;
	ft_init_game_structs(game);
	if (ft_valid_map(game->level_list[game->current_level], game))
	{
		if (ft_start_game(game))
			return (1);
	}
	return (0);
}

// print formatted total game time (HH:MM:SS)
static void	ft_print_total_time(long long time_ms)
{
	int		seconds;
	int		minutes;
	int		hours;
	char	*tmp;

	seconds = (time_ms / 1000) % 60;
	minutes = (time_ms / (1000 * 60)) % 60;
	hours = (time_ms / (1000 * 60 * 60));
	ft_printf("\n\n\033[1;38;5;178m");
	ft_printf("\n\tTotal game time: ");
	tmp = ft_pad_zero(hours);
	ft_printf("%s:", tmp);
	free(tmp);
	tmp = ft_pad_zero(minutes);
	ft_printf("%s:", tmp);
	free(tmp);
	tmp = ft_pad_zero(seconds);
	ft_printf("%s\n\n", tmp);
	free(tmp);
	ft_printf("\033[0m");
}

// update player stats and save data if the level was completed
void	ft_finalize_level(t_game *game, long long level_time)
{
	game->acc_time_ms += level_time;
	if (game->completed)
	{
		game->player_data.game_time_ms = game->acc_time_ms;
		game->player_data.moves = game->player.move_count;
		game->player_data.score = game->player.inventory * 100;
		ft_save_player_data(game);
		ft_print_total_time(game->acc_time_ms);
	}
}
