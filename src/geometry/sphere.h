#pragma once

#include <optional>
#include "math/vector.h"
#include "geometry/shape.h"
#include "material/material.h"

class Sphere : public Shape {
private:
    Vector _center;
    double _radius;
    Material* _material;

public:
    Sphere(const Vector& center, double radius, Material* material);

    const Vector& center() const;
    double radius() const;
    Material* material() const;

    std::optional<Hit> hit(const Ray& ray) const override;
};
