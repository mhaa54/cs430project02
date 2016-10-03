

#include "json.h"
#include "ppmrw_io.h"
#include <math.h>


// maximum number of objects
#define MAX_NODES 128

// distance to near clipping plane
#define zp 1

// distance to far clipping plane
#define fcp 200

// json array
node scene[MAX_NODES];

// number of nodes. Should be <= MAX_NODES
int nNodes;

// viewport size
int width, height;


// return 1 if we found an intersection of the vector "u" with the scene
// pos is the resulting hit position in the space, and "index" the resulting object index
int shoot(double *u, double *pos, int *index)
{
  return 1;
}

// to the ray casting, and save it into filename
void ray_casting(const char *filename)
{
  // do some validations
  if (nNodes <= 0)
  {
    fprintf(stderr, "Empty scene\n");
    exit(1);
  }

  // look for camera object
  int found = 0;
  double w, h;
  for (int i = 0; i < nNodes; i++)
  {
    if (strcmp(scene[i].type, "camera") == 0)
    {
      found = 1;
      w = scene[i].width;
      h = scene[i].height;
      if (w <= 0.0 || w > 4096.0 || h< 0.0 || h > 4096.0)
      {
        fprintf(stderr, "Invalid camera. Please, check the scene\n");
        exit(1);
      }
    }
  }
  if (found == 0)
  {
    fprintf(stderr, "Camera object not found. Invalid scene\n");
    exit(1);
  }


  // creating image buffer
  unsigned char *imageR = NULL, *imageG = NULL, *imageB = NULL;
  /*
  * Dynamically allocate memory to hold image buffers
  */
  imageR = (unsigned char *)malloc(height * width * sizeof(unsigned char));
  imageG = (unsigned char *)malloc(height * width * sizeof(unsigned char));
  imageB = (unsigned char *)malloc(height * width * sizeof(unsigned char));

  /*
  * Check validity
  */
  if (imageR == NULL || imageG == NULL || imageB == NULL)
  {
    fprintf(stderr, "Memory allocation failed for the image\n");
    exit(1);
  }

  // erasing image
  int s = width * height;
  memset(imageR, 0, s);
  memset(imageG, 0, s);
  memset(imageB, 0, s);

  // the height of one pixel 
  double pixheight = h / (double)height;

  // the width of one pixel 
  double pixwidth = w / (double)width;
  
  // for each row 
  for(int i = 0; i < pixheight; i++)
  { 
    // y coord of row 
    double py = -h/2.0 + pixheight * (i + 0.5);

    // for each column 
    for(int j = 0; j < width; j++)
    { 
      // x coord of column 
      double px = -w/2.0 + pixwidth * (j + 0.5);

      // z coord is on screen 
      double pz = -zp;

      // length of p vector
      double norm = sqrt(px*px + py*py + pz*pz);

      // unit ray vector 
      double ur[3] = {px/norm, py/norm, pz/norm};

      // return position of first hit 
      double hit[3];
      int index;
      if (shoot(ur, hit, &index))
      {
        // pixel colored by object hit 
      }

    } 
  }  


  // save ppm file
  writePPM6(imageR, imageG, imageB, height, width, filename);

  // free image
  free(imageR);
  free(imageG);
  free(imageB);
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
