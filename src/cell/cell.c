#include "../../include/conway.h"

int count_neighbors(t_map *map, int x, int y) {
	int count = 0;
	for (int dx = -1; dx <= 1; dx++) {
		for (int dy = -1; dy <= 1; dy++) {
			if (dx == 0 && dy == 0)
				continue;
			int nx = x + dx;
			int ny = y + dy;
			if (nx >= 0 && nx < (int)map->width && ny >= 0 && ny < (int)map->height) {
				if (map->cell[ny][nx])
					count++;
			}
		}
	}
	return count;
}

void next_generation(t_map *map) {
	bool **new_state = malloc(sizeof(bool *) * map->height);
	for (int i = 0; i < map->height; i++) {
		new_state[i] = malloc(sizeof(bool) * map->width);
		for (int j = 0; j < map->width; j++) {
			int neighbors = count_neighbors(map, j, i);
			if (map->cell[i][j])
				new_state[i][j] = (neighbors == 2 || neighbors == 3);
			else
				new_state[i][j] = (neighbors == 3);
		}
	}
	for (int i = 0; i < map->height; i++) {
		for (int j = 0; j < map->width; j++)
			map->cell[i][j] = new_state[i][j];
		free(new_state[i]);
	}
	free(new_state);
}
