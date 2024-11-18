#include <sil/sil.hpp>
#include "color_effects.hpp"


int main()
{
    sil::Image image{"images/logo.png"};
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
    Effects::glitch(image);
    image = Effects::fade_between_colors(glm::vec3{1.0f, 0.0f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f});

    image.save("output/pouet.png");
}

