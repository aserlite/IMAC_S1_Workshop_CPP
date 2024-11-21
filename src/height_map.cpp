#include "color_effects.hpp"

namespace Effects
{
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
                    color = glm::mix(glm::vec3(0.4f, 0.4f, 0.2f), glm::vec3(0.7f, 0.7f, 0.7f), (value - 0.80f) / 0.25f); // Montagnes

                image.pixel(x, y).r = color.r;
                image.pixel(x, y).g = color.g;
                image.pixel(x, y).b = color.b;
            }
        }

        return image;
    }
} // namespace Effects