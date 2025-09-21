/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_line_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 11:50:21 by so_long           #+#    #+#             */
/*   Updated: 2025/09/21 11:55:32 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// extract and return a duplicate of the player's name from the line  
static char	*extract_existing_name(char *line)
{
	char	*sep;
	char	tmp;
	char	*existing_name;

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
	return (existing_name);
}

// write either the updated player entry or the original line to the file
static int	write_line_or_player(int fd, t_game *game,
		char *line, char *existing_name)
{
	size_t	len;
	int		player_found;

	player_found = 0;
	len = ft_strlen(line);
	if (existing_name && ft_strncmp(existing_name, game->player_data.name,
			ft_strlen(game->player_data.name)) == 0)
	{
		if (len > 0 && line[len - 1] != '\n')
			write(fd, "\n", 1);
		ft_write_player_entry(fd, &game->player_data);
		player_found = 1;
	}
	else
	{
		write(fd, line, len);
		if (len > 0 && line[len - 1] != '\n')
			write(fd, "\n", 1);
	}
	return (player_found);
}

// process a single line and write it or updated player entry to the file
static int	ft_process_line(int fd, t_game *game, char *line)
{
	char	*existing_name;
	int		player_found;

	existing_name = extract_existing_name(line);
	player_found = write_line_or_player(fd, game, line, existing_name);
	free(existing_name);
	return (player_found);
}

// process all lines, replace matching player entry and write them to file
int	ft_process_lines_and_write(int fd, t_game *game, char **lines,
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
