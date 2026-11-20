#pragma once

#include <memory>
#include <optional>
#include <vector>
#include "geometry/shape.h"
#include "geometry/ray.h"
#include "geometry/hit.h"
#include "light/light.h"

// Everything that gets rendered: the shapes and the light.
// The scene owns its shapes. It only knows them as Shapes, never as Sphere or Plane.
class Scene {
private:
    Light _light;
    std::vector<std::unique_ptr<Shape>> _shapes;

public:
    explicit Scene(const Light& light);

    const Light& light() const;

    // Takes ownership of the shape
    void add(std::unique_ptr<Shape> shape);

    // The hit with the smallest t over all shapes, or std::nullopt if the ray hits nothing
    std::optional<Hit> nearestHit(const Ray& ray) const;
};
