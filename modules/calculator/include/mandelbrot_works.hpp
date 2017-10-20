#include <opencv2/opencv.hpp>


namespace mandelbrot_works
{

  void generateMandelbrotSet(
    cv::Mat& image,
    double min_reaxl, double max_real,
    double min_im, double max_im,
    int num_iterations);

  double mandelbrot(double real, double im, int num_iterations);

  void generateSetFromCenter(cv::Mat &image, double x, double y, double size, int num_iterations);



  void superMandel(cv::Mat &image,
                   int num_points,
                   int num_iterations,
                   double x, double y, double size);











}


