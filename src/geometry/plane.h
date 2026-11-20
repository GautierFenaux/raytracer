#pragma once

#include <optional>
#include "math/vector.h"
#include "geometry/shape.h"
#include "material/material.h"

// An infinite flat surface through `point`, perpendicular to `normal`.
class Plane : public Shape {
private:
    Vector _point;
    Vector _normal;  // normalised in the constructor
    Material* _material;

public:
    Plane(const Vector& point, const Vector& normal, Material* material);

    std::optional<Hit> hit(const Ray& ray) const override;
};
