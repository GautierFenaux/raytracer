#pragma once

#include <optional>
#include "geometry/ray.h"
#include "geometry/hit.h"

// Anything a ray can hit. The scene only knows this interface,
// so adding a new shape means adding a new class, nothing else.
class Shape {
public:
    virtual ~Shape() = default;

    // The nearest hit in front of the ray's origin (t > 0), with a unit normal,
    // or std::nullopt if the ray misses.
    virtual std::optional<Hit> hit(const Ray& ray) const = 0;
};
