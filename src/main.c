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
	wrap.mlx_win = mlx_new_window(wrap.mlx_ptr, 600, 400, "Window");

	mlx_hook(wrap.mlx_win, 17, 0, &full_quit, &wrap);
	mlx_hook(wrap.mlx_win, KeyPress,
		KeyPressMask, &handle_keypress, &wrap);
	mlx_hook(wrap.mlx_win, KeyRelease,
		KeyReleaseMask, &handle_keyrelease, &wrap);
	mlx_loop(wrap.mlx_ptr);
}
