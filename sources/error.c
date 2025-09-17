/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: so_long <so_long@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:58:14 by so_long           #+#    #+#             */
/*   Updated: 2025/09/16 11:12:43 by so_long          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// print nomap error message to the console and frees the game
int	ft_nomap_error(t_game *game, char *err_msg)
{
	ft_printf("\n\t  Error  \n\n");
	ft_printf("%s\n", err_msg);
	ft_printf("\n\n\t\t===== No pain, no game =====\n\n");
	free(game);
	return (0);
}

// print error message to the console, destroys the map and frees the game
int	ft_error(t_game *game, char *err_msg)
{
	ft_printf("\n\t  Error  \n\n");
	ft_printf("%s\n", err_msg);
	ft_printf("\n\n\t\t===== No pain, no game =====\n\n");
	ft_free_map(game);
	free(game);
	return (0);
}
