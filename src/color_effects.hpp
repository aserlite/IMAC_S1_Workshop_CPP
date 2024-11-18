#ifndef COLOR_EFFECTS_HPP
#define COLOR_EFFECTS_HPP

#include <sil/sil.hpp>
#include <functional>
#include "random.hpp"

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
sil::Image circle(int margin, int thickness);
void animated_disk(int space);


} 

#endif