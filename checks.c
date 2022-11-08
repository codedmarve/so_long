/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 10:29:13 by moduwole          #+#    #+#             */
/*   Updated: 2022/10/27 10:29:13 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map(char *argv, t_frame *game)
{
	char	*line;
	int		i;
	int		fd;

	i = 0;
	game->map = (char **)ft_calloc(game->rows + 1, sizeof(char *));
	if (!game->map)
		return (32 - ft_printf("Error: memory allocation failed\n"));
	game->map[game->rows] = NULL;
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	game->map[i] = ft_strtrim(line, "\n");
	free(line);
	while (game->map[i])
	{
		i++;
		line = get_next_line(fd);
		game->map[i] = ft_strtrim(line, "\n");
		free(line);
	}
	game->cols = ft_strlen(game->map[0]) - 1;
	close(fd);
	if (ft_ispec(game) != 1 || game->gate != 1 || game->herbs < 1)
		return (40 - ft_printf("Error: check that P == 1, E == 1, C > 0\n"));
	return (1);
}

int	iswall(char *str, char c)
{
	static int	n;
	int			i;

	if (c == 'l' && (int)ft_strlen(str) != n - 2)
	{
		free(str);
		return (42 - ft_printf("Error: unequal row length, check last row\n"));
	}
	n = ft_strlen(str);
	i = ft_strlen(str) - 1;
	if ((str[i] != '\n' || i < 4) && c != 'l')
	{
		free(str);
		return (41 - ft_printf("Error: wrong map format, check first row\n"));
	}
	if (c != 'l')
		i -= 2;
	while (i >= 0 && str[i] == '1')
		i--;
	free(str);
	if (i < 0)
		return (n);
	return (47 - ft_printf("Error: non-wall character in first or last row\n"));
}

int	ismiddle(char *str, char *nxt, int cols)
{
	static int	i = 1;

	i++;
	if ((int)ft_strlen(str) == cols + 2 && str[cols + 1] == '\n'
		&& str[cols - 1] == '1' && str[0] == '1')
	{
		cols -= 1;
		while (cols >= 0 && (str[cols] == '1' || str[cols] == '0'
				|| str[cols] == 'P' || str[cols] == 'C' || str[cols] == 'E'))
			cols--;
		if (cols != -1)
		{
			free(str);
			free(nxt);
			ft_printf("Error: non-O1CEP character, check row %i\n", i);
			return (0);
		}
		free(str);
		return (1);
	}
	free(str);
	free(nxt);
	ft_printf("Error: row %i must start and end with 1 with equal length \n", i);
	return (0);
}

int	isvalid(int fd, t_frame *game)
{
	char	*line;
	char	*nxt;

	line = get_next_line(fd);
	game->cols = iswall(line, ' ') - 2;
	if (!(game->cols + 2))
		return (0);
	line = get_next_line(fd);
	game->rows = 2;
	nxt = get_next_line(fd);
	while (nxt)
	{
		game->rows++;
		if (!ismiddle(line, nxt, game->cols))
			return (0);
		line = nxt;
		nxt = get_next_line(fd);
	}
	if (!iswall(line, 'l'))
		return (0);
	if (game->rows < 3 || game->rows == game->cols)
		return (44 - ft_printf("Error: rows must != cols & both must be > 2\n"));
	return (game->rows);
}

t_frame	*checker(char *argv)
{
	t_frame	*game;
	char	*s;
	int		fd;

	s = ft_strchr(argv, '.');
	fd = open(argv, O_RDONLY);
	game = (t_frame *)ft_calloc(1, sizeof(t_frame));
	if (fd < 0 || !s || !game || ft_strlen(s) != 4 || ft_strncmp(s, ".ber", 4))
	{
		ft_printf("Error: check map file\n");
		return (ft_clear_game(game), NULL);
	}
	init_game(game);
	if (!isvalid(fd, game))
		return (ft_clear_game(game), close(fd), NULL);
	close(fd);
	if (!load_map(argv, game) || !ispath(game))
		return (ft_clear_game(game), NULL);
	return (game);
}
