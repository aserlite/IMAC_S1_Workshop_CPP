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

    void mosaic(sil::Image &pattern)
    {
        const int targetWidth = pattern.width() * 4;
        const int targetHeight = pattern.height() * 4;
        sil::Image mosaicImage{targetWidth, targetHeight};

        for (int x = 0; x < targetWidth; x += pattern.width())
        {
            for (int y = 0; y < targetHeight; y += pattern.height())
            {
                for (int i = 0; i < pattern.width(); i++)
                {
                    for (int j = 0; j < pattern.height(); j++)
                    {
                        if (x + i < targetWidth && y + j < targetHeight)
                        {
                            mosaicImage.pixel(x + i, y + j) = pattern.pixel(i, j);
                        }
                    }
                }
            }
        }

        pattern = mosaicImage;
    }

    void miror_mosaic(sil::Image &pattern)
    {
        const int targetWidth = pattern.width() * 4;
        const int targetHeight = pattern.height() * 4;
        sil::Image mosaicImage{targetWidth, targetHeight};

        for (int x = 0; x < targetWidth; x += pattern.width())
        {
            for (int y = 0; y < targetHeight; y += pattern.height())
            {
                bool invert = ((x / pattern.width()) % 2 == 1) ^ ((y / pattern.height()) % 2 == 1);
                for (int i = 0; i < pattern.width(); i++)
                {
                    for (int j = 0; j < pattern.height(); j++)
                    {
                        int targetX = invert ? pattern.width() - 1 - i : i;
                        int targetY = invert ? pattern.height() - 1 - j : j;
                        if (x + i < targetWidth && y + j < targetHeight)
                        {
                            mosaicImage.pixel(x + i, y + j) = pattern.pixel(targetX, targetY);
                        }
                    }
                }
            }
        }

        pattern = mosaicImage;
    }

    void glitch(sil::Image &image)
    {
        int iterations = 50;
        for (int i = 0; i < iterations; ++i)
        {
            int block_width = random_int(5, 25);
            int block_height = random_int(5, 15);

            int x1 = random_int(0, image.width() - block_width);
            int y1 = random_int(0, image.height() - block_height);
            int x2 = random_int(0, image.width() - block_width);
            int y2 = random_int(0, image.height() - block_height);
            for (int dx = 0; dx < block_width; ++dx)
            {
                for (int dy = 0; dy < block_height; ++dy)
                {
                    if (x1 + dx < image.width() && y1 + dy < image.height() &&
                        x2 + dx < image.width() && y2 + dy < image.height())
                    {
                        std::swap(image.pixel(x1 + dx, y1 + dy), image.pixel(x2 + dx, y2 + dy));
                    }
                }
            }
        }
        for (int i = 0; i < iterations / 2; ++i)
        {
            int line = random_int(0, image.height());
            int offset = random_int(-30, 30);

            for (int x = 0; x < image.width(); ++x)
            {
                int new_x = (x + offset + image.width()) % image.width();
                std::swap(image.pixel(x, line), image.pixel(new_x, line));
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

    sil::Image fade_between_colors(const glm::vec3 &color1, const glm::vec3 &color2)
    {
        sil::Image image{300 /*width*/, 200 /*height*/};

        for (int x{0}; x < image.width(); ++x)
        {
            for (int y{0}; y < image.height(); ++y)
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

    void dithering(sil::Image &image)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            for (int x = 0; x < image.width(); ++x)
            {
                float old_pixel = image.pixel(x, y).r;
                float new_pixel = old_pixel > 0.5f ? 1.0f : 0.0f;
                image.pixel(x, y).r = new_pixel;
                image.pixel(x, y).g = new_pixel;
                image.pixel(x, y).b = new_pixel;
                float quant_error = old_pixel - new_pixel;

                if (x + 1 < image.width())
                {
                    image.pixel(x + 1, y).r += quant_error * 7 / 16;
                    image.pixel(x + 1, y).g += quant_error * 7 / 16;
                    image.pixel(x + 1, y).b += quant_error * 7 / 16;
                }
                if (x - 1 >= 0 && y + 1 < image.height())
                {
                    image.pixel(x - 1, y + 1).r += quant_error * 3 / 16;
                    image.pixel(x - 1, y + 1).g += quant_error * 3 / 16;
                    image.pixel(x - 1, y + 1).b += quant_error * 3 / 16;
                }
                if (y + 1 < image.height())
                {
                    image.pixel(x, y + 1).r += quant_error * 5 / 16;
                    image.pixel(x, y + 1).g += quant_error * 5 / 16;
                    image.pixel(x, y + 1).b += quant_error * 5 / 16;
                }
                if (x + 1 < image.width() && y + 1 < image.height())
                {
                    image.pixel(x + 1, y + 1).r += quant_error * 1 / 16;
                    image.pixel(x + 1, y + 1).g += quant_error * 1 / 16;
                    image.pixel(x + 1, y + 1).b += quant_error * 1 / 16;
                }
            }
        }
    }

    void contrast_stretching(sil::Image &image)
    {
        float min_luminance = 1.0f;
        float max_luminance = 0.0f;
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float luminance = 0.30f * image.pixel(x, y).r + 0.59f * image.pixel(x, y).g + 0.11f * image.pixel(x, y).b;
                if (luminance < min_luminance)
                {
                    min_luminance = luminance;
                }
                if (luminance > max_luminance)
                {
                    max_luminance = luminance;
                }
            }
        }
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float &r = image.pixel(x, y).r;
                float &g = image.pixel(x, y).g;
                float &b = image.pixel(x, y).b;

                r = (r - min_luminance) / (max_luminance - min_luminance);
                g = (g - min_luminance) / (max_luminance - min_luminance);
                b = (b - min_luminance) / (max_luminance - min_luminance);
            }
        }
    }

    void vortex(sil::Image &image, float strength)
    {
        sil::Image original = image;
        int centerX = image.width() / 2;
        int centerY = image.height() / 2;

        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                int dx = x - centerX;
                int dy = y - centerY;
                float distance = std::sqrt(dx * dx + dy * dy);
                float angle = std::atan2(dy, dx) + strength * distance / std::min(image.width(), image.height());

                int srcX = static_cast<int>(centerX + distance * std::cos(angle));
                int srcY = static_cast<int>(centerY + distance * std::sin(angle));

                if (srcX >= 0 && srcX < image.width() && srcY >= 0 && srcY < image.height())
                {
                    image.pixel(x, y) = original.pixel(srcX, srcY);
                }
            }
        }
    }

    void convolution(sil::Image &image, const std::vector<std::vector<float>> &kernel)
    {
        int kernel_size = kernel.size();
        int offset = kernel_size / 2;
        sil::Image result = image;

        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float r = 0.0f, g = 0.0f, b = 0.0f;

                for (int i = 0; i < kernel_size; ++i)
                {
                    for (int j = 0; j < kernel_size; ++j)
                    {
                        int ix = x + i - offset;
                        int iy = y + j - offset;

                        if (ix >= 0 && ix < image.width() && iy >= 0 && iy < image.height())
                        {
                            r += image.pixel(ix, iy).r * kernel[i][j];
                            g += image.pixel(ix, iy).g * kernel[i][j];
                            b += image.pixel(ix, iy).b * kernel[i][j];
                        }
                    }
                }

                result.pixel(x, y).r = std::min(1.0f, std::max(0.0f, r));
                result.pixel(x, y).g = std::min(1.0f, std::max(0.0f, g));
                result.pixel(x, y).b = std::min(1.0f, std::max(0.0f, b));
            }
        }

        image = result;
    }

}