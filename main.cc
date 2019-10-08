#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv) {
   const string filename = argv[1];
   assert(argc == 2 && "Arguments given were not in the form './still filename'");
   VideoCapture capture(filename);
   cout << "Got the file" << endl;
   Mat frame;
   int count = 0;

   capture >> frame;
   assert(capture.isOpened());
   assert(!frame.empty());

   const unsigned int width = frame.cols;
   const unsigned int height = frame.rows;
   assert(width > 0 && "Width of the video is not greater than zero");
   assert(height > 0 && "Height of the video is not greater than zero");

   unsigned int** red = (unsigned int**) malloc(width * sizeof(unsigned int*));
   unsigned int** green = (unsigned int**) malloc(width * sizeof(unsigned int*));
   unsigned int** blue = (unsigned int**) malloc(width * sizeof(unsigned int*));

   for (unsigned int i = 0; i < width; i++) {
      red[i] = (unsigned int*) malloc(height * sizeof(unsigned int));
      green[i] = (unsigned int*) malloc(height * sizeof(unsigned int));
      blue[i] = (unsigned int*) malloc(height * sizeof(unsigned int));
   }

   // Setting the arrays to
   for (unsigned int i = 0; i < width; i++) {
      for (unsigned int j = 0; j < height; j++) {
         red[i][j] = 0;
         green[i][j] = 0;
         blue[i][j] = 0;
      }
   }

   cout << "FPS is: " << capture.get(CV_CAP_PROP_FPS) << endl;
   unsigned int frames = capture.get(CAP_PROP_FRAME_COUNT);
   cout << "Total number of frames: " << frames << endl;

   while (!frame.empty()) {
      count++;
      cout << "\033[2J\033[1;1H";
      cout << "[";
      for (unsigned int i = 0; i < width; i++) {
         for (unsigned int j = 0; j < height; j++) {
            Vec3b pixel = frame.at<Vec3b>(j, i);
            blue[i][j] += pixel[0];
            green[i][j] += pixel[1];
            red[i][j] += pixel[2];
         }
      }
      int bar = 70 * count / frames;
      for (int i = 0; i < bar; i++) {
         cout << "$";
      }
      cout << "] " << 100 * count / frames << "%\r" << endl;
      cout.flush();
      capture >> frame;
   }

   cout << "Done gathering RGB data" << endl;

   Mat result(height, width, CV_8UC3, Scalar(0, 0, 0));

   for (unsigned int i = 0; i < width; i++) {
      for (unsigned int j = 0; j < height; j++) {
         int p_red = red[i][j]/count;
         assert(p_red >= 0 && p_red <= 255 && "The red value is not within RGB boundaries");

         int p_green = green[i][j]/count;
         assert(p_green >= 0 && p_green <= 255 && "The green value is not within RGB boundaries");

         int p_blue = blue[i][j]/count;
         assert(p_blue >= 0 && p_blue <= 255 && "The blue value is not within RGB boundaries");

         Vec3b pixel(p_blue, p_green, p_red);
         result.at<Vec3b>(j, i) = pixel;
      }
   }

   ostringstream name;
   name << filename << "_image.jpeg";

   imwrite(name.str(), result);
   capture.release();

   for (unsigned int i = 0; i < width; i++) {
      free(red[i]);
      free(green[i]);
      free(blue[i]);
   }

   free(red);
   free(green);
   free(blue);

   cout << "Done!" << endl;

   return 0;
}