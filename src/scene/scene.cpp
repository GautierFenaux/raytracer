#include "scene.h"

Scene::Scene(const Light& light) : _light(light) {}

const Light& Scene::light() const { return _light; }

void Scene::add(std::unique_ptr<Shape> shape) {
    _shapes.push_back(std::move(shape));
}

std::optional<Hit> Scene::nearestHit(const Ray& ray) const {
    std::optional<Hit> nearest;
    for (const std::unique_ptr<Shape>& shape : _shapes) {
        std::optional<Hit> hit = shape->hit(ray);  // polymorphic call: Sphere::hit, Plane::hit...
        if (hit && (!nearest || hit->t < nearest->t)) {
            nearest = hit;
        }
    }
    return nearest;
}
