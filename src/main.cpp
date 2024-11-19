#include <sil/sil.hpp>
#include "color_effects.hpp"


int main()
{
    sil::Image image{"images/photo.jpg"};
    //Effects::luminosity(image,0.4f);
    //image = Effects::fade();
    //Effects::rgb_split(image);
    // image = Effects::disk(50);

    // sil::Image canva{500, 500};
    // image = Effects::circle(canva,100,15,50,25);
    //image = Effects::disk(100,50);

    //Effects::animated_disk(25);

    // image = Effects::rosace();
    //Effects::miror_mosaic(image);
    // Effects::sort_pixels(image);
    //image = Effects::fade_between_colors(glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f});
    // image = Effects::mandelbrot(500, 500, 100);
    // Effects::contrast_stretching(image);
    // Effects::vortex(image, 15.f);
    Effects::convolution(image, {{0.0625, 0.125, 0.0625}, {0.125, 0.25, 0.125}, {0.0625, 0.125, 0.0625}});

    image.save("output/pouet.png");
}

