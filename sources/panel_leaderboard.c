/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_leaderboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 09:58:07 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:34:33 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// reads player data from a file and returns an array of players
static t_player_data	*ft_load_players_from_file(int *count)
{
	int				fd;
	t_player_data	*players;
	t_player_data	player;
	int				valid;

	players = NULL;
	*count = 0;
	fd = open(PLAYER_DATA_FILE, O_RDONLY);
	if (fd < 0)
		return (NULL);
	player = ft_read_player_line(fd, &valid);
	while (player.name[0] != '\0' || valid)
	{
		if (valid)
			players = ft_add_player(players, player, count);
		player = ft_read_player_line(fd, &valid);
	}
	close(fd);
	return (players);
}

// sort players in ascending order by game time
static void	ft_sort_players_by_time(t_player_data *players, int count)
{
	int				i;
	int				j;
	t_player_data	tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (players[i].game_time_ms > players[j].game_time_ms)
			{
				tmp = players[i];
				players[i] = players[j];
				players[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

// load players from file and return them sorted by time
static t_player_data	*ft_get_top_players(int *count)
{
	t_player_data	*players;

	players = ft_load_players_from_file(count);
	if (players)
		ft_sort_players_by_time(players, *count);
	return (players);
}

// render the leaderboard panel with top players
void	ft_display_leaderboard(t_game *game, int panel_y)
{
	int				count;
	t_player_data	*top_players;

	top_players = ft_get_top_players(&count);
	if (!top_players || count == 0)
		return ;
	ft_render_leaderboard_header(game, panel_y);
	ft_render_leaderboard_entries(game, panel_y, top_players, count);
	free(top_players);
}
