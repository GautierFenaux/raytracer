#pragma once

#include "material.h"

class FlatShader : public Material {
private:
    Colour _colour;

public:
    FlatShader(const Colour& colour);

    Colour shade(const Hit& hit, const Light& light) const override;
};
