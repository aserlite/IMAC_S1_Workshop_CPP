#include "color_effects.hpp"

namespace Effects
{

    void keep_only_green(sil::Image &image)
    {
        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                image.pixel(x, y).r = 0.f;
                image.pixel(x, y).b = 0.f;
            }
        }
    }

    void exchange_colors(sil::Image &image)
    {
        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                float tmp = image.pixel(x, y).r;
                image.pixel(x, y).r = image.pixel(x, y).b;
                image.pixel(x, y).b = tmp;
            }
        }
    }

    void greyscale(sil::Image &image)
    {
        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
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
        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                image.pixel(x, y).r = 1.f - image.pixel(x, y).r;
                image.pixel(x, y).g = 1.f - image.pixel(x, y).g;
                image.pixel(x, y).b = 1.f - image.pixel(x, y).b;
            }
        }
    }

    sil::Image fade()
    {
        sil::Image image{300 /*width*/, 200 /*height*/};

        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                float intensity = static_cast<float>(x) / image.width();
                image.pixel(x, y).r = intensity;
                image.pixel(x, y).g = intensity;
                image.pixel(x, y).b = intensity;
            }
        }

        return image;
    }

    void miror(sil::Image &image)
    {
        sil::Image ref = image;
        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
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
        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
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

        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
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

        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                red_channel.pixel(x, y).g = 0.f;
                red_channel.pixel(x, y).b = 0.f;

                green_channel.pixel(x, y).r = 0.f;
                green_channel.pixel(x, y).b = 0.f;

                blue_channel.pixel(x, y).r = 0.f;
                blue_channel.pixel(x, y).g = 0.f;
            }
        }

        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
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
        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
            {
                image.pixel(x, y).r = std::min(1.0f, std::max(0.0f, image.pixel(x, y).r + coef));
                image.pixel(x, y).g = std::min(1.0f, std::max(0.0f, image.pixel(x, y).g + coef));
                image.pixel(x, y).b = std::min(1.0f, std::max(0.0f, image.pixel(x, y).b + coef));
            }
        }
    }

    sil::Image disk(int margin)
    {
        int width = 500;
        int height = 500;
        sil::Image image{width, height};

        int centerX = width / 2;
        int centerY = height / 2;
        int radius = std::min(width, height) / 2 - margin;

        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                int dx = x - centerX;
                int dy = y - centerY;
                if (dx * dx + dy * dy < radius * radius)
                {
                    image.pixel(x, y) = {1.0f, 1.0f, 1.0f};
                }
            }
        }

        return image;
    }

    sil::Image circle(int margin, int thickness)
    {
        int width = 500;
        int height = 500;
        sil::Image image{width, height};

        int centerX = width / 2;
        int centerY = height / 2;
        int outerRadius = std::min(width, height) / 2 - margin;
        int innerRadius = outerRadius - thickness;

        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                int dx = x - centerX;
                int dy = y - centerY;
                int distanceSquared = dx * dx + dy * dy;
                if (distanceSquared < outerRadius * outerRadius && distanceSquared >= innerRadius * innerRadius)
                {
                    image.pixel(x, y) = {1.0f, 1.0f, 1.0f};
                }
            }
        }

        return image;
    }

    sil::Image disk(int margin)
    {
        int width = 500;
        int height = 500;
        sil::Image image{width, height};

        int centerX = width / 2;
        int centerY = height / 2;
        int radius = std::min(width, height) / 2 - margin;

        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                int dx = x - centerX;
                int dy = y - centerY;
                if (dx * dx + dy * dy < radius * radius)
                {
                    image.pixel(x, y) = {1.0f, 1.0f, 1.0f};
                }
            }
        }

        return image;
    }
}