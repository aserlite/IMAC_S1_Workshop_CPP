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

    std::vector<std::vector<float>> emboss = {
    {-2, -1, 0},
    {-1,  1, 1},
    { 0,  1, 2}
    };
    std::vector<std::vector<float>> outline = {
        {-1, -1, -1},
        {-1,  8, -1},
        {-1, -1, -1}
    };
    std::vector<std::vector<float>> sharpen = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };

    std::vector<std::vector<float>> gaussian = {
        {1 / 273.0f,  4 / 273.0f,  7 / 273.0f,  4 / 273.0f, 1 / 273.0f},
        {4 / 273.0f, 16 / 273.0f, 26 / 273.0f, 16 / 273.0f, 4 / 273.0f},
        {7 / 273.0f, 26 / 273.0f, 41 / 273.0f, 26 / 273.0f, 7 / 273.0f},
        {4 / 273.0f, 16 / 273.0f, 26 / 273.0f, 16 / 273.0f, 4 / 273.0f},
        {1 / 273.0f,  4 / 273.0f,  7 / 273.0f,  4 / 273.0f, 1 / 273.0f}
    };
    
    Effects::convolution(image, gaussian);
    
    image.save("output/pouet.png");
}

