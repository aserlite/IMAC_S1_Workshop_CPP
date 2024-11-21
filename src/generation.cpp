#include "color_effects.hpp"

namespace Effects
{

    sil::Image fade()
    {
        sil::Image image{300 /*width*/, 200 /*height*/};
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float intensity = static_cast<float>(x) / image.width();
                image.pixel(x, y).r = intensity;
                image.pixel(x, y).g = intensity;
                image.pixel(x, y).b = intensity;
            }
        }
        return image;
    }

    sil::Image fade_between_colors(const glm::vec3 &color1, const glm::vec3 &color2)
    {
        sil::Image image{300 /*width*/, 200 /*height*/};
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float percentage = static_cast<float>(x) / image.width();
                glm::vec3 mixed_color = glm::mix(color1, color2, percentage);
                image.pixel(x, y).r = mixed_color.r;
                image.pixel(x, y).g = mixed_color.g;
                image.pixel(x, y).b = mixed_color.b;
            }
        }
        return image;
    }

    sil::Image mandelbrot(int width, int height, int max_iterations)
    {
        sil::Image image{width, height};
        for (int x = 0; x < width; ++x)
        {
            for (int y = 0; y < height; ++y)
            {
                std::complex<float> c((x - width / 2.0f) * 4.0f / width, (y - height / 2.0f) * 4.0f / height);
                std::complex<float> z = 0;
                int iterations = 0;
                while (std::abs(z) <= 2.0f && iterations < max_iterations)
                {
                    z = z * z + c;
                    ++iterations;
                }
                float intensity = static_cast<float>(iterations) / max_iterations;
                image.pixel(x, y).r = intensity;
                image.pixel(x, y).g = intensity;
                image.pixel(x, y).b = intensity;
            }
        }
        return image;
    }

    sil::Image disk(int margin, int decx, int decy)
    {
        int width = 500;
        int height = 500;
        sil::Image image{width, height};
        int centerX = width / 2 + decx;
        int centerY = height / 2 + decy;
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

    sil::Image circle(sil::Image &image, int margin, int thickness, int decx, int decy)
    {
        int width = image.width();
        int height = image.height();
        int centerX = width / 2 + decx;
        int centerY = height / 2 + decy;
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

    void animated_disk(int space)
    {
        int frames = 0;
        for (int i = -250; i <= 250; i += space)
        {
            sil::Image image = disk(100, i, 0);
            std::string name = "output/animation/frame" + std::to_string(frames) + ".png";
            frames++;
            image.save(name);
        }
    }

    sil::Image rosace()
    {
        sil::Image image{500, 500};
        int margin = 150;
        int thickness = 5;
        int radius = image.width() / 2 - margin;
        Effects::circle(image, margin, thickness, 0, 0);
        Effects::circle(image, margin, thickness, 100, 0);
        Effects::circle(image, margin, thickness, -100, 0);
        Effects::circle(image, margin, thickness, radius / 2, radius - radius / 6);
        Effects::circle(image, margin, thickness, -radius / 2, radius - radius / 6);
        Effects::circle(image, margin, thickness, radius / 2, -radius + radius / 6);
        Effects::circle(image, margin, thickness, -radius / 2, -radius + radius / 6);
        return image;
    }

} // namespace Effects