#include "render/camera.h"
#include "colour/colour.h"

Camera::Camera(const Vector& position, const double screenWidth) :
    _position(position), _screenWidth(screenWidth) {}

const Vector& Camera::position() const {
    return _position;
}

Ray Camera::rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const {

    double pixelSize = _screenWidth / imageWidth;

    double x = ((column + 0.5) - (imageWidth / 2.0)) * pixelSize;
    double y = -((row + 0.5) - (imageHeight / 2.0)) * pixelSize;

    Vector pixelPosition(x, y, 0);
    Vector direction = pixelPosition - _position;

    return Ray(_position, direction);

}

Colour Camera::trace(const Ray& ray, const Scene& scene) const {
    std::optional<Hit> hit = scene.nearestHit(ray);
    if (!hit) {
        return Colour(0, 0, 0);
    }
    return hit->material->shade(*hit, scene.light());
}

void Camera::render(const Scene& scene, Image& image) const {
    for (int row = 0; row < image.height(); ++row) {
        for (int column = 0; column < image.width(); ++column) {
            Ray ray = rayThroughPixel(column, row, image.width(), image.height());
            image.setPixel(column, row, trace(ray, scene));
        }
    }
}
