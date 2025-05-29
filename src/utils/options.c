#include "../../include/conway.h"

t_option OPTION[] = {{"--help", "Display this help message"},
					 {"--random", "Randomize cell placement"},
					 {"--heatmap", "Color cells based on neighbor count"},
					 {"--no-grid", "Hide the grid overlay"},
					 {"--window-width", "Set the window width to SIZE (px)"},
					 {"--window-height", "Set the window height to SIZE (px)"},
					 {"--cell-size", "Set the size of each cell (px)"},
					 {"--blank-cell", "Set the padding around the map"},
					 {"--cell-offset", "Set the inner padding of a cell (px)"},
					 {"--target-fps", "Set the target frames per second"},
					 {0}};
