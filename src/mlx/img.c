#include "../../include/conway.h"

void my_mlx_pixel_put(t_wrap *wrap, int x, int y, int color) {
	char *dst;
	t_data	*data;

	if (x < 0 || x > wrap->window_width)
		return;
	if (y < 0 || y > wrap->window_height)
		return;
	data = &wrap->data;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void update_img(t_wrap *wrap) {
	mlx_put_image_to_window(wrap->mlx_ptr, wrap->mlx_win, wrap->data.img, 0, 0);
}

void clear_image(t_wrap *wrap) {
	int x, y;
	for (y = 0; y < wrap->window_height; y++) {
		for (x = 0; x < wrap->window_width; x++)
			my_mlx_pixel_put(wrap, x, y, 0x000000);
	}
}
