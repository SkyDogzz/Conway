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
			my_mlx_pixel_put(wrap, line.p1.x, y, color);
		return;
	}

	m = (float)dy / (float)dx;
	x = line.p1.x;
	while (x <= line.p2.x) {
		y = m * (x - line.p1.x) + line.p1.y;
		my_mlx_pixel_put(wrap, x, (int)y, color);
		x++;
	}
}

void get_grid_size(t_wrap *wrap, int *height, int *width) {
	*height = wrap->map.height * wrap->cell_size;
	*width = wrap->map.width * wrap->cell_size;
}

void get_offsets(t_wrap *wrap, int height, int width, int *offsetX, int *offsetY) {
	*offsetX = wrap->window_width - width;
	*offsetY = wrap->window_height - height;
}

void fill_cell(t_wrap *wrap, int x, int y, int color) {
	if (wrap->cell_size <= 5) {
		for (int i = 1; i <= wrap->cell_size; i++) {
			for (int j = 1; j <= wrap->cell_size; j++) {
				my_mlx_pixel_put(wrap, x + j, y + i, color);
			}
		}
	} else {
		for (int i = wrap->cell_offset; i <= wrap->cell_size - wrap->cell_offset + 1; i++) {
			for (int j = wrap->cell_offset; j <= wrap->cell_size - wrap->cell_offset + 1; j++) {
				my_mlx_pixel_put(wrap, x + j, y + i, color);
			}
		}
	}
}

int get_heatmap_color(int neighbors) {
	if (neighbors < 0)
		neighbors = 0;
	if (neighbors > 8)
		neighbors = 8;

	int r = (255 * neighbors) / 8;
	int g = 0;
	int b = (255 * (8 - neighbors)) / 8;

	return (r << 16) | (g << 8) | b;
}

void draw_grid(t_wrap *wrap) {
	int	   height;
	int	   width;
	int	   offsetX;
	int	   offsetY;
	t_line line;

	get_grid_size(wrap, &height, &width);
	get_offsets(wrap, height, width, &offsetX, &offsetY);

	for (int i = 0; i < wrap->map.height; i++) {
		for (int j = 0; j < wrap->map.width; j++) {
			int x = offsetX / 2 + j * wrap->cell_size;
			int y = offsetY / 2 + i * wrap->cell_size;
			if (wrap->map.cell[i][j]) {
				if (wrap->map.cell[i][j]) {
					int color = 0xF0F0F0;
					if (wrap->heatmap) {
						int neighbors = count_neighbors(&wrap->map, j, i);
						color = get_heatmap_color(neighbors);
					}
					fill_cell(wrap, x, y, color);
				}
			}
		}
	}

	if (!wrap->display_grid)
		return;

	if (wrap->cell_size > 5) {
		for (int j = 0; j <= wrap->map.width; j++) {
			line.p1.x = offsetX / 2 + j * wrap->cell_size;
			line.p2.x = line.p1.x;
			line.p1.y = offsetY / 2;
			line.p2.y = offsetY / 2 + height;
			draw_line(wrap, line, 0xA0A0A0);
		}

		for (int i = 0; i <= wrap->map.height; i++) {
			line.p1.y = offsetY / 2 + i * wrap->cell_size;
			line.p2.y = line.p1.y;
			line.p1.x = offsetX / 2;
			line.p2.x = offsetX / 2 + width;
			draw_line(wrap, line, 0xA0A0A0);
		}
	}
}
