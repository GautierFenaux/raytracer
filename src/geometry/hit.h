#pragma once

#include "math/vector.h"
#include "material/material.h"

// Where a ray meets a shape.
// t is the ray parameter: point == ray.origin() + t * ray.direction().
// The scene compares t to keep the nearest hit.
struct Hit {
    double t;
    Vector point;
    Vector normal;       // unit vector, pointing out of the surface
    Material* material;  // not owned: the material outlives the shape
};
