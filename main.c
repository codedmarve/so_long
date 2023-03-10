/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 07:42:29 by moduwole          #+#    #+#             */
/*   Updated: 2022/11/07 11:27:20 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_frame	*game;

	if (argc != 2)
		return (29 - ft_printf("Error: argument must be one\n"));
	game = checker(argv[1]);
	if (game)
		launch_graphics(game);
	return (0);
}
