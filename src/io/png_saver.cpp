#include "png_saver.h"
#include "lodepng.h"
#include <vector>
#include <stdexcept>

void PngSaver::save(Image& image, const std::string& path) {
    const unsigned int w = image.width();
    const unsigned int h = image.height();

    std::vector<unsigned char> pixels;
    pixels.reserve(w * h * 4);

    for (unsigned int y = 0; y < h; ++y) {
        for (unsigned int x = 0; x < w; ++x) {
            Colour c = image.pixel(x, y);
            pixels.push_back(static_cast<unsigned char>(c.r() * 255.0));
            pixels.push_back(static_cast<unsigned char>(c.g() * 255.0));
            pixels.push_back(static_cast<unsigned char>(c.b() * 255.0));
            pixels.push_back(255);
        }
    }

    unsigned int error = lodepng::encode(path, pixels, w, h);
    if (error)
        throw std::runtime_error(lodepng_error_text(error));
}
