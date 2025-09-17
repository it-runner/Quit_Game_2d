/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:52:59 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 20:28:22 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// verify that all required XPM images were loaded successfully
int	ft_check_xpm_images(t_game *game)
{
	if (!game->hero.img || !game->item.img || !game->exit.img
		|| !game->floor.img || !game->wall.img)
	{
		ft_free_images(game);
		mlx_destroy_window(game->show.mlx_ptr, game->show.win_ptr);
		mlx_destroy_display(game->show.mlx_ptr);
		free(game->show.mlx_ptr);
		ft_error(game, "Could not load xpm files");
		return (0);
	}
	return (1);
}

// load pixel data addresses for all game textures
int	ft_set_xpm_addr(t_game *game)
{
	game->hero.addr = mlx_get_data_addr(game->hero.img,
			&game->hero.bits_per_pixel, &game->hero.size_line,
			&game->hero.endian);
	game->item.addr = mlx_get_data_addr(game->item.img,
			&game->item.bits_per_pixel, &game->item.size_line,
			&game->item.endian);
	game->exit.addr = mlx_get_data_addr(game->exit.img,
			&game->exit.bits_per_pixel, &game->exit.size_line,
			&game->exit.endian);
	game->floor.addr = mlx_get_data_addr(game->floor.img,
			&game->floor.bits_per_pixel, &game->floor.size_line,
			&game->floor.endian);
	game->wall.addr = mlx_get_data_addr(game->wall.img,
			&game->wall.bits_per_pixel, &game->wall.size_line,
			&game->wall.endian);
	return (1);
}

// load all XPM textures into the game
t_game	*ft_load_xpm_textures(t_game *game)
{
	game->hero.img = mlx_xpm_file_to_image(game->show.mlx_ptr,
			"graphics/P_hero.xpm", &game->hero.bits_per_pixel,
			&game->hero.size_line);
	game->item.img = mlx_xpm_file_to_image(game->show.mlx_ptr,
			"graphics/C_item.xpm", &game->item.bits_per_pixel,
			&game->item.size_line);
	game->exit.img = mlx_xpm_file_to_image(game->show.mlx_ptr,
			"graphics/E_exit_closed.xpm", &game->exit.bits_per_pixel,
			&game->exit.size_line);
	game->floor.img = mlx_xpm_file_to_image(game->show.mlx_ptr,
			"graphics/0_floor.xpm", &game->floor.bits_per_pixel,
			&game->floor.size_line);
	game->wall.img = mlx_xpm_file_to_image(game->show.mlx_ptr,
			"graphics/1_wall.xpm", &game->wall.bits_per_pixel,
			&game->wall.size_line);
	if (!ft_check_xpm_images(game))
		return (0);
	if (!ft_set_xpm_addr(game))
	{
		ft_error(game, "Could not find xpm address");
		return (0);
	}
	return (game);
}

// loads side images on the left and right side of the map
int	ft_load_side_images(t_game *game)
{
	game->side_img_left = mlx_xpm_file_to_image(game->show.mlx_ptr,
			"graphics/img/sg1.xpm", &game->side_img_width,
			&game->side_img_height);
	game->side_img_right = mlx_xpm_file_to_image(game->show.mlx_ptr,
			"graphics/img/sg2.xpm", &game->side_img_width,
			&game->side_img_height);
	if (!game->side_img_left || !game->side_img_right)
	{
		ft_printf("Error: Could not load side images\n");
		if (game->side_img_left)
			mlx_destroy_image(game->show.mlx_ptr, game->side_img_left);
		if (game->side_img_right)
			mlx_destroy_image(game->show.mlx_ptr, game->side_img_right);
		return (0);
	}
	return (1);
}
