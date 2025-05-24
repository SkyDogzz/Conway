#include "../include/conway.h"

void	exit_with_error(const char *err, const int code)
{
	fprintf(stderr, "%s\n", err);
	exit(code);
}

int	main(int argc, char **argv)
{
	t_wrap	wrap;

	if (argc <= 1 || argc >= 4)
		exit_with_error("Incorrect usage", 1);
	if (argc == 2)
	{
		if (!read_from_file(&wrap.map, argv[1]))
			exit(1);
	}
	else
{
		printf("Still to implement\n");
		exit(0);
	}
	wrap.mlx_ptr = mlx_init();
	wrap.mlx_win = mlx_new_window(wrap.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Window");
	mlx_hook(wrap.mlx_win, 17, 0, &full_quit, &wrap);
	mlx_hook(wrap.mlx_win, KeyPress,
		  KeyPressMask, &handle_keypress, &wrap);
	mlx_hook(wrap.mlx_win, KeyRelease,
		  KeyReleaseMask, &handle_keyrelease, &wrap);
	wrap.data.img = mlx_new_image(wrap.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	wrap.data.addr = mlx_get_data_addr(wrap.data.img, &wrap.data.bits_per_pixel, &wrap.data.line_length,
									&wrap.data.endian);
	draw_grid(&wrap);
	mlx_put_image_to_window(wrap.mlx_ptr, wrap.mlx_win, wrap.data.img, 0, 0);
	mlx_loop(wrap.mlx_ptr);
}
