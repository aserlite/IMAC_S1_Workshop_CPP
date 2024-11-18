#include <sil/sil.hpp>
#include "color_effects.hpp"


int main()
{
    sil::Image image{"images/logo.png"};
    //Effects::luminosity(image,0.4f);
    //image = Effects::fade();
    //Effects::rgb_split(image);
    // image = Effects::disk(50);
    image = Effects::circle(50,15);

    image.save("output/pouet.png");
}

