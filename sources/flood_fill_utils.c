/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 22:13:00 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 23:12:16 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// initialize queue with given capacity and allocate memory
void	ft_queue_init(t_queue *q, int capacity)
{
	q->data = malloc(sizeof(t_character) * capacity);
	if (!q->data)
		return ;
	q->front = 0;
	q->rear = 0;
	q->capacity = capacity;
}

// dynamically add an element to the end of the queue
void	ft_queue_push(t_queue *q, t_character c)
{
	t_character	*new_data;
	int			i;

	i = 0;
	if (q->rear >= q->capacity)
	{
		q->capacity *= 2;
		new_data = malloc(sizeof(t_character) * q->capacity);
		if (!new_data)
			return ;
		while (i < q->rear)
		{
			new_data[i] = q->data[i];
			i++;
		}
		free(q->data);
		q->data = new_data;
	}
	q->data[q->rear++] = c;
}

// remove and return the front element from the queue
t_character	ft_queue_pop(t_queue *q)
{
	return (q->data[q->front++]);
}

// check if the queue is empty (front and rear indices are equal)
int	ft_is_queue_empty(t_queue *q)
{
	return (q->front == q->rear);
}

// remove player and collectibles when stepped on, then trigger flood fill
void	ft_clear_and_flood(t_game *game, t_map size, t_character charpos)
{
	if (game->map.map[charpos.y_char][charpos.x_char] == 'P')
		game->map.map[charpos.y_char][charpos.x_char] = '0';
	if (game->map.map[charpos.y_char][charpos.x_char] == 'C')
		game->map.map[charpos.y_char][charpos.x_char] = '0';
	ft_flood_fill(game, size, charpos, game->map.map[charpos.y_char]
	[charpos.x_char]);
}
