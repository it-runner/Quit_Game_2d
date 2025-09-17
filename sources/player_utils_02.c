/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:50:43 by so_long           #+#    #+#             */
/*   Updated: 2025/09/17 10:47:09 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// count the number of lines in a file
static int	count_lines_in_file(const char *filename)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		count++;
		free(line);
	}
	if (close(fd) < 0)
		return (-1);
	return (count);
}

// helper function to read lines from a file
static char	**ft_read_lines_from_fd(int fd, int total_lines, int *count)
{
	char	**lines;
	char	*line;

	lines = malloc(sizeof(char *) * (total_lines + 1));
	if (!lines)
		return (NULL);
	*count = 0;
	line = get_next_line(fd);
	while (line != NULL && *count < total_lines)
	{
		lines[(*count)++] = line;
		line = get_next_line(fd);
	}
	if (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd);
		}
	}
	lines[*count] = NULL;
	return (lines);
}

// read all player data from a file into array of strings
char	**ft_read_player_data(int *count)
{
	int		total_lines;
	char	**lines;
	int		fd;

	total_lines = count_lines_in_file(PLAYER_DATA_FILE);
	if (total_lines < 0)
		return (NULL);
	fd = open(PLAYER_DATA_FILE, O_RDONLY);
	if (fd < 0)
		return (NULL);
	lines = ft_read_lines_from_fd(fd, total_lines, count);
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	if (close(fd) < 0)
		ft_printf("Warning: close() failed for player data file\n");
	return (lines);
}

// check if the player name is valid and not already taken
int	ft_is_valid_player_name(const char *name)
{
	if (ft_strlen(name) < 3 || ft_strlen(name) > NICK_NAME_LEN)
		return (0);
	if (!ft_str_is_alnum(name))
		return (0);
	if (ft_does_player_exist(name))
	{
		ft_printf("\n❌ Name '%s' already exists! \
			Please choose a different name.\n\n", name);
		return (0);
	}
	return (1);
}

// check if a string contains only letters and numbers
int	ft_str_is_alnum(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
