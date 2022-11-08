/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:05:52 by moduwole          #+#    #+#             */
/*   Updated: 2022/11/02 15:05:52 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_frame *game)
{
	game->rows = 0;
	game->cols = 0;
	game->herbs = 0;
	game->gate = 0;
	game->steps = 0;
	game->collected = 0;
}

void	ft_put_img(t_frame *game, void *img, int row, int col)
{
	mlx_put_image_to_window(game->mlx, game->win, \
			img, SIZE * col, SIZE * row);
}

int	free_destroy(t_frame *game)
{
	mlx_destroy_image(game->mlx, game->wall);
	mlx_destroy_image(game->mlx, game->space);
	mlx_destroy_image(game->mlx, game->wiz[0]);
	mlx_destroy_image(game->mlx, game->wiz[1]);
	mlx_destroy_image(game->mlx, game->herb);
	mlx_destroy_image(game->mlx, game->door[0]);
	mlx_destroy_image(game->mlx, game->door[1]);
	mlx_loop_end(game->mlx);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	ft_clear_game(game);
	exit(0);
}

void	ft_clear_game(t_frame *game)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
	free(game);
}

void	change_position(t_frame *game, int row, int col)
{
	if (game->last_pos == '0')
		ft_put_img(game, game->space, game->player[0], game->player[1]);
	else if (game->last_pos == 'E')
		ft_put_img(game, game->door[0], game->player[0], game->player[1]);
	game->map[game->player[0]][game->player[1]] = game->last_pos;
	ft_put_img(game, game->wiz_img, row, col);
	game->last_pos = game->map[row][col];
	game->player[0] = row;
	game->player[1] = col;
	game->steps++;
	ft_printf("steps: %i\tHerbs: %i/%i\n", game->steps, game->collected, \
			game->herbs);
}
