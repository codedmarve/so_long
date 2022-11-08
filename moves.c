/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 17:23:44 by moduwole          #+#    #+#             */
/*   Updated: 2022/11/06 17:23:44 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_exit(t_frame *game, int row, int col)
{
	if (game->herbs != game->collected)
	{
		ft_printf("You must collect all herbs\n");
		change_position(game, row, col);
	}
	else
	{
		ft_printf("YOU WIN!!!\n");
		free_destroy(game);
	}
}

void	check_gate(t_frame *game)
{
	int	row;
	int	col;

	row = -1;
	if (game->herbs == game->collected)
	{
		while (++row < game->rows)
		{
			col = -1;
			while (++col < game->cols)
				if (game->map[row][col] == 'E')
					ft_put_img(game, game->door[1], row, col);
		}
	}
	else
		return ;
}

void	move_wiz(t_frame *game, int row, int col)
{
	if (game->map[row][col] == '1')
		return ;
	else if (game->map[row][col] == '0' || game->map[row][col] == 'C')
	{
		if (game->map[row][col] == 'C')
		{
			game->map[row][col] = '0';
			game->collected++;
			check_gate(game);
		}
		change_position(game, row, col);
	}
	else if (game->map[row][col] == 'E')
		is_exit(game, row, col);
}

void	key_hook2(int keycode, t_frame *game)
{
	if (keycode == KEY_D)
	{
		if (game->direction != 'R')
		{
			game->wiz_img = game->wiz[0];
			ft_put_img(game, game->wiz_img, game->player[0], game->player[1]);
			game->direction = 'R';
		}
		else
			move_wiz(game, game->player[0], game->player[1] + 1);
	}
	else if (keycode == KEY_A)
	{
		if (game->direction != 'L')
		{
			game->wiz_img = game->wiz[1];
			ft_put_img(game, game->wiz_img, game->player[0], game->player[1]);
			game->direction = 'L';
		}
		else
			move_wiz(game, game->player[0], game->player[1] - 1);
	}
}

int	ft_key_hook(int keycode, t_frame *game)
{
	if (keycode == ESC_KEY)
		free_destroy(game);
	else if (keycode == KEY_D || keycode == KEY_A)
		key_hook2(keycode, game);
	else if (keycode == KEY_W)
		move_wiz(game, game->player[0] - 1, game->player[1]);
	else if (keycode == KEY_S)
		move_wiz(game, game->player[0] + 1, game->player[1]);
	return (0);
}
