#include "../../include/conway.h"

void draw_line(t_wrap *wrap, t_line line, int color) {
	int	  dx;
	int	  dy;
	float m;
	int	  x;
	float y;

	dx = line.p2.x - line.p1.x;
	dy = line.p2.y - line.p1.y;

	if (dx == 0) {
		int y_start = line.p1.y < line.p2.y ? line.p1.y : line.p2.y;
		int y_end = line.p1.y > line.p2.y ? line.p1.y : line.p2.y;
		for (int y = y_start; y <= y_end; y++)
			my_mlx_pixel_put(&wrap->data, line.p1.x, y, color);
		return;
	}

	m = (float)dy / (float)dx;
	x = line.p1.x;
	while (x <= line.p2.x) {
		y = m * (x - line.p1.x) + line.p1.y;
		my_mlx_pixel_put(&wrap->data, x, (int)y, color);
		x++;
	}
}

void get_grid_size(t_map map, int *height, int *width) {
	*height = map.height * CELL_SIZE;
	*width = map.width * CELL_SIZE;
}

void get_offsets(t_map map, int height, int width, int *offsetX, int *offsetY) {
	*offsetX = WINDOW_WIDTH - width;
	*offsetY = WINDOW_HEIGHT - height;
	(void)map;
}

void fill_cell(t_wrap *wrap, int x, int y, int color) {
	for (int i = 1 + CELL_OFFSET; i < CELL_SIZE - CELL_OFFSET; i++) {
		for (int j = 1 + CELL_OFFSET; j < CELL_SIZE - CELL_OFFSET; j++) {
			my_mlx_pixel_put(&wrap->data, x + j, y + i, color);
		}
	}
}

void draw_grid(t_wrap *wrap) {
	int	   height;
	int	   width;
	int	   offsetX;
	int	   offsetY;
	t_line line;

	get_grid_size(wrap->map, &height, &width);
	get_offsets(wrap->map, height, width, &offsetX, &offsetY);

	for (size_t i = 0; i < wrap->map.height; i++) {
		for (size_t j = 0; j < wrap->map.width; j++) {
			int x = offsetX / 2 + j * CELL_SIZE;
			int y = offsetY / 2 + i * CELL_SIZE;
			if (wrap->map.cell[i][j])
				fill_cell(wrap, x, y, 0xF0F0F0);
		}
	}

	for (size_t j = 0; j <= wrap->map.width; j++) {
		line.p1.x = offsetX / 2 + j * CELL_SIZE;
		line.p2.x = line.p1.x;
		line.p1.y = offsetY / 2;
		line.p2.y = offsetY / 2 + height;
		draw_line(wrap, line, 0xA0A0A0);
	}

	for (size_t i = 0; i <= wrap->map.height; i++) {
		line.p1.y = offsetY / 2 + i * CELL_SIZE;
		line.p2.y = line.p1.y;
		line.p1.x = offsetX / 2;
		line.p2.x = offsetX / 2 + width;
		draw_line(wrap, line, 0xA0A0A0);
	}
}
