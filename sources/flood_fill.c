/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 07:19:59 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 23:04:24 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// process a map position, marking it as visited and counting items/exits
static int	ft_process_position(t_game *game, t_character pos, char filler)
{
	char	current;

	current = game->map.map[pos.y_char][pos.x_char];
	if (current != filler && current != 'C' && current != 'E')
		return (0);
	if (current == 'C')
		game->map.item_count++;
	if (current == 'E')
		game->map.exit_count++;
	game->map.map[pos.y_char][pos.x_char] = 'F';
	return (1);
}

// push the four adjacent positions (up, down, left, right) into the queue
static void	ft_enqueue_neighbors(t_queue *q, t_character pos)
{
	ft_queue_push(q, (t_character){.x_char = pos.x_char - 1,
		.y_char = pos.y_char, .move_count = 0});
	ft_queue_push(q, (t_character){.x_char = pos.x_char + 1,
		.y_char = pos.y_char, .move_count = 0});
	ft_queue_push(q, (t_character){.x_char = pos.x_char,
		.y_char = pos.y_char - 1, .move_count = 0});
	ft_queue_push(q, (t_character){.x_char = pos.x_char,
		.y_char = pos.y_char + 1, .move_count = 0});
}

// flood-fill algorithm to explore the map
void	ft_flood_fill(t_game *game, t_map size, t_character start, char filler)
{
	t_queue		q;
	t_character	pos;

	ft_queue_init(&q, 1024);
	ft_queue_push(&q, start);
	while (!ft_is_queue_empty(&q))
	{
		pos = ft_queue_pop(&q);
		if (pos.y_char < 0 || pos.y_char >= size.y_map
			|| pos.x_char < 0 || pos.x_char >= size.x_map)
			continue ;
		if (ft_process_position(game, pos, filler))
			ft_enqueue_neighbors(&q, pos);
	}
	free(q.data);
}

// check if all items and the exit are reachable on the map
static int	ft_access_error(t_game *game, int item_no, int exit_no)
{
	if (item_no != game->map.item_count)
	{
		ft_error(game, "No access to collectives");
		return (0);
	}
	if (exit_no != game->map.exit_count)
	{
		ft_error(game, "Mission Impossible. No access to exit");
		return (0);
	}
	return (1);
}

// flood map and check access to items/exit
int	ft_flood_access_check(t_game *game)
{
	t_character	charpos;
	t_map		size;
	int			item_num;
	int			exit_num;

	item_num = game->map.item_count;
	exit_num = game->map.exit_count;
	game->map.item_count = 0;
	game->map.exit_count = 0;
	charpos = (t_character){.x_char = game->player.x_char,
		.y_char = game->player.y_char};
	size = (t_map){.x_map = game->map.line_size, .y_map = game->map.col_size};
	ft_clear_and_flood(game, size, charpos);
	if (!ft_access_error(game, item_num, exit_num))
		return (0);
	return (1);
}
