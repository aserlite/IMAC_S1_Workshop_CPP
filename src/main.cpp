#include <sil/sil.hpp>
#include "color_effects.hpp"


int main()
{
    sil::Image image{"images/photo.jpg"};

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

    // Effects::convolution(image, sharpen);

    image = Effects::diamond_square(10); // crash au dessus de 14
    image.save("images/readme/diamond_square.png");
}

