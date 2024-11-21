#include <sil/sil.hpp>
#include "color_effects.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

int displayMenu(const std::vector<std::string> &options)
{
    std::cout << "Please choose an option:\n";
    for (size_t i = 0; i < options.size(); ++i)
    {
        std::cout << i + 1 << ". " << options[i] << "\n";
    }
    int choice;
    std::cin >> choice;
    return choice - 1;
}

void applyFilter(int choice, sil::Image &image)
{
    switch (choice)
    {
    case 0:
        Effects::keep_only_green(image);
        break;
    case 1:
        Effects::exchange_colors(image);
        break;
    case 2:
        Effects::greyscale(image);
        break;
    case 3:
        Effects::negative(image);
        break;
    case 4:
        Effects::miror(image);
        break;
    case 5:
        Effects::noise(image);
        break;
    case 6:
        Effects::rotate_90(image);
        break;
    case 7:
        Effects::rgb_split(image);
        break;
    case 8:
        Effects::luminosity(image, 1.2f);
        break;
    case 9:
        Effects::mosaic(image);
        break;
    case 10:
        Effects::miror_mosaic(image);
        break;
    case 11:
        Effects::glitch(image);
        break;
    case 12:
        Effects::sort_pixels(image);
        break;
    case 13:
        Effects::dithering(image);
        break;
    case 14:
        Effects::contrast_stretching(image);
        break;
    case 15:
        Effects::vortex(image, 1.0f);
        break;
    case 16:
        Effects::convolution(image, {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}});
        break;
    case 17:
        Effects::gaussian_blur(image, 1.0f);
        break;
    case 18:
        Effects::gaussian_difference(image, 1.0f);
        break;
    case 19:
        Effects::k_means_clustering(image, 5);
        break;
    case 20:
        Effects::kuwahara_filter(image, 3);
        break;
    default:
        std::cout << "Invalid choice\n";
        break;
    }
}

sil::Image applyGenerativeFunction(int choice)
{
    sil::Image image{500, 500};
    switch (choice)
    {
    case 0:
        return Effects::fade();
    case 1:
        return Effects::disk(10);
    case 2:
        return Effects::circle(image, 10, 2);
    case 3:
        Effects::animated_disk(10);
        return sil::Image(100, 100);
    case 4:
        return Effects::rosace();
    case 5:
        return Effects::fade_between_colors({1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f});
    case 6:
        return Effects::mandelbrot(750, 750, 100);
    case 7:
        return Effects::diamond_square(10);
    default:
        std::cout << "Invalid choice\n";
        return sil::Image(100, 100);
    }
}

void showLoadingAnimation(bool &loading)
{
    const std::vector<std::string> frames = {"|", "/", "-", "\\"};
    int frameIndex = 0;
    while (loading)
    {
        std::cout << "\rProcessing " << frames[frameIndex] << std::flush;
        frameIndex = (frameIndex + 1) % frames.size();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "\rProcessing done!   " << std::endl;
}

int main()
{
    std::vector<std::string> categories = {"Filters", "Generative Functions"};
    int categoryChoice = displayMenu(categories);

    if (categoryChoice == 0)
    {
        std::vector<std::string> filters = {
            "Keep Only Green", "Exchange Colors", "Greyscale", "Negative", "Miror", "Noise", "Rotate 90",
            "RGB Split", "Luminosity", "Mosaic", "Miror Mosaic", "Glitch", "Sort Pixels", "Dithering",
            "Contrast Stretching", "Vortex", "Convolution", "Gaussian Blur", "Gaussian Difference",
            "K-Means Clustering", "Kuwahara Filter"};
        int filterChoice = displayMenu(filters);

        std::string filePath;
        std::cout << "Enter the path to the image file: ";
        std::cin >> filePath;

        sil::Image image{filePath};

        bool loading = true;
        std::thread loadingThread(showLoadingAnimation, std::ref(loading));

        applyFilter(filterChoice, image);
        image.save("output/output.png");

        loading = false;
        loadingThread.join();
    }
    else if (categoryChoice == 1)
    {
        std::vector<std::string> generativeFunctions = {
            "Fade", "Disk", "Circle", "Animated Disk", "Rosace", "Fade Between Colors", "Mandelbrot", "Diamond Square"};
        int generativeChoice = displayMenu(generativeFunctions);

        bool loading = true;
        std::thread loadingThread(showLoadingAnimation, std::ref(loading));

        sil::Image image = applyGenerativeFunction(generativeChoice);
        image.save("output/output.png");

        loading = false;
        loadingThread.join();
    }
    else
    {
        std::cout << "Invalid category choice\n";
    }

    return 0;
}