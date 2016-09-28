

#include "json.h"


// maximum number of objects
#define MAX_NODES 128

// json array
node scene[MAX_NODES];

// number of nodes. Should be <= MAX_NODES
int nNodes;

// viewport size
int width, height;


void ray_casting(const char *filename)
{
}

int main(int argc, char *argv[])
{
	if (argc != 5)
	{
		fprintf(stderr, "Please, use raycast <width> <height> <input.json> <output.ppm>\n");
		return 1;
	}

	width = atoi(argv[1]);
	if (width <= 0 || width > 4906)
	{
		fprintf(stderr, "Wrong output image size. Please, use any size between 1..4096\n");
		return 1;
	}
	
	height = atoi(argv[2]);
	if (height <= 0 || height > 4906)
	{
		fprintf(stderr, "Wrong output image size. Please, use any size between 1..4096\n");
		return 1;
	}
	
	read_scene(argv[3], &nNodes, scene);
	ray_casting(argv[4]);
	
	return 0;
} 
