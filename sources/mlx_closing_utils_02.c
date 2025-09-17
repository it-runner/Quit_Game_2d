/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_closing_utils_02.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:11:31 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 11:19:02 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// clean up the game resources and optionally exit the program
void	ft_cleanup_game(t_game *game, int should_load_next)
{
	if (game->map.map)
	{
		ft_free_map(game);
		game->map.map = NULL;
	}
	if (!should_load_next)
	{
		if (game->level_list)
			free(game->level_list);
		free(game);
		exit(EXIT_SUCCESS);
	}
}

// free all allocated memory for the game map
void	ft_free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.col_size)
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
}

// free all loaded images from memory
void	ft_free_images(t_game *game)
{
	if (game->hero.img)
		mlx_destroy_image(game->show.mlx_ptr, game->hero.img);
	if (game->item.img)
		mlx_destroy_image(game->show.mlx_ptr, game->item.img);
	if (game->exit.img)
		mlx_destroy_image(game->show.mlx_ptr, game->exit.img);
	if (game->floor.img)
		mlx_destroy_image(game->show.mlx_ptr, game->floor.img);
	if (game->wall.img)
		mlx_destroy_image(game->show.mlx_ptr, game->wall.img);
	if (game->panel.img)
		mlx_destroy_image(game->show.mlx_ptr, game->panel.img);
	if (game->side_img_left)
		mlx_destroy_image(game->show.mlx_ptr, game->side_img_left);
	if (game->side_img_right)
		mlx_destroy_image(game->show.mlx_ptr, game->side_img_right);
}

// safely free MLX resources and destroy window
void	ft_free_mlx_resources(t_game *game)
{
	if (game->show.mlx_ptr)
	{
		ft_free_images(game);
		if (game->show.win_ptr)
			mlx_destroy_window(game->show.mlx_ptr, game->show.win_ptr);
		mlx_destroy_display(game->show.mlx_ptr);
		free(game->show.mlx_ptr);
		game->show.mlx_ptr = NULL;
		game->show.win_ptr = NULL;
	}
}
