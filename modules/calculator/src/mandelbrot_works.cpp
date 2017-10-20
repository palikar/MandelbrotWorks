#include "mandelbrot_works.hpp"
#include <opencv2/opencv.hpp>

namespace mandelbrot_works{

  double mandelbrot(double real, double im, int num_iterations)
  {

    double z_0_real = 0;
    double z_0_im = 0;
    double z_next_real;
    double z_next_im;

    for (int i = 0; i < num_iterations; ++i) {
      //calculate next
      z_next_real = z_0_real * z_0_real - z_0_im * z_0_im + real;
      z_next_im = 2 * z_0_im * z_0_real + im;

      //swap
      z_0_im = z_next_im;
      z_0_real = z_next_real;


      if((z_0_im*z_0_im + z_0_real*z_0_real) > 4)
      {
        //unbounded!
        return i;
      }

    }
    return -1.0;
  }

  void generateSetFromCenter(cv::Mat &image, double x, double y, double size, int num_iterations){

    mandelbrot_works::generateMandelbrotSet(image, x - size, x + size, y - size, y + size, num_iterations);

  }



  void generateMandelbrotSet(
    cv::Mat& mandel,
    double min_real, double max_real,
    double min_im, double max_im,
    int num_iterations) {


    int width = mandel.size[0];
    int height = mandel.size[1];


    double real_factor = (max_real - min_real)/(width - 1);
    double im_factor = (max_im - min_im)/(height - 1);


#pragma omp for
    for (int y = 0; y < width; ++y) {

      float c_im = max_im - y*im_factor;
      for (int x = 0; x < height; ++x) {
        float c_real = min_real + x*real_factor;

        int res = mandelbrot(c_real, c_im, num_iterations);
        if (res == -1)
        {
          mandel.at<double>(y,x) = 0.0;
        }
        else
        {
          double color = (res / (float)num_iterations);
          mandel.at<double>(y,x) = color;
        }


      }

    }
  }


  double fRand(double fMin, double fMax)
  {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
  }


  void superMandel(cv::Mat &image,
                   int num_points,
                   int num_iterations,
                   double x, double y, double size)
  {
    int width = image.size[0];
    int height = image.size[1];
    double min_real = x - size;
    double max_real = x + size;

    double min_im = y - size;
    double max_im = y + size;


    double real_factor = (max_real - min_real)/(width - 1);
    double im_factor = (max_im - min_im)/(height - 1);


    double point_r;
    double point_i;
    double z_0_real = 0;
    double z_0_im = 0;
    double z_next_real;
    double z_next_im;

    int x_;
    int y_;

    double incr_val = 0.000000001;


    for (int n = 0; n < num_points; ++n) {


      point_r = fRand(x-size, x+size);
      point_i = fRand(y-size, y+size);

      double res = mandelbrot(point_r, point_i,num_iterations);
      if(res >= 0)
      {
        z_0_real = 0;
        z_0_im = 0;

        while ((z_0_im*z_0_im + z_0_real*z_0_real) < 4)
        {
          //calculate next
          z_next_real = z_0_real * z_0_real - z_0_im * z_0_im + point_r;
          z_next_im = 2 * z_0_im * z_0_real + point_i;

          //swap
          z_0_im = z_next_im;
          z_0_real = z_next_real;

          x_ = (z_0_real - min_real)/real_factor;
          y_ = (-z_0_im + max_im)/im_factor;
          if(x_ >= 0 && y_ >= 0 && x_<width && y_<height)
          {
            image.at<double>(x_,y_)+= incr_val;
          }
          
        }


        point_i = -point_i;
        z_0_real = 0;
        z_0_im = 0;

        while ((z_0_im*z_0_im + z_0_real*z_0_real) < 4)
        {
          //calculate next
          z_next_real = z_0_real * z_0_real - z_0_im * z_0_im + point_r;
          z_next_im = 2 * z_0_im * z_0_real + point_i;

          //swap
          z_0_im = z_next_im;
          z_0_real = z_next_real;

          x_ = (z_0_real - min_real)/real_factor;
          y_ = (-z_0_im + max_im)/im_factor;
          if(x_ >= 0 && y_ >= 0 && x_<width && y_<height)
          {
            image.at<double>(x_,y_)+= incr_val;
          }
          
        }
        

      }


    }


  }


}
