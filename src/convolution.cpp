#include "color_effects.hpp"

namespace Effects
{
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
    
} // namespace Effects