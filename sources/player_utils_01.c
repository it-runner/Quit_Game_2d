/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:34:11 by so_long           #+#    #+#             */
/*   Updated: 2025/09/17 10:46:28 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_write_player_entry(int fd, t_player_data *player)
{
	int			i;
	int			j;
	long long	n;
	char		rev[32];
	char		numbuf[32];

	write(fd, player->name, ft_strlen(player->name));
	write(fd, "|", 1);
	n = player->game_time_ms;
	i = 0;
	if (n == 0)
		numbuf[i++] = '0';
	else
	{
		j = 0;
		while (n > 0)
		{
			rev[j++] = '0' + (n % 10);
			n /= 10;
		}
		while (j > 0)
			numbuf[i++] = rev[--j];
	}
	numbuf[i++] = '\n';
	write(fd, numbuf, i);
}

// process a single line and write it or updated player entry to the file
static int	ft_process_line(int fd, t_game *game, char *line)
{
	char	*sep;
	char	*existing_name;
	char	tmp;
	int		player_found;

	sep = ft_strchr(line, '|');
	if (sep)
	{
		tmp = *sep;
		*sep = '\0';
		existing_name = ft_strdup(line);
		*sep = tmp;
	}
	else
		existing_name = ft_strdup(line);
	player_found = 0;
	if (existing_name && ft_strncmp(existing_name, game->player_data.name,
			ft_strlen(game->player_data.name)) == 0)
	{
		ft_write_player_entry(fd, &game->player_data);
		player_found = 1;
	}
	else
		write(fd, line, ft_strlen(line));
	return (free(existing_name), player_found);
}

// process all lines, replace matching player entry and write them to file
static int	ft_process_lines_and_write(int fd, t_game *game, char **lines,
	int count)
{
	int		i;
	int		player_found;

	i = 0;
	player_found = 0;
	while (i < count)
	{
		player_found |= ft_process_line(fd, game, lines[i]);
		free(lines[i]);
		i++;
	}
	return (player_found);
}

// save game player data to a temporary file
int	ft_save_player_data_temp(t_game *game, char **lines, int count)
{
	int	fd;
	int	player_found;

	fd = open("./player_data_temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	player_found = ft_process_lines_and_write(fd, game, lines, count);
	if (!player_found)
		ft_write_player_entry(fd, &game->player_data);
	free(lines);
	close(fd);
	return (0);
}

// process player input, handle "reset", validate name, or assign default
int	ft_handle_player_input(t_game *game, char *input, int bytes_read)
{
	if (bytes_read > 0)
	{
		input[bytes_read - 1] = '\0';
		if (input[0] == '\0')
		{
			ft_set_default_player_name(game);
			return (1);
		}
		if (ft_strncmp(input, "reset", 5) == 0)
		{
			ft_reset_player_file();
			ft_printf("Player data has been reset.\n\n");
			return (0);
		}
		if (ft_is_valid_player_name(input))
		{
			ft_strlcpy(game->player_data.name, input,
				sizeof(game->player_data.name));
			return (1);
		}
	}
	else
		return (ft_set_default_player_name(game), 1);
	return (0);
}
