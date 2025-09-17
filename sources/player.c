/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 21:12:15 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 22:22:22 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// continuously prompt the player until a valid name is entered
void	ft_prompt_player_name(t_game *game)
{
	char	input[NICK_NAME_LEN + 1];
	int		bytes_read;
	int		valid_name;

	valid_name = 0;
	while (!valid_name)
	{
		ft_print_name_prompt();
		bytes_read = read(0, input, sizeof(input) - 1);
		valid_name = ft_handle_player_input(game, input, bytes_read);
	}
}

// save current player's data to the main file
void	ft_save_player_data(t_game *game)
{
	int		count;
	char	**lines;

	lines = ft_read_player_data(&count);
	if (ft_save_player_data_temp(game, lines, count) != 0)
	{
		ft_printf("Error: Could not create temporary file\n");
		return ;
	}
	if (rename("./player_data_temp.txt", PLAYER_DATA_FILE) != 0)
	{
		ft_printf("Error: Could not update player data file\n");
	}
	else
		ft_printf("Game results saved for %s\n", game->player_data.name);
}

// check if the line starts with the given name followed by a '|'
static int	ft_line_starts_with_name(const char *line, const char *name)
{
	char	*pipe_pos;
	size_t	name_len;
	char	*existing_name;
	int		result;

	result = 0;
	pipe_pos = ft_strchr(line, '|');
	if (!pipe_pos)
		return (0);
	if (pipe_pos)
	{
		name_len = pipe_pos - line;
		existing_name = ft_substr(line, 0, name_len);
		if (existing_name && ft_strncmp(existing_name,
				name, ft_strlen(name)) == 0)
			result = 1;
		free(existing_name);
	}
	return (result);
}

// return 1 if the player name exists in the data file, 0 otherwise.
int	ft_does_player_exist(const char *name)
{
	int		fd;
	char	*line;
	int		result;

	fd = open(PLAYER_DATA_FILE, O_RDONLY);
	if (fd < 0)
		return (0);
	result = 0;
	line = get_next_line(fd);
	while (line && !result)
	{
		result = ft_line_starts_with_name(line, name);
		free(line);
		if (!result)
			line = get_next_line(fd);
	}
	close(fd);
	return (result);
}

// display a formatted prompt asking the player to enter their name
void	ft_print_name_prompt(void)
{
	ft_printf("\n");
	ft_printf("╔══════════════════════════════════════════════════════════════╗\
		\n");
	ft_printf("║                     ENTER YOUR NAME                          ║\
		\n");
	ft_printf("║  (3-25 characters, letters and numbers, must be unique)      ║\
		\n");
	ft_printf("║                                                              ║\
		\n");
	ft_printf("║  Type 'reset' to clear all player data                       ║\
		\n");
	ft_printf("╚══════════════════════════════════════════════════════════════╝\
		\n\n");
	ft_printf("--->> ");
}
