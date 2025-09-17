/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 20:27:02 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 11:21:11 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// helper function to print banner
static void	ft_print_level_banner(char *str)
{
	ft_printf("\n\n\033[1;38;5;155m");
	ft_printf("  -----------------------------------------------------------	\
		\n\n");
	ft_printf("     %s         L  E  V  E  L    C  O  M  P  L  E  T  E  D 		\
		\n\n", str);
	ft_printf("  -----------------------------------------------------------	\
		\033[0m\n\n");
}

// print level completed banner to the console
static void	ft_level_completed_banner(int level_number)
{
	char	level_str[3];
	char	*num_str;

	if (level_number + 1 < 10)
	{
		level_str[0] = '0';
		level_str[1] = (level_number + 1) + '0';
		level_str[2] = '\0';
	}
	else
	{
		num_str = ft_itoa(level_number + 1);
		if (num_str)
		{
			ft_strlcpy(level_str, num_str, 3);
			free(num_str);
		}
		else
		{
			level_str[0] = '0';
			level_str[1] = '1';
			level_str[2] = '\0';
		}
	}
	ft_print_level_banner(level_str);
}

// handle win state: mark level completed, show banner, and load next level
void	ft_handle_level_win(t_game *game)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	game->end_time_ms = (long long)tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	ft_printf("\n\n  YOU WIN!\n");
	ft_level_completed_banner(game->current_level);
	game->completed = 1;
	if (ft_load_next_level(game) == 0)
		ft_finish_level(game);
}
