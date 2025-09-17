/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:40:24 by so_long           #+#    #+#             */
/*   Updated: 2025/08/20 13:17:18 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 	
	read chunk to buffer
	0 = EOF or error
	1 = data read to file and process can be continued 
*/
static int	read_buf(int fd, char **str, char *buf)
{
	ssize_t	bytes_read;

	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read == 0 && (**str))
		return (0);
	if (bytes_read <= 0)
	{
		free(*str);
		*str = NULL;
		return (0);
	}
	buf[bytes_read] = '\0';
	return (1);
}

static char	*alloc_str(char *old_chunk_str, char *buf, ssize_t start,
				ssize_t len)
{
	ssize_t	i;
	char	*new_str;

	new_str = (char *)malloc(sizeof(char)
			* (str_len(old_chunk_str) + len + 1));
	if (!new_str)
	{
		free(old_chunk_str);
		return (NULL);
	}
	i = 0;
	while (old_chunk_str[i])
	{
		new_str[i] = old_chunk_str[i];
		i++;
	}
	free(old_chunk_str);
	new_str[i + len] = '\0';
	while (len)
	{
		len--;
		new_str[i + len] = buf[start + len];
	}
	return (new_str);
}

/*	used when no newline found
	0 = error, 1 = success */
static int	add_chunk(char **chunk_str, char *buf, ssize_t *line_start,
		ssize_t *line_len)
{
	*chunk_str = alloc_str(*chunk_str, buf, *line_start,
			BUFFER_SIZE - *line_start);
	if (!*chunk_str)
		return (0);
	*line_start = 0;
	*line_len = 0;
	return (1);
}

static char	*complete_line(char *line, char *buf, ssize_t *line_start,
		ssize_t *line_len)
{
	line = alloc_str(line, buf, *line_start, *line_len);
	*line_start += *line_len;
	*line_len = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	char			*full_line;
	static char		buf[BUFFER_SIZE + 1];
	static ssize_t	line_start = 0;
	static ssize_t	len = 0;

	if (fd < 0 || BUFFER_SIZE <= 0 || !create_empty_line(&full_line))
		return (NULL);
	while (!len)
	{
		if (!line_start && !read_buf(fd, &full_line, buf))
			return (full_line);
		len = find_newline(buf, line_start) - line_start;
		if (len > 0)
			return (complete_line(full_line, buf, &line_start, &len));
		else if (!add_chunk(&full_line, buf, &line_start, &len))
			return (NULL);
	}
	return (NULL);
}
