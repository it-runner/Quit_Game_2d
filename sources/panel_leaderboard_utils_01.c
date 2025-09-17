/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_leaderboard_utils_01.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 13:35:19 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:32:43 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// build a string by combining rank number and player name
static char	*ft_format_ranked_name(int rank, const char *name)
{
	char	*num;
	char	*tmp;
	char	*result;

	num = ft_itoa(rank);
	if (!num)
		return (NULL);
	tmp = ft_strjoin(num, ". ");
	free(num);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, name);
	free(tmp);
	return (result);
}

// render the "Top 3 Players" header on the leaderboard panel
void	ft_render_leaderboard_header(t_game *game, int panel_y)
{
	int	start_x;
	int	start_y;

	start_x = game->show.x_win - 640;
	start_y = panel_y + 40;
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		start_x, start_y, 0xDD8700, "T O P  3   P L A Y E R S");
}

// render a single leaderboard entry (player name + time)
static void	ft_render_leaderboard_entry(t_game *game, int y,
	t_player_data player, int rank)
{
	char	*time_str;
	char	*rank_text;

	time_str = ft_make_time_str(player.game_time_ms / 3600000,
			(player.game_time_ms / 60000) % 60,
			(player.game_time_ms / 1000) % 60);
	rank_text = ft_format_ranked_name(rank, player.name);
	if (rank_text)
	{
		mlx_string_put(game->show.mlx_ptr,
			game->show.win_ptr, 1280, y, 0xFFFFFF, rank_text);
		free(rank_text);
	}
	else
		mlx_string_put(game->show.mlx_ptr,
			game->show.win_ptr, 1280, y, 0xFFFFFF, "(unknown)");
	if (time_str)
	{
		mlx_string_put(game->show.mlx_ptr,
			game->show.win_ptr, 1560, y, 0x44FF44, time_str);
		free(time_str);
	}
	else
		mlx_string_put(game->show.mlx_ptr,
			game->show.win_ptr, 1560, y, 0x44FF44, "00:00:00");
}

// render up to 3 top players on the leaderboard panel
void	ft_render_leaderboard_entries(t_game *game, int panel_y,
	t_player_data *top_players, int count)
{
	int	start_y;
	int	i;

	start_y = panel_y + 40;
	i = 0;
	while (i < count && i < 3)
	{
		ft_render_leaderboard_entry(game, start_y + 30 + (i * 25),
			top_players[i], i + 1);
		i++;
	}
}

// render the current level number on the game panel
void	ft_display_level_number(t_game *game, int panel_y)
{
	char	*level_num;
	char	*text;

	level_num = ft_pad_zero(game->current_level + 1);
	if (!level_num)
		return ;
	text = ft_strjoin("L E V E L   ", level_num);
	free(level_num);
	if (!text)
		return ;
	mlx_string_put(game->show.mlx_ptr, game->show.win_ptr,
		940, panel_y + 130, 0x44AA99, text);
	free(text);
}
