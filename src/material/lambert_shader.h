#pragma once

#include "material.h"

class LambertShader : public Material {
private:
    Colour _colour;

public:
    LambertShader(const Colour& colour);

    Colour shade(const Hit& hit, const Light& light) const override;
};
