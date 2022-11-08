/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 07:42:03 by moduwole          #+#    #+#             */
/*   Updated: 2022/11/01 07:42:03 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_ispec(t_frame *game)
{
	int	p;
	int	row;
	int	col;

	row = -1;
	p = 0;
	while (game->map[++row])
	{
		col = -1;
		while (game->map[row][++col])
		{
			if (game->map[row][col] == 'P')
			{
				p++;
				game->player[0] = row;
				game->player[1] = col;
			}
			else if (game->map[row][col] == 'E')
				game->gate++;
			else if (game->map[row][col] == 'C')
				game->herbs++;
		}
	}
	return (p);
}

int	check_path(t_frame *game, int **marked)
{
	int	row;
	int	col;
	int	exit;
	int	herbs;

	row = -1;
	exit = 0;
	herbs = 0;
	while (game->map[++row])
	{
		col = -1;
		while (game->map[row][++col])
		{
			if ((game->map[row][col] == 'E') && (marked[row][col]))
					exit++;
			if ((game->map[row][col] == 'C') && (marked[row][col]))
					herbs++;
		}
	}
	if ((exit + herbs) == (game->herbs + 1))
		return (1);
	return (48 - ft_printf("Error: check map paths to Collectibles and Exit\n"));
}

void	mark_path(t_frame *game, int row, int col, int **marked)
{
	if ((row < 0 || row >= game->rows) && (col < 0 || col >= game->cols))
		return ;
	if (game->map[row][col] != '1' && marked[row][col] != 1)
	{
		marked[row][col] = 1;
		mark_path(game, row, col + 1, marked);
		mark_path(game, row, col - 1, marked);
		mark_path(game, row + 1, col, marked);
		mark_path(game, row - 1, col, marked);
	}
}

int	ispath(t_frame *game)
{
	int		**marked;
	int		valid;
	int		i;

	i = 0;
	valid = 1;
	marked = (int **)ft_calloc(game->rows, sizeof(int *));
	while (i < game->rows)
	{
		marked[i] = (int *)ft_calloc(game->cols, sizeof(int));
		i++;
	}
	mark_path(game, game->player[0], game->player[1], marked);
	valid = check_path(game, marked);
	while (--i >= 0)
		free(marked[i]);
	free(marked);
	return (valid);
}
