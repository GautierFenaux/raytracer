#include "plane.h"

Plane::Plane(const Vector& point, const Vector& normal, Material* material)
    : _point(point), _normal(normal.normalised()), _material(material) {}

std::optional<Hit> Plane::hit(const Ray& ray) const {
    // A point X is on the plane when n.(X - P) = 0.
    // With X = O + tD this gives t = n.(P - O) / n.D
    double nDotD = _normal.dot(ray.direction());

    // The ray runs parallel to the plane: it never reaches it
    if (nDotD == 0.0) {
        return std::nullopt;
    }

    double t = _normal.dot(_point - ray.origin()) / nDotD;

    // The plane is behind the ray's origin (or at it)
    if (t <= 0.0) {
        return std::nullopt;
    }

    return Hit{t, ray.at(t), _normal, _material};
}
