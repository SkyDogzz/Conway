#include "../../include/conway.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color) {
	char *dst;

	if (x < 0 || x > WINDOW_WIDTH)
		return;
	if (y < 0 || y > WINDOW_HEIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void update_img(t_wrap *wrap) {
	mlx_put_image_to_window(wrap->mlx_ptr, wrap->mlx_win, wrap->data.img, 0, 0);
}

void clear_image(t_data *data) {
	int x, y;
	for (y = 0; y < WINDOW_HEIGHT; y++) {
		for (x = 0; x < WINDOW_WIDTH; x++)
			my_mlx_pixel_put(data, x, y, 0x000000);
	}
}
