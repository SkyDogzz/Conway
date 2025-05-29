#include "../../include/conway.h"

t_option OPTION[] = {{"--help", "Display this help message"},
					 {"--random", "Fill the grid randomly"},
					 {"--heatmap", "Color cells based on neighbor count"},
					 {"--no-grid", "Hide the grid overlay"},
					 {"--window-width", "Set window width in pixels"},
					 {"--window-height", "Set window height in pixels"},
					 {"--cell-size", "Set size of each cell in pixels"},
					 {"--blank-cell", "Set padding around the map"},
					 {"--cell-offset", "Set inner padding inside each cell"},
					 {"--target-fps", "Set target frames per second"},
					 {"[size]", "Create a square grid of the given size"},
					 {"<file>", "Load map from a text file"},
					 {NULL, NULL}};
