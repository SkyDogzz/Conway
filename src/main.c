#include "../include/conway.h"

void exit_with_error(const char *err, const int code) {
	fprintf(stderr, "%s\n", err);
	exit(code);
}


void draw_info(t_wrap *wrap) {
	int y = 20;
	char str[64];

	sprintf(str, "Framerate max: %d", wrap->target_fps);
	mlx_string_put(wrap->mlx_ptr, wrap->mlx_win, 20, y += 15, 0xFFFFFF, str);
	sprintf(str, "FPS: %d", wrap->real_fps);
	mlx_string_put(wrap->mlx_ptr, wrap->mlx_win, 20, y += 15, 0xFFFFFF, str);
	sprintf(str, "Grid: %d x %d", wrap->map.width, wrap->map.height);
	mlx_string_put(wrap->mlx_ptr, wrap->mlx_win, 20, y += 15, 0xFFFFFF, str);
	sprintf(str, "Cell size: %d", wrap->cell_size);
	mlx_string_put(wrap->mlx_ptr, wrap->mlx_win, 20, y += 15, 0xFFFFFF, str);
	sprintf(str, "Heatmap: %s", wrap->heatmap ? "ON" : "OFF");
	mlx_string_put(wrap->mlx_ptr, wrap->mlx_win, 20, y += 15, 0xFFFFFF, str);
	sprintf(str, "Auto mode: %s", wrap->auto_mode ? "ON" : "OFF");
	mlx_string_put(wrap->mlx_ptr, wrap->mlx_win, 20, y += 15, 0xFFFFFF, str);
	sprintf(str, "Grid overlay: %s", wrap->display_grid ? "ON" : "OFF");
	mlx_string_put(wrap->mlx_ptr, wrap->mlx_win, 20, y += 15, 0xFFFFFF, str);
}

int auto_loop_hook(t_wrap *wrap) {
	static struct timeval last_time = {0};
	static struct timeval last_fps_check = {0};
	static int			  frame_count = 0;

	struct timeval current_time;
	double		   elapsed;
	double		   frame_delay;
	double		   fps_elapsed;

	if (!wrap->auto_mode)
	{
		draw_info(wrap);
		return 0;
	}

	gettimeofday(&current_time, NULL);

	elapsed = (current_time.tv_sec - last_time.tv_sec) + (current_time.tv_usec - last_time.tv_usec) / 1000000.0;

	frame_delay = 1.0 / wrap->target_fps;

	if (elapsed >= frame_delay) {
		last_time = current_time;
		clear_image(wrap);
		next_generation(&wrap->map);
		draw_grid(wrap);
		update_img(wrap);
		draw_info(wrap);
		frame_count++;
	}

	fps_elapsed =
		(current_time.tv_sec - last_fps_check.tv_sec) + (current_time.tv_usec - last_fps_check.tv_usec) / 1000000.0;
	if (fps_elapsed >= 1.0) {
		wrap->real_fps = frame_count;
		frame_count = 0;
		last_fps_check = current_time;
	}
	return 0;
}

void display_help(void) {
	int i = 0;

	printf("Conway's Game of Life - Available Options\n");
	printf("Usage:\n");
	printf("  ./conway map_file.txt [OPTIONS...]\n");
	printf("  ./conway size [OPTIONS...]\n\n");

	printf("Examples:\n");
	printf("  ./conway 50 --random --heatmap\n");
	printf("  ./conway pattern.txt --no-grid --cell-size 8\n\n");

	printf("Options:\n");
	while (OPTION[i].name != NULL) {
		printf("  %-20s %s\n", OPTION[i].name, OPTION[i].description);
		i++;
	}
}

