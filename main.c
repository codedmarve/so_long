#include "so_long.h"

// int	main(void)
// {
// 	void	*mlx;

// 	mlx = mlx_init();
// }

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 520, 320, "Hello world!");
	mlx_loop(mlx);
}