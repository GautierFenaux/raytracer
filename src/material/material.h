#pragma once

#include "colour/colour.h"

struct Hit;
class Light;

class Material {
public:
    virtual ~Material() = default;
    virtual Colour shade(const Hit& hit, const Light& light) const = 0;
};