int main(int argc, char **argv) {
	t_wrap			  wrap;
	t_arg_container **argp;

	if (argc == 1) {
		display_help();
		return (0);
	}
	argp = parse_argp(argc, argv);

	wrap.window_width = DEFAULT_WINDOW_WIDTH;
	wrap.window_height = DEFAULT_WINDOW_HEIGHT;
	wrap.cell_size = DEFAULT_CELL_SIZE;
	wrap.blank_cell = DEFAULT_BLANK_CELL;
	wrap.cell_offset = DEFAULT_CELL_OFFSET;
	wrap.target_fps = DEFAULT_TARGET_FPS;
	wrap.display_grid = DEFAULT_DISPLAY_GRID;
	wrap.run = false;
	wrap.random = false;
	wrap.real_fps = 0;
	wrap.heatmap = false;
	wrap.offset_x = 0;
	wrap.offset_y = 0;

	int i = 0;

	while (argp[i]) {
		if (argp[i]->type == ARG_BOOL && ft_strcmp(argp[i]->value.as_bool.key, "--help") == 0) {
			display_help();
			free_argp(argp);
			return (0);
		}
		i++;
	}

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
			else if (ft_strcmp(argp[i]->value.as_int.key, "--target-fps") == 0)
				wrap.target_fps = argp[i]->value.as_int.value;
			else {
				display_help();
				free_argp(argp);
				return (0);
			}
		} else if (argp[i]->type == ARG_BOOL) {
			if (ft_strcmp(argp[i]->value.as_bool.key, "--no-grid") == 0)
				wrap.display_grid = false;
			else if (ft_strcmp(argp[i]->value.as_bool.key, "--random") == 0)
				wrap.random = true;
			else if (ft_strcmp(argp[i]->value.as_bool.key, "--heatmap") == 0)
				wrap.heatmap = true;
			else {
				display_help();
				free_argp(argp);
				return (0);
			}
		} else {
			display_help();
			free_argp(argp);
			return (0);
		}
		i++;
	}

	i = 1;
	while (i < argc) {
		int size;

		if (argv[i][0] == '-')
			i++;
		else if (strict_atoi(argv[i], &size)) {
			wrap.map.height = size;
			wrap.map.width = size;
			init_map(&wrap);
			if (wrap.random) {
				srand(time(NULL));
				for (int y = wrap.blank_cell; y < wrap.map.height - wrap.blank_cell; y++) {
					for (int x = wrap.blank_cell; x < wrap.map.width - wrap.blank_cell; x++) {
						wrap.map.cell[y][x] = rand() % 2;
					}
				}
			}
			wrap.run = true;
			break;
		} else {
			if (!read_from_file(&wrap, argv[i])) {
				free_argp(argp);
				exit_with_error(strerror(errno), 1);
			}
			wrap.run = true;
			break;
		}
	}

	free_argp(argp);
	if (!wrap.run) {
		display_help();
		return (0);
	}
	wrap.mlx_ptr = mlx_init();
	wrap.mlx_win = mlx_new_window(wrap.mlx_ptr, wrap.window_width, wrap.window_height, "Window");
	mlx_hook(wrap.mlx_win, 17, 0, &full_quit, &wrap);
	mlx_hook(wrap.mlx_win, KeyPress, KeyPressMask, &handle_keypress, &wrap);
	mlx_hook(wrap.mlx_win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &wrap);
	mlx_mouse_hook(wrap.mlx_win, handle_mouse_event, &wrap);
	wrap.auto_mode = false;
	mlx_loop_hook(wrap.mlx_ptr, (int (*)(void *))auto_loop_hook, &wrap);
	wrap.data.img = mlx_new_image(wrap.mlx_ptr, wrap.window_width, wrap.window_height);
	wrap.data.addr =
		mlx_get_data_addr(wrap.data.img, &wrap.data.bits_per_pixel, &wrap.data.line_length, &wrap.data.endian);
	draw_grid(&wrap);
	mlx_put_image_to_window(wrap.mlx_ptr, wrap.mlx_win, wrap.data.img, 0, 0);
	mlx_loop(wrap.mlx_ptr);
}
