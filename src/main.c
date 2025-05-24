#include "../include/conway.h"

void exit_with_error(const char *err, const int code) {
	fprintf(stderr, "%s\n", err);
	exit(code);
}

int auto_loop_hook(t_wrap *wrap) {
	static int frame = 0;
	static int prev_speed = 0;

	if (!wrap->auto_mode)
		return (0);

	if (wrap->auto_speed != prev_speed) {
		frame = 0;
		prev_speed = wrap->auto_speed;
	}

	if (++frame < wrap->auto_speed)
		return (0);

	frame = 0;
	clear_image(&wrap->data);
	next_generation(&wrap->map);
	draw_grid(wrap);
	update_img(wrap);
	return (0);
}

int main(int argc, char **argv) {
	t_wrap wrap;

	if (argc <= 1 || argc >= 4)
		exit_with_error("Incorrect usage", 1);
	if (argc == 2) {
		if (!read_from_file(&wrap.map, argv[1]))
			exit(1);
	} else {
		printf("Still to implement\n");
		exit(0);
	}
	wrap.mlx_ptr = mlx_init();
	wrap.mlx_win = mlx_new_window(wrap.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Window");
	mlx_hook(wrap.mlx_win, 17, 0, &full_quit, &wrap);
	mlx_hook(wrap.mlx_win, KeyPress, KeyPressMask, &handle_keypress, &wrap);
	mlx_hook(wrap.mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &wrap);
	wrap.auto_mode = false;
	wrap.auto_speed = 100;
	mlx_loop_hook(wrap.mlx_ptr, (int (*)(void *))auto_loop_hook, &wrap);
	wrap.data.img = mlx_new_image(wrap.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	wrap.data.addr =
		mlx_get_data_addr(wrap.data.img, &wrap.data.bits_per_pixel, &wrap.data.line_length, &wrap.data.endian);
	draw_grid(&wrap);
	mlx_put_image_to_window(wrap.mlx_ptr, wrap.mlx_win, wrap.data.img, 0, 0);
	mlx_loop(wrap.mlx_ptr);
}
