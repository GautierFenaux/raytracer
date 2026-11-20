#include "flat_shader.h"

FlatShader::FlatShader(const Colour& colour) : _colour(colour) {}

Colour FlatShader::shade(const Hit&, const Light&) const { return _colour; }
