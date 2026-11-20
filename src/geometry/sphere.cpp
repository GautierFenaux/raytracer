#include "sphere.h"
#include "ray.h"
#include <cmath>

Sphere::Sphere(const Vector& center, double radius, Material* material)
    : _center(center), _radius(radius), _material(material) {}

const Vector& Sphere::center() const { return _center; }
double Sphere::radius() const { return _radius; }
Material* Sphere::material() const { return _material; }

std::optional<Hit> Sphere::hit(const Ray& ray) const {
    Vector D = ray.direction();
    Vector O = ray.origin();
    Vector C = _center;

    Vector L = O - C;
    double a = D.dot(D);
    double b = 2*D.dot(L);
    double c = L.dot(L) - _radius*_radius;

    double delta = b*b - 4*a*c;

    if(delta < 0) {
        return std::nullopt;
    }

    double t1 = (-b - sqrt(delta)) / (2*a);
    double t2 = (-b + sqrt(delta)) / (2*a);

    // t1 <= t2 because a > 0. Keep the nearest root strictly in front of the origin:
    // t == 0 is the origin itself, which would make a surface hit itself later (shadows).
    double t;
    if(t1 > 0) {
        t = t1;
    } else if(t2 > 0) {
        t = t2;  // the ray starts inside the sphere
    } else {
        return std::nullopt;
    }

    Vector point = ray.at(t);
    Vector normal = (point - _center).normalised();

    return Hit{t, point, normal, _material};
}