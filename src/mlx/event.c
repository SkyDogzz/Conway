#include "../../include/conway.h"

void free_map(t_map *map) {
	size_t i;

	i = 0;
	while (i < map->height) {
		free(map->cell[i]);
		i++;
	}
	free(map->cell);
}

int full_quit(t_wrap *wrap) {
	mlx_destroy_image(wrap->mlx_ptr, wrap->data.img);
	mlx_destroy_window(wrap->mlx_ptr, wrap->mlx_win);
	mlx_destroy_display(wrap->mlx_ptr);
	free(wrap->mlx_ptr);
	free_map(&wrap->map);
	exit(0);
}

int handle_keypress(int keycode, t_wrap *wrap) {
	if (keycode == KEYCODE_Q || keycode == KEYCODE_ESC)
		full_quit(wrap);
	if (keycode == KEYCODE_LEFT && wrap->auto_speed > 1)
		wrap->auto_speed /= 1.1;
	if (keycode == KEYCODE_RIGHT)
		wrap->auto_speed *= 1.1;
	if (keycode == KEYCODE_SPACE) {
		clear_image(&wrap->data);
		next_generation(&wrap->map);
		draw_grid(wrap);
		update_img(wrap);
	}
	if (keycode == 'a') {
		wrap->auto_mode = !wrap->auto_mode;
	}
	return (0);
}

int handle_keyrelease(int keycode, t_wrap *wrap) {
	(void)keycode;
	(void)wrap;
	return (0);
}
