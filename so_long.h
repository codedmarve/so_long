/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:17:05 by moduwole          #+#    #+#             */
/*   Updated: 2022/11/02 22:17:05 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./minilibx-linux/mlx.h"
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef SIZE
#  define SIZE 80
#  define ESC_KEY 65307
#  define KEY_W 119
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_A 97
# endif

typedef struct s_frame
{
	char	**map;
	void	*mlx;
	void	*win;
	void	*wall;
	void	*space;
	void	*wiz_img;
	void	*wiz[2];
	char	direction;
	char	last_pos;
	void	*herb;
	void	*door[2];
	int		player[2];
	int		img_wh;
	int		steps;
	int		rows;
	int		cols;
	int		herbs;
	int		gate;
	int		collected;
}			t_frame;

t_frame		*checker(char *argv);
int			ispath(t_frame *game);
int			ft_ispec(t_frame *game);
void		init_map(t_frame *game);
void		init_game(t_frame *game);
void		ft_clear_game(t_frame *game);
int			free_destroy(t_frame *game);
void		launch_graphics(t_frame *game);
int			load_map(char *argv, t_frame *game);
int			ft_key_hook(int keycode, t_frame *game);
void		change_position(t_frame *game, int row, int col);
void		ft_put_img(t_frame *game, void *img, int row, int col);

#endif