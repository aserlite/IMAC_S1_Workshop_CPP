#include "color_effects.hpp"

namespace Effects
{
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
} // namespace Effects