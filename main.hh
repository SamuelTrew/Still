#ifndef STILL_MAIN_H
#define STILL_MAIN_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Mat set_average_colour(unsigned int** red, unsigned int** green, unsigned int** blue, unsigned int width, unsigned int height, int count);
void free_resources(unsigned int** red, unsigned int** green, unsigned int** blue, unsigned int width);

#endif //STILL_MAIN_H
