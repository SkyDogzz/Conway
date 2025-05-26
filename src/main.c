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
	clear_image(wrap);
	next_generation(&wrap->map);
	draw_grid(wrap);
	update_img(wrap);
	return (0);
}

int main(int argc, char **argv) {
	t_wrap			  wrap;
	t_arg_container **argp;

	argp = parse_argp(argc, argv);
	int i = 0;
	while (argp[i]) {
		if (argp[i]->type == ARG_STR) {
			if (ft_strcmp(argp[i]->value.as_str.key, "--map") == 0) {
				if (!read_from_file(&wrap, argp[i]->value.as_str.value))
				{
					free_argp(argp);
					exit_with_error(strerror(errno), 1);
				}
				break;
			}
		} else if (argp[i]->type == ARG_INT) {
			if (ft_strcmp(argp[i]->value.as_int.key, "--size") == 0) {
				wrap.map.height = argp[i]->value.as_int.value;
				wrap.map.width = argp[i]->value.as_int.value;
				init_map(&wrap);
				break;
			}
		}
		i++;
	}
	wrap.window_width = DEFAULT_WINDOW_WIDTH;
	wrap.window_height = DEFAULT_WINDOW_HEIGHT;
	wrap.cell_size = DEFAULT_CELL_SIZE;
	wrap.blank_cell = DEFAULT_BLANK_CELL;
	wrap.cell_offset = DEFAULT_CELL_OFFSET;

	i = 0;
	while (argp[i]) {
		if (argp[i]->type == ARG_INT) {
			if (ft_strcmp(argp[i]->value.as_int.key, "--window-width") == 0)
				wrap.window_width = argp[i]->value.as_int.value;
			else if (ft_strcmp(argp[i]->value.as_int.key, "--window-height") == 0)
				wrap.window_height = argp[i]->value.as_int.value;
			else if (ft_strcmp(argp[i]->value.as_int.key, "--cell-size") == 0)
				wrap.cell_size = argp[i]->value.as_int.value;
			else if (ft_strcmp(argp[i]->value.as_int.key, "--blank-cell") == 0)
				wrap.blank_cell = argp[i]->value.as_int.value;
			else if (ft_strcmp(argp[i]->value.as_int.key, "--cell-offset") == 0)
				wrap.cell_offset = argp[i]->value.as_int.value;
		}
		i++;
	}
	free_argp(argp);
	wrap.mlx_ptr = mlx_init();
	wrap.mlx_win = mlx_new_window(wrap.mlx_ptr, wrap.window_width, wrap.window_height, "Window");
	mlx_hook(wrap.mlx_win, 17, 0, &full_quit, &wrap);
	mlx_hook(wrap.mlx_win, KeyPress, KeyPressMask, &handle_keypress, &wrap);
	mlx_hook(wrap.mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &wrap);
	mlx_mouse_hook(wrap.mlx_win, handle_mouse_event, &wrap);
	wrap.auto_mode = false;
	wrap.auto_speed = 100;
	mlx_loop_hook(wrap.mlx_ptr, (int (*)(void *))auto_loop_hook, &wrap);
	wrap.data.img = mlx_new_image(wrap.mlx_ptr, wrap.window_width, wrap.window_height);
	wrap.data.addr =
		mlx_get_data_addr(wrap.data.img, &wrap.data.bits_per_pixel, &wrap.data.line_length, &wrap.data.endian);
	draw_grid(&wrap);
	mlx_put_image_to_window(wrap.mlx_ptr, wrap.mlx_win, wrap.data.img, 0, 0);
	mlx_loop(wrap.mlx_ptr);
}
