/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:32:27 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 22:45:24 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// initialize map file paths
static void	ft_init_level_paths(t_game *game)
{
	game->level_list[0] = "maps/ex01.ber";
	game->level_list[1] = "maps/ex02.ber";
	game->level_list[2] = "maps/ex03.ber";
	game->level_list[3] = "maps/ex04.ber";
	game->level_list[4] = "maps/ex05.ber";
	game->level_list[5] = "maps/ex06.ber";
	game->level_list[6] = "maps/ex07.ber";
	game->level_list[7] = "maps/ex08.ber";
}

// initialize game levels by allocating memory and setting map file paths
t_game	*ft_init_levels(t_game *game)
{
	int	actual_levels;

	actual_levels = TOTAL_LEVELS;
	if (TOTAL_LEVELS > ALL_AVAILABLE_MAPS)
	{
		ft_printf("Warning: TOTAL_LEVELS (%d) > ALL_AVAILABLE_MAPS (%d). \
			Using %d levels.\n",
			TOTAL_LEVELS, ALL_AVAILABLE_MAPS, ALL_AVAILABLE_MAPS);
		actual_levels = ALL_AVAILABLE_MAPS;
	}
	game->total_levels = actual_levels;
	game->level_list = malloc(sizeof(char *) * (ALL_AVAILABLE_MAPS + 1));
	if (!game->level_list)
	{
		ft_nomap_error(game, "    Malloc error for level list.");
		return (NULL);
	}
	ft_bzero(game->level_list, sizeof(char *) * (ALL_AVAILABLE_MAPS + 1));
	ft_init_level_paths(game);
	game->current_level = 0;
	return (game);
}

// go to the next level, cleaning up current resources and updating game time
int	ft_load_next_level(t_game *game)
{
	struct timeval	tv;
	long long		now_ms;
	long long		level_time;

	if (game->current_level >= game->total_levels - 1)
		return (0);
	gettimeofday(&tv, NULL);
	now_ms = (long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	level_time = now_ms - game->start_time_ms;
	game->acc_time_ms += level_time;
	ft_free_images(game);
	mlx_destroy_window(game->show.mlx_ptr, game->show.win_ptr);
	mlx_destroy_display(game->show.mlx_ptr);
	free(game->show.mlx_ptr);
	ft_free_map(game);
	game->current_level++;
	game->completed = 0;
	ft_init_game_structs(game);
	if (ft_valid_map(game->level_list[game->current_level], game))
		return (ft_start_game(game));
	return (0);
}
