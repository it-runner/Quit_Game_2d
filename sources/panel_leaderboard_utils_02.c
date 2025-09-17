/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_leaderboard_utils_02.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:02:07 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 23:07:17 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// parse a single player line into a t_player_data struct
static t_player_data	ft_parse_player_line(char *line)
{
	t_player_data	player;
	char			**data;
	int				i;

	player.name[0] = '\0';
	player.game_time_ms = 0;
	data = ft_split(line, '|');
	if (!data || !data[0] || !data[1])
		return (player);
	ft_strlcpy(player.name, data[0], sizeof(player.name));
	player.game_time_ms = ft_atoi(data[1]);
	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
	return (player);
}

// add a new player to the dynamic array of players
t_player_data	*ft_add_player(t_player_data *players,
	t_player_data new_player, int *count)
{
	t_player_data	*tmp;
	int				i;

	tmp = malloc(sizeof(t_player_data) * (*count + 1));
	if (!tmp)
		return (players);
	i = 0;
	while (i < *count)
	{
		tmp[i] = players[i];
		i++;
	}
	tmp[*count] = new_player;
	free(players);
	(*count)++;
	return (tmp);
}

// read and parse a player line from the file descriptor
t_player_data	ft_read_player_line(int fd, int *valid)
{
	char			*line;
	t_player_data	player;

	player.name[0] = '\0';
	*valid = 0;
	line = get_next_line(fd);
	if (line)
	{
		player = ft_parse_player_line(line);
		free(line);
		if (player.name[0] != '\0')
			*valid = 1;
	}
	return (player);
}
