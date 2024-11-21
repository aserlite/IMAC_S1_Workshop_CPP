#include "color_effects.hpp"

namespace Effects
{

    void keep_only_green(sil::Image &image)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                image.pixel(x, y).r = 0.f;
                image.pixel(x, y).b = 0.f;
            }
        }
    }

    void exchange_colors(sil::Image &image)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float tmp = image.pixel(x, y).r;
                image.pixel(x, y).r = image.pixel(x, y).b;
                image.pixel(x, y).b = tmp;
            }
        }
    }

    void greyscale(sil::Image &image)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float grey = image.pixel(x, y).r * 0.30f + image.pixel(x, y).g * 0.59f + image.pixel(x, y).b * 0.11f;
                image.pixel(x, y).r = grey;
                image.pixel(x, y).g = grey;
                image.pixel(x, y).b = grey;
            }
        }
    }

    void negative(sil::Image &image)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                image.pixel(x, y).r = 1.f - image.pixel(x, y).r;
                image.pixel(x, y).g = 1.f - image.pixel(x, y).g;
                image.pixel(x, y).b = 1.f - image.pixel(x, y).b;
            }
        }
    }

    void miror(sil::Image &image)
    {
        sil::Image ref = image;
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                int miror_ref = image.width() - x - 1;
                image.pixel(x, y).r = ref.pixel(miror_ref, y).r;
                image.pixel(x, y).g = ref.pixel(miror_ref, y).g;
                image.pixel(x, y).b = ref.pixel(miror_ref, y).b;
            }
        }
    }

    void noise(sil::Image &image)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                if (random_int(1, 10) == 5)
                {
                    image.pixel(x, y) = {random_float(0, 1), random_float(0, 1), random_float(0, 1)};
                }
            }
        }
    }

    void rotate_90(sil::Image &image)
    {
        sil::Image rotated_image(image.height(), image.width());
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                rotated_image.pixel(y, image.width() - 1 - x) = image.pixel(x, y);
            }
        }
        image = rotated_image;
    }

    void rgb_split(sil::Image &image)
    {
        sil::Image red_channel = image;
        sil::Image green_channel = image;
        sil::Image blue_channel = image;

        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                red_channel.pixel(x, y).g = 0.f;
                red_channel.pixel(x, y).b = 0.f;

                green_channel.pixel(x, y).r = 0.f;
                green_channel.pixel(x, y).b = 0.f;

                blue_channel.pixel(x, y).r = 0.f;
                blue_channel.pixel(x, y).g = 0.f;
            }
        }

        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                if (x + 10 < image.width())
                {
                    image.pixel(x, y).r = red_channel.pixel(x + 10, y).r;
                }
                else
                {
                    image.pixel(x, y).r = 0.f;
                }

                if (x - 10 >= 0)
                {
                    image.pixel(x, y).g = green_channel.pixel(x - 10, y).g;
                }
                else
                {
                    image.pixel(x, y).g = 0.f;
                }

                if (y + 10 < image.height())
                {
                    image.pixel(x, y).b = blue_channel.pixel(x, y + 10).b;
                }
                else
                {
                    image.pixel(x, y).b = 0.f;
                }
            }
        }
    }

    void luminosity(sil::Image &image, float coef)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                image.pixel(x, y).r = std::min(1.0f, std::max(0.0f, image.pixel(x, y).r + coef));
                image.pixel(x, y).g = std::min(1.0f, std::max(0.0f, image.pixel(x, y).g + coef));
                image.pixel(x, y).b = std::min(1.0f, std::max(0.0f, image.pixel(x, y).b + coef));
            }
        }
    }

    void sort_pixels(sil::Image &image)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            std::vector<std::tuple<float, float, float>> column;
            for (int y = 0; y < image.height(); ++y)
            {
                auto pixel = image.pixel(x, y);
                column.emplace_back(pixel.r, pixel.g, pixel.b);
            }

            std::sort(column.begin(), column.end(), [](const auto &a, const auto &b)
                      { return (std::get<0>(a) + std::get<1>(a) + std::get<2>(a)) < (std::get<0>(b) + std::get<1>(b) + std::get<2>(b)); });

            for (int y = 0; y < image.height(); ++y)
            {
                auto &[r, g, b] = column[y];
                image.pixel(x, y).r = r;
                image.pixel(x, y).g = g;
                image.pixel(x, y).b = b;
            }
        }
    }

} // namespace Effects