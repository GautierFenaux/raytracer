#pragma once
#include "math/vector.h"
#include "geometry/ray.h"
#include "scene/scene.h"
#include "render/image.h"
#include "colour/colour.h"

class Camera {
private:
    Vector _position;
    double _screenWidth;

public:
    Camera(const Vector& position, const double screenWidth);

    const Vector& position() const;

    Ray rayThroughPixel(int column, int row, int imageWidth, int imageHeight) const;

    // Colour seen along one ray: the nearest surface, shaded by its material, or black
    Colour trace(const Ray& ray, const Scene& scene) const;

    void render(const Scene& scene, Image& image) const;
};
