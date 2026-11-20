#include "lambert_shader.h"
#include "geometry/hit.h"
#include "light/light.h"
#include <algorithm>

LambertShader::LambertShader(const Colour& colour) : _colour(colour) {}

Colour LambertShader::shade(const Hit& hit, const Light& light) const {
    Vector toLight = (light.position() - hit.point).normalised();

    // Surfaces facing away from the light receive no light, never negative light
    double intensity = std::max(0.0, hit.normal.dot(toLight));

    return _colour * light.colour() * intensity;
}
