#include "../../include/conway.h"

void free_map(t_map *map) {
	int i;

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
	if (keycode == KEYCODE_LEFT && wrap->auto_speed > 1) {
		if (wrap->auto_speed > 100)
			wrap->auto_speed /= 1.1;
	}
	if (keycode == KEYCODE_RIGHT) {
		wrap->auto_speed *= 1.1;
	}
	if (keycode == KEYCODE_SPACE) {
		clear_image(wrap);
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

bool is_in_grid(t_wrap *wrap, int x, int y) {
	int width;
	int height;
	int offsetX;
	int offsetY;

	get_grid_size(wrap, &height, &width);
	get_offsets(wrap, height, width, &offsetX, &offsetY);

	if (x < offsetX / 2 || x > width + offsetX / 2)
		return (false);
	else if (y < offsetY / 2 || y > width + offsetY / 2)
		return (false);
	return (true);
}

void get_cell_pos(t_wrap *wrap, int x, int y, t_point *cell) {
	int width;
	int height;
	int offsetX;
	int offsetY;

	get_grid_size(wrap, &height, &width);
	get_offsets(wrap, height, width, &offsetX, &offsetY);
	x = x - offsetX / 2;
	y = y - offsetY / 2;
	cell->x = x / wrap->cell_size;
	cell->y = y / wrap->cell_size;
}

void switch_cell(t_wrap *wrap, t_point cell) {
	if (wrap->map.cell[cell.y][cell.x] == true)
		wrap->map.cell[cell.y][cell.x] = false;
	else
		wrap->map.cell[cell.y][cell.x] = true;
	clear_image(wrap);
	draw_grid(wrap);
	update_img(wrap);
}

int handle_mouse_event(int keycode, int x, int y, t_wrap *wrap) {
	t_point cell;
	if (keycode != 1)
		return (0);
	if (!is_in_grid(wrap, x, y)) {
		return (0);
	}
	get_cell_pos(wrap, x, y, &cell);
	switch_cell(wrap, cell);
	(void)wrap;
	return (0);
}
