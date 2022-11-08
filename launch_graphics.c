/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 15:29:20 by moduwole          #+#    #+#             */
/*   Updated: 2022/11/03 15:29:20 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map(t_frame *game)
{
	int	row;
	int	col;

	row = -1;
	while (++row < game->rows)
	{
		col = -1;
		while (++col < game->cols)
		{
			if (game->map[row][col] == '1')
				ft_put_img(game, game->wall, row, col);
			else if (game->map[row][col] == '0')
				ft_put_img(game, game->space, row, col);
			else if (game->map[row][col] == 'C')
				ft_put_img(game, game->herb, row, col);
			else if (game->map[row][col] == 'P')
				ft_put_img(game, game->wiz_img, row, col);
			else if (game->map[row][col] == 'E')
				ft_put_img(game, game->door[0], row, col);
		}
	}
}

void	load_wall_door(t_frame *game)
{
	game->wall = mlx_xpm_file_to_image(game->mlx, \
			"./imgs/xpm/wall.xpm", &game->img_wh, &game->img_wh);
	game->space = mlx_xpm_file_to_image(game->mlx, \
			"./imgs/xpm/space.xpm", &game->img_wh, &game->img_wh);
	game->door[0] = mlx_xpm_file_to_image(game->mlx, \
			"./imgs/xpm/door1.xpm", &game->img_wh, &game->img_wh);
	game->door[1] = mlx_xpm_file_to_image(game->mlx, \
			"./imgs/xpm/door2.xpm", &game->img_wh, &game->img_wh);
}

void	load_wiz_herbs(t_frame *game)
{
	game->herb = mlx_xpm_file_to_image(game->mlx, \
			"./imgs/xpm/herb.xpm", &game->img_wh, &game->img_wh);
	game->wiz[0] = mlx_xpm_file_to_image(game->mlx, \
			"./imgs/xpm/wiz_right.xpm", &game->img_wh, &game->img_wh);
	game->wiz[1] = mlx_xpm_file_to_image(game->mlx, \
			"./imgs/xpm/wiz_left.xpm", &game->img_wh, &game->img_wh);
	if (game->player[1] <= (game->cols / 2))
	{
		game->wiz_img = game->wiz[0];
		game->direction = 'R';
	}
	else if (game->player[1] > (game->cols / 2))
	{
		game->wiz_img = game->wiz[1];
		game->direction = 'L';
	}
}

void	launch_graphics(t_frame *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SIZE * game->cols, \
			SIZE * game->rows, "WIZARD OF OZ");
	game->last_pos = '0';
	load_wiz_herbs(game);
	load_wall_door(game);
	init_map(game);
	ft_printf("Steps: %i\tHerbs: %i/%i\n", game->steps, game->herbs, \
			game->collected);
	mlx_hook(game->win, 2, 1L << 0, ft_key_hook, game);
	mlx_hook(game->win, 17, 1L << 2, free_destroy, game);
	mlx_loop(game->mlx);
}
