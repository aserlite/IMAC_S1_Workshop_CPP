#ifndef COLOR_EFFECTS_HPP
#define COLOR_EFFECTS_HPP

#include <sil/sil.hpp>
#include <functional>
#include "random.hpp"
#include <complex>

namespace Effects {

void keep_only_green(sil::Image &image);
void exchange_colors(sil::Image &image);
void greyscale(sil::Image &image);
void negative(sil::Image &image);
sil::Image fade();
void miror(sil::Image &image);
void noise(sil::Image &image);
void rotate_90(sil::Image &image);
void rgb_split(sil::Image &image);
void luminosity(sil::Image &image, float coef);
sil::Image disk(int margin , int decx = 0, int decy = 0);
sil::Image circle(sil::Image &image,int margin, int thickness, int decx = 0, int decy = 0);
void animated_disk(int space);
sil::Image rosace();
void mosaic(sil::Image &image);
void miror_mosaic (sil::Image &pattern);
void glitch(sil::Image &image);
sil::Image fade_between_colors(const glm::vec3 &color1, const glm::vec3 &color2);
void sort_pixels(sil::Image &image);
sil::Image mandelbrot(int width, int height, int max_iterations);
void dithering(sil::Image &image);
void contrast_stretching(sil::Image &image);
void vortex(sil::Image &image, float strength);
void convolution(sil::Image &image, const std::vector<std::vector<float>> &kernel);
void gaussian_blur(sil::Image &image, float sigma);
void gaussian_difference(sil::Image &image,float sigma );
void k_means_clustering(sil::Image &image, int k);
void kuwahara_filter(sil::Image &image, int radius);

} 

#endif