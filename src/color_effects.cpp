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

    void gaussian_blur(sil::Image &image, float sigma)
    {
        int kernel_radius = static_cast<int>(std::ceil(3 * sigma));
        int kernel_size = 2 * kernel_radius + 1;
        std::vector<std::vector<float>> kernel(kernel_size, std::vector<float>(kernel_size));

        float sum = 0.0f;
        for (int i = -kernel_radius; i <= kernel_radius; ++i)
        {
            for (int j = -kernel_radius; j <= kernel_radius; ++j)
            {
                float value = std::exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
                kernel[i + kernel_radius][j + kernel_radius] = value;
                sum += value;
            }
        }

        for (int i = 0; i < kernel_size; ++i)
        {
            for (int j = 0; j < kernel_size; ++j)
            {
                kernel[i][j] /= sum;
            }
        }

        convolution(image, kernel);
    }

    void gaussian_difference(sil::Image &image, float sigma)
    {
        sil::Image original = image;
        gaussian_blur(image, sigma);
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                image.pixel(x, y).r = original.pixel(x, y).r - image.pixel(x, y).r;
                image.pixel(x, y).g = original.pixel(x, y).g - image.pixel(x, y).g;
                image.pixel(x, y).b = original.pixel(x, y).b - image.pixel(x, y).b;
            }
        }
    }

    void k_means_clustering(sil::Image &image, int k)
    {
        std::vector<glm::vec3> centroids(k);
        std::vector<int> labels(image.width() * image.height(), 0);
        std::vector<int> counts(k, 0);
        std::vector<glm::vec3> sums(k, glm::vec3(0.0f));
        for (int i = 0; i < k; ++i)
        {
            int x = random_int(0, image.width() - 1);
            int y = random_int(0, image.height() - 1);
            centroids[i] = image.pixel(x, y);
        }
        bool changed = true;
        while (changed)
        {
            changed = false;
            for (int x = 0; x < image.width(); ++x)
            {
                for (int y = 0; y < image.height(); ++y)
                {
                    glm::vec3 color = image.pixel(x, y);
                    float min_distance = std::numeric_limits<float>::max();
                    int best_centroid = 0;
                    for (int i = 0; i < k; ++i)
                    {
                        float distance = glm::distance(color, centroids[i]);
                        if (distance < min_distance)
                        {
                            min_distance = distance;
                            best_centroid = i;
                        }
                    }
                    if (labels[y * image.width() + x] != best_centroid)
                    {
                        labels[y * image.width() + x] = best_centroid;
                        changed = true;
                    }
                }
            }
            std::fill(counts.begin(), counts.end(), 0);
            std::fill(sums.begin(), sums.end(), glm::vec3(0.0f));
            for (int x = 0; x < image.width(); ++x)
            {
                for (int y = 0; y < image.height(); ++y)
                {
                    int label = labels[y * image.width() + x];
                    sums[label] += image.pixel(x, y);
                    counts[label]++;
                }
            }
            for (int i = 0; i < k; ++i)
            {
                if (counts[i] > 0)
                {
                    centroids[i] = sums[i] / static_cast<float>(counts[i]);
                }
            }
        }
        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                int label = labels[y * image.width() + x];
                image.pixel(x, y) = centroids[label];
            }
        }
    }

    void kuwahara_filter(sil::Image &image, int radius)
    {
        sil::Image result = image;

        for (int x = 0; x < image.width(); ++x)
        {
            for (int y = 0; y < image.height(); ++y)
            {
                float min_variance = std::numeric_limits<float>::max();
                glm::vec3 best_color{0.0f};

                for (int dx = -radius; dx <= radius; dx += radius)
                {
                    for (int dy = -radius; dy <= radius; dy += radius)
                    {
                        glm::vec3 sum{0.0f};
                        glm::vec3 sum_sq{0.0f};
                        int count = 0;

                        for (int i = 0; i <= radius; ++i)
                        {
                            for (int j = 0; j <= radius; ++j)
                            {
                                int nx = std::clamp(x + dx + i, 0, image.width() - 1);
                                int ny = std::clamp(y + dy + j, 0, image.height() - 1);

                                glm::vec3 color = image.pixel(nx, ny);
                                sum += color;
                                sum_sq += color * color;
                                ++count;
                            }
                        }

                        glm::vec3 mean = sum / static_cast<float>(count);
                        glm::vec3 variance = (sum_sq / static_cast<float>(count)) - (mean * mean);
                        float variance_sum = variance.r + variance.g + variance.b;

                        if (variance_sum < min_variance)
                        {
                            min_variance = variance_sum;
                            best_color = mean;
                        }
                    }
                }

                result.pixel(x, y) = best_color;
            }
        }

        image = result;
    }

    sil::Image diamond_square(int size)
    {
        int n = size;
        int map_size = (1 << n) + 1;
        std::vector<std::vector<float>> map(map_size, std::vector<float>(map_size, 0.0f));

        map[0][0] = random_float(0.0f, 1.0f);
        map[0][map_size - 1] = random_float(0.0f, 1.0f);
        map[map_size - 1][0] = random_float(0.0f, 1.0f);
        map[map_size - 1][map_size - 1] = random_float(0.0f, 1.0f);

        int step_size = map_size - 1;
        float scale = 1.0f;

        while (step_size > 1)
        {
            int half_step = step_size / 2;

            for (int x = 0; x < map_size - 1; x += step_size)
            {
                for (int y = 0; y < map_size - 1; y += step_size)
                {
                    float avg = (map[x][y] + map[x + step_size][y] + map[x][y + step_size] + map[x + step_size][y + step_size]) / 4.0f;
                    map[x + half_step][y + half_step] = avg + random_float(-scale, scale);
                }
            }

            for (int x = 0; x < map_size; x += half_step)
            {
                for (int y = (x + half_step) % step_size; y < map_size; y += step_size)
                {
                    float avg = (map[(x - half_step + map_size) % map_size][y] +
                                 map[(x + half_step) % map_size][y] +
                                 map[x][(y + half_step) % map_size] +
                                 map[x][(y - half_step + map_size) % map_size]) /
                                4.0f;
                    map[x][y] = avg + random_float(-scale, scale);
                }
            }

            step_size /= 2;
            scale /= 2.0f;
        }

        sil::Image image(map_size, map_size);
        for (int x = 0; x < map_size; ++x)
        {
            for (int y = 0; y < map_size; ++y)
            {
                float value = map[x][y];
                glm::vec3 color;
            if (value < 0.25f)
                color = glm::mix(glm::vec3(0.0f, 0.0f, 0.5f), glm::vec3(0.1f, 0.5f, 0.8f), value / 0.25f); // Eau
            else if (value < 0.5f)
                color = glm::mix(glm::vec3(0.1f, 0.5f, 0.8f), glm::vec3(0.2f, 0.8f, 0.2f), (value - 0.25f) / 0.25f); // Plages
            else if (value < 0.75f)
                color = glm::mix(glm::vec3(0.2f, 0.8f, 0.2f), glm::vec3(0.4f, 0.4f, 0.2f), (value - 0.5f) / 0.25f); // Forêts
            else
                color = glm::mix(glm::vec3(0.4f, 0.4f, 0.2f), glm::vec3(0.8f, 0.8f, 0.8f), (value - 0.75f) / 0.25f); // Montagnes

                image.pixel(x, y).r = color.r;
                image.pixel(x, y).g = color.g;
                image.pixel(x, y).b = color.b;
            }
        }
        image.save("output/before.png");
        std::vector<std::vector<float>> soft_smooth = {
            {1 / 16.0, 2 / 16.0, 1 / 16.0},
            {2 / 16.0, 4 / 16.0, 2 / 16.0},
            {1 / 16.0, 2 / 16.0, 1 / 16.0}
        };
        std::vector<std::vector<float>> sobel_x = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
        };

        std::vector<std::vector<float>> erosion = {
            {0.02, 0.04, 0.02},
            {0.04, 0.2, 0.04},
            {0.02, 0.04, 0.02}
        };

        std::vector<std::vector<float>> sharpen = {
            {0.02, 0.04, 0.02},
            {0.04, 0.2, 0.04},
            {0.02, 0.04, 0.02}
        };


        return image;
    }

}